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

static const char *TAG = "main";

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

    while (1) {
        vTaskDelay(pdMS_TO_TICKS(10000));
    }
}
