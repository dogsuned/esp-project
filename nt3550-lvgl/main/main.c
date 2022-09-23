/*
 * SPDX-FileCopyrightText: 2021 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_err.h"
#include "esp_log.h"
#include "lcd.h"
#include "key.h"
#include "ui.h"

static const char *TAG = "main";

void app_key_handler(key_type_e key, key_evt_e evt)
{
    lv_event_t event;

    ESP_LOGI(TAG, "key event: %d\n", evt);
    event.user_data = (void *)key;
    ui_event_scmain(&event);
}

void app_main(void)
{
    esp_err_t retval;

    retval = key_process_start();
    if (retval) {
        ESP_LOGE(TAG, "key_process_start failed: %d\n", retval);
    }

    retval = lcd_process_start();
    if (retval) {
        ESP_LOGE(TAG, "lcd_process_start failed: %d\n", retval);
    }

    key_func_register(KEY_0, app_key_handler);
    key_func_register(KEY_1, app_key_handler);
    key_func_register(KEY_2, app_key_handler);
    key_func_register(KEY_3, app_key_handler);

    while (1) {
        vTaskDelay(pdMS_TO_TICKS(10000));
    }
}
