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

#include <stdio.h>
#include <string.h>

#include "esp_err.h"
#include "esp_log.h"

#include "nvs_flash.h"
#include "nvs.h"

#include "iot_import.h"

#define MFG_PARTITION_NAME "mfg_nvs"
#define NVS_PRODUCT "aliyun-key"

static const char *TAG = "wrapper_product";

static bool s_part_init_flag;

static esp_err_t HAL_ProductParam_init(void)
{
    esp_err_t ret = ESP_OK;

    do {
        if (s_part_init_flag == false) {
            if ((ret = nvs_flash_init_partition(MFG_PARTITION_NAME)) != ESP_OK) {
                ESP_LOGE(TAG, "NVS Flash init %s failed, Please check that you have flashed mfg_nvs partition!!!", MFG_PARTITION_NAME);
                break;
            }

            s_part_init_flag = true;
        }
    } while (0);

    return ret;
}

static int HAL_GetProductParam(char *param_name, const char *param_name_str)
{
    esp_err_t ret;
    size_t read_len = 0;
    nvs_handle handle;

    do {
        if (HAL_ProductParam_init() != ESP_OK) {
            break;
        }

        if (param_name == NULL) {
            ESP_LOGE(TAG, "%s param %s NULL", __func__, param_name);
            break;
        }

        ret = nvs_open_from_partition(MFG_PARTITION_NAME, NVS_PRODUCT, NVS_READONLY, &handle);

        if (ret != ESP_OK) {
            ESP_LOGE(TAG, "%s nvs_open failed with %x", __func__, ret);
            break;
        }

        ret = nvs_get_str(handle, param_name_str, NULL, (size_t *)&read_len);

        if (ret != ESP_OK) {
            ESP_LOGE(TAG, "%s nvs_get_str get %s failed with %x", __func__, param_name_str, ret);
            break;
        }

        ret = nvs_get_str(handle, param_name_str, param_name, (size_t *)&read_len);

        if (ret != ESP_OK) {
            ESP_LOGE(TAG, "%s nvs_get_str get %s failed with %x", __func__, param_name_str, ret);
        } else {
            ESP_LOGV(TAG, "%s %s %s", __func__, param_name_str, param_name);
        }

        nvs_close(handle);
    } while (0);

    return read_len;
}

int HAL_GetPartnerID(char pid_str[PID_STR_MAXLEN])
{
    memset(pid_str, 0x0, PID_STR_MAXLEN);
    strcpy(pid_str, "espressif");
    return strlen(pid_str);
}

int HAL_GetModuleID(char mid_str[MID_STR_MAXLEN])
{
    memset(mid_str, 0x0, MID_STR_MAXLEN);
    strcpy(mid_str, "wroom");
    return strlen(mid_str);
}

char *HAL_GetChipID(char cid_str[HAL_CID_LEN])
{
    memset(cid_str, 0x0, HAL_CID_LEN);
    strncpy(cid_str, "esp8266", HAL_CID_LEN);
    cid_str[HAL_CID_LEN - 1] = '\0';
    return cid_str;
}

int HAL_GetDeviceID(char device_id[DEVICE_ID_MAXLEN])
{
    memset(device_id, 0x0, DEVICE_ID_MAXLEN);
    char device_name[DEVICE_NAME_MAXLEN] = {0};
    char product_key[PRODUCT_KEY_MAXLEN] = {0};
    HAL_GetDeviceName(device_name);
    HAL_GetProductKey(product_key);
    HAL_Snprintf(device_id, DEVICE_ID_MAXLEN, "%s.%s", product_key, device_name);
    device_id[DEVICE_ID_MAXLEN - 1] = '\0';
    return strlen(device_id);
}

/**
 * @brief Get device name from user's system persistent storage
 *
 * @param [ou] device_name: array to store device name, max length is IOTX_DEVICE_NAME_LEN
 * @return the actual length of device name
 */
int HAL_GetDeviceName(char device_name[DEVICE_NAME_MAXLEN])
{
    return HAL_GetProductParam(device_name, "DeviceName");
}

/**
 * @brief Get device secret from user's system persistent storage
 *
 * @param [ou] device_secret: array to store device secret, max length is IOTX_DEVICE_SECRET_LEN
 * @return the actual length of device secret
 */
int HAL_GetDeviceSecret(char device_secret[DEVICE_SECRET_MAXLEN])
{
    return HAL_GetProductParam(device_secret, "DeviceSecret");
}

/**
 * @brief Get product key from user's system persistent storage
 *
 * @param [ou] product_key: array to store product key, max length is IOTX_PRODUCT_KEY_LEN
 * @return  the actual length of product key
 */
int HAL_GetProductKey(char product_key[PRODUCT_KEY_MAXLEN])
{
    return HAL_GetProductParam(product_key, "ProductKey");
}

int HAL_GetProductSecret(char product_secret[PRODUCT_SECRET_MAXLEN])
{
    return HAL_GetProductParam(product_secret, "ProductSecret");
}

/**
 * @brief Get firmware version
 *
 * @param [ou] version: array to store firmware version, max length is IOTX_FIRMWARE_VER_LEN
 * @return the actual length of firmware version
 */
int HAL_GetFirmwareVersion(char version[FIRMWARE_VERSION_MAXLEN])
{
    if (!version) {
        ESP_LOGE(TAG, "%s version is NULL", __func__);
        return 0;
    }

    memset(version, 0, FIRMWARE_VERSION_MAXLEN);
    int len = strlen(CONFIG_LINKKIT_FIRMWARE_VERSION);
    if (len > FIRMWARE_VERSION_MAXLEN) {
        len = 0;
    } else {
        memcpy(version, CONFIG_LINKKIT_FIRMWARE_VERSION, len);
    }

    return len;
}

static int HAL_SetProductParam(char *param_name, const char *param_name_str)
{
    esp_err_t ret;
    size_t write_len = 0;
    nvs_handle handle;

    do {
        if (HAL_ProductParam_init() != ESP_OK) {
            break;
        }

        if (param_name == NULL) {
            ESP_LOGE(TAG, "%s param %s NULL", __func__, param_name);
            break;
        }

        ret = nvs_open_from_partition(MFG_PARTITION_NAME, NVS_PRODUCT, NVS_READWRITE, &handle);

        if (ret != ESP_OK) {
            ESP_LOGE(TAG, "%s nvs_open failed with %x", __func__, ret);
            break;
        }

        ret = nvs_set_str(handle, param_name_str, param_name);

        if (ret != ESP_OK) {
            ESP_LOGE(TAG, "%s nvs_set_str set %s failed with %x", __func__, param_name_str, ret);
        } else {
            write_len = strlen(param_name);
            ESP_LOGV(TAG, "%s %s %s", __func__, param_name_str, param_name);
        }

        nvs_close(handle);
    } while (0);

    return write_len;
}

int HAL_SetDeviceName(char device_name[DEVICE_NAME_MAXLEN])
{
    return HAL_SetProductParam(device_name, "DeviceName");
}

int HAL_SetDeviceSecret(char device_secret[DEVICE_SECRET_MAXLEN])
{
    return HAL_SetProductParam(device_secret, "DeviceSecret");
}

int HAL_SetProductKey(char product_key[PRODUCT_KEY_MAXLEN])
{
    return HAL_SetProductParam(product_key, "ProductKey");
}

int HAL_SetProductSecret(char product_secret[PRODUCT_SECRET_MAXLEN])
{
    return HAL_SetProductParam(product_secret, "ProductSecret");
}
