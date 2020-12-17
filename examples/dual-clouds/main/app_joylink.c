// Copyright 2015-2020 Espressif Systems (Shanghai) PTE LTD
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"

#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_log.h"
#include "esp_event_loop.h"
#include "nvs.h"
#include "nvs_flash.h"
#include "app_joylink.h"
#include "linkkit_solo.h"

#include "joylink_softap_start.h"
#include "joylink.h"

#if !defined(ESP_IDF_VERSION)
#include "apps/sntp/sntp.h"
#elif (ESP_IDF_VERSION < ESP_IDF_VERSION_VAL(3,4,0))
#include "apps/sntp/sntp.h"
#else
#include "esp_sntp.h"
#endif

TaskHandle_t joylink_task_handle = NULL;

static void esp_start_ap_mode(void)
{
    wifi_config_t config;

    memset(&config, 0x0, sizeof(config));
    esp_wifi_set_mode(WIFI_MODE_APSTA);
    printf("ssid:%s\r\n", CONFIG_JOYLINK_SOFTAP_SSID);

    config.ap.ssid_len = strlen(CONFIG_JOYLINK_SOFTAP_SSID);

    if (config.ap.ssid_len > sizeof(config.ap.ssid)) {
        config.ap.ssid_len = sizeof(config.ap.ssid);
    }

    memcpy(config.ap.ssid, CONFIG_JOYLINK_SOFTAP_SSID, config.ap.ssid_len);
    config.ap.max_connection = 3;
    config.ap.channel = 9;
    esp_wifi_set_config(WIFI_IF_AP, &config);
}

static void joylink_task(void *pvParameters)
{
    nvs_handle out_handle;
    wifi_config_t config;
    size_t size = 0;
    bool flag = false;

    esp_wifi_set_mode(WIFI_MODE_STA);

    if (nvs_open("joylink_wifi", NVS_READONLY, &out_handle) == ESP_OK) {
        memset(&config,0x0,sizeof(config));
        size = sizeof(config.sta.ssid);
        if (nvs_get_str(out_handle,"ssid",(char*)config.sta.ssid,&size) == ESP_OK) {
            if (size > 0) {
                size = sizeof(config.sta.password);
                if (nvs_get_str(out_handle,"password",(char*)config.sta.password,&size) == ESP_OK) {
                    flag = true;
                } else {
                    printf("--get password fail");
                }
            }
        } else {
            printf("--get ssid fail");
        }
        nvs_close(out_handle);
    }

    if (flag) {
        esp_wifi_set_config(ESP_IF_WIFI_STA,&config);
        esp_wifi_connect();
    } else {
        esp_start_ap_mode();
        joylink_softap_start(1000*60*60);
    }
    vTaskDelay(30000 / portTICK_RATE_MS);

    xTaskCreate((void (*)(void *))linkkit_main, "light", 10240, NULL, 5, NULL);

    vTaskDelete(NULL);
}

void delete_joylink_task(void)
{
    vTaskDelete(joylink_task_handle);
}

void joylink_main(void)
{
    xTaskCreate(joylink_task, "jl_task", 6000, NULL, 2, &joylink_task_handle);
}
