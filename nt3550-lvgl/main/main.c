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

//回调函数
static void state_task(void *pvParameters)
{
	static char InfoBuffer[512] = {0};
	while (1)
	{
	    vTaskList((char *) &InfoBuffer);
		printf("任务名      任务状态 优先级   剩余栈 任务序号\r\n");
		printf("\r\n%s\r\n", InfoBuffer);
        vTaskDelay(2000 / portTICK_PERIOD_MS);
	}
}

void app_key_handler(key_type_e key, key_evt_e evt)
{
    lv_event_t event;

    ESP_LOGI(TAG, "key event: %d\n", evt);
    event.code = LV_EVENT_CLICKED;
    event.user_data = (void *)key;
    ui_event_handler(&event);
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

    //首先创建一个任务单独来做这件事情
    xTaskCreate(state_task, "state_task", 2048, NULL, 6, NULL);

    while (1) {
        vTaskDelay(pdMS_TO_TICKS(10000));
    }
}
