/*
 * ESPRESSIF MIT License
 *
 * Copyright (c) 2019 <ESPRESSIF SYSTEMS (SHANGHAI) PTE LTD>
 *
 * Permission is hereby granted for use on all ESPRESSIF SYSTEMS products, in which case,
 * it is free of charge, to any person obtaining a copy of this software and associated
 * documentation files (the "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the Software is furnished
 * to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#include <stdlib.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"

#include "esp_err.h"
#include "esp_event_loop.h"
#include "esp_log.h"
#include "esp_wifi.h"

#include "lwip/apps/sntp.h"

#include "iot_import.h"

#include "conn_mgr.h"
#include "linkkit_solo.h"
#include "joylink.h"

bool distribution_network_change = 0;

static const char *TAG = "conn_mgr";

static system_event_cb_t hal_wifi_system_cb;

static esp_err_t conn_mgr_obtain_time(void)
{
    sntp_setoperatingmode(SNTP_OPMODE_POLL);
    sntp_setservername(0, "pool.ntp.org");
    sntp_setservername(1, "ntp1.aliyun.com");
    sntp_setservername(2, "cn.ntp.org.cn"); 
    sntp_init();

    return ESP_OK;
}

static void joylink_main_task(void *pvParameters)
{
    joylink_main_start();

    vTaskDelete(NULL);
}

static esp_err_t conn_mgr_wifi_event_loop_handler(void *ctx, system_event_t *event)
{
    system_event_info_t *info = &event->event_info;
    switch (event->event_id) {
        case SYSTEM_EVENT_STA_GOT_IP:
            conn_mgr_obtain_time();
            if(distribution_network_change) {
                xTaskCreate((void (*)(void *))linkkit_main, "light", 10240, NULL, 5, NULL);
            } else {
                xTaskCreate(joylink_main_task, "joylink_main_task", 1024*11, NULL, 2, NULL);
            }
            break;

        case SYSTEM_EVENT_STA_DISCONNECTED:
            ESP_LOGE(TAG, "Disconnect reason : %d", info->disconnected.reason);
#ifdef CONFIG_IDF_TARGET_ESP8266
            if (info->disconnected.reason == WIFI_REASON_BASIC_RATE_NOT_SUPPORT) {
                /*Switch to 802.11 bgn mode */
                esp_wifi_set_protocol(ESP_IF_WIFI_STA, WIFI_PROTOCOL_11B | WIFI_PROTOCOL_11G | WIFI_PROTOCOL_11N);
            }
#endif
            esp_wifi_connect();
            break;

        default:
            break;
    }

    /** The application loop event handle */
    if (hal_wifi_system_cb) {
        hal_wifi_system_cb(ctx, event);
    }

    return ESP_OK;
}

esp_err_t app_wifi_init(void)
{
    extern esp_err_t HAL_Kv_Init(void);
    HAL_Kv_Init();

    tcpip_adapter_init();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_event_loop_init(conn_mgr_wifi_event_loop_handler, NULL));
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    ESP_ERROR_CHECK(esp_wifi_set_storage(WIFI_STORAGE_RAM));
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));
    ESP_ERROR_CHECK(esp_wifi_start());

    return ESP_OK;
}

static esp_err_t conn_mgr_is_configured(bool *configured)
{
    if (!configured) {
        return ESP_ERR_INVALID_ARG;
    }

    *configured = false;

    int ssid_len = 32;
    uint8_t ssid[32];

    int ret = HAL_Kv_Get(STA_SSID_KEY, ssid, &ssid_len);

    if (ret == ESP_OK && ssid_len) {
        *configured = true;
        ESP_LOGI(TAG, "Found ssid %s", ssid);
    }

    return ESP_OK;
}

static esp_err_t conn_mgr_wifi_connect(void)
{
    wifi_config_t wifi_config = {0};
    int ssid_len = sizeof(wifi_config.sta.ssid);
    int password_len = sizeof(wifi_config.sta.password);

    int ret = HAL_Kv_Get(STA_SSID_KEY, wifi_config.sta.ssid, &ssid_len);

    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to get stored SSID");
        return ESP_FAIL;
    }

    /* Even if the password is not found, it is not an error, as it could be an open network */
    ret = HAL_Kv_Get(STA_PASSWORD_KEY, wifi_config.sta.password, &password_len);

    if (ret != ESP_OK) {
        ESP_LOGW(TAG, "Failed to get stored Password");
        password_len = 0;
    }

    esp_wifi_set_mode(WIFI_MODE_STA);
    esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_config);
    esp_wifi_start();
    esp_wifi_connect();

    return ESP_OK;
}

esp_err_t conn_mgr_start(void)
{
    bool ret = true;
    bool configured = false;
    uint8_t mode = 0;
    int mode_len = sizeof(uint8_t);
    conn_sc_mode_t awss_mode = CONN_SC_ZERO_MODE;

    // Let's find out if the device is configured.
    if (conn_mgr_is_configured(&configured) != ESP_OK) {
        return ESP_FAIL;
    }

    // Get SC mode and decide to start which awss service
    HAL_Kv_Get(SC_MODE, &mode, &mode_len);
    if (mode_len && mode == CONN_SOFTAP_MODE) {
        awss_mode = CONN_SOFTAP_MODE;
    }

    // If the device is not yet configured, start awss service.
    if (!configured) {
        do {
            if (awss_config_press() != 0) {
                ret = false;
                break;
            }
            if (awss_mode == CONN_SOFTAP_MODE) {
                if (awss_dev_ap_start() != 0) {
                    ret = false;
                    break;
                }
            } else {
                if (awss_start() != 0) {
                    ret = false;
                    break;
                }
            }
        } while (0);
    } else {
        if (conn_mgr_wifi_connect() != ESP_OK) {
            ret = false;
        }
    }

    return ret == true ? ESP_OK : ESP_FAIL;
}
