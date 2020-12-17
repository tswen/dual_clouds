#include "esp_log.h"
#include "esp_system.h"
#include "nvs_flash.h"

#include "driver/gpio.h"

#include "button.h"
#include "conn_mgr.h"
#include "app_button.h"
#include "app_joylink.h"
#include "app_ali_smartliving.h"
#include "joylink_softap_start.h"

static void button_press_3sec_cb(void *arg)
{
    ESP_LOGW("button", "press_3sec");
    nvs_flash_erase();
    esp_restart();
}

static void button_press_cb(void *arg)
{
    ESP_LOGW("button", "press");
    if(!distribution_network_change) {    //In normal mode(joylink + ali-smartliving)
        if(joylink_softap_status()) {     //joylink is configuring the network
            delete_joylink_task();
            distribution_network_change = true;
            xTaskCreate((void (*)(void *))start_conn_mgr, "conn_mgr", 3072, NULL, 5, NULL);
        } else {    //joylink is connected to the cloud
            esp_restart();
        }
    } else {    //In ali-smartliving mode
        esp_restart();
    }
}

static void configure_push_button(int gpio_num, void (*btn_cb)(void *))
{
    button_handle_t btn_handle = iot_button_create(gpio_num, 0);

    if (btn_handle) {
        iot_button_set_evt_cb(btn_handle, BUTTON_CB_TAP, button_press_cb, NULL);
        iot_button_add_on_press_cb(btn_handle, 3, button_press_3sec_cb, NULL);
    }
}

void button_Init(void)
{
    configure_push_button(GPIO_NUM_0, NULL);
}
