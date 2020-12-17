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

#pragma once

#include "esp_err.h"
#include "esp_event_loop.h"

#ifdef __cplusplus
extern "C" {
#endif

#define HOTSPOT_AP "aha"
#define ROUTER_AP "adha"
#define STA_SSID_KEY             "stassid"
#define STA_PASSWORD_KEY         "pswd"
#define AP_SSID_KEY              CONFIG_AP_SSID_KEY
#define SC_MODE                  "scmode"

typedef enum {
    CONN_SC_ZERO_MODE = 1,
    CONN_SOFTAP_MODE  = 2,
} conn_sc_mode_t;

extern bool distribution_network_change;

/**
 * @brief init the connection management module
 * 
 * @return
 *     - ESP_OK : OK
 *     - others : fail
 */
esp_err_t app_wifi_init(void);

/**
 * @brief start the connection management module
 * 
 * If the device is configured, the device will connect to the router which is configured.
 * If the device is not configured, the device will start awss service.
 * 
 * @return
 *     - ESP_OK : OK
 *     - others : fail
 */
esp_err_t conn_mgr_start(void);

