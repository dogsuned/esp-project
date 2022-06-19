#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include <time.h>
#include "key.h"

#define KEY_0_GPIO              41
#define KEY_1_GPIO              42
#define KEY_2_GPIO              39
#define KEY_3_GPIO              40

#define KEY_STATE_UP            1
#define KEY_STATE_DOWN          0

#define KEY_LONG_PRESS_MS       (1500)

typedef enum {
    KEY_ISR_FALLING,
    KEY_ISR_RISING
} key_isr_e;

typedef struct {
    key_type_e key;
    uint8_t gpio;
    uint8_t state;
    uint64_t tv;
    key_evt_callback_f cb;
} key_mng_t;

typedef struct {
    uint8_t gpio;
    key_isr_e evt;
} key_msg_t;

static const char *TAG = "key";
static uint32_t key_gpio_map[KEY_MAX] = {
    KEY_0_GPIO,
    KEY_1_GPIO,
    KEY_2_GPIO,
    KEY_3_GPIO,
};
static key_mng_t key_pool[KEY_MAX];
static xQueueHandle key_evt_queue = NULL;

static void key_gpio_isr_handle(void *arg)
{
    key_msg_t msg;

    msg.gpio = (uint32_t)arg;
    if (gpio_get_level(msg.gpio)) {
        msg.evt = KEY_ISR_RISING;
    } else {
        msg.evt = KEY_ISR_FALLING;
    }

    if (key_evt_queue) {
        xQueueSendFromISR(key_evt_queue, &msg, NULL);
    }
}

static void key_gpio_config(uint8_t gpio)
{
    gpio_config_t key_gpio = {
        .pin_bit_mask = 1ULL << gpio,
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = 1,
        .pull_down_en = 0,
        .intr_type = GPIO_INTR_ANYEDGE
    };
    gpio_config(&key_gpio);
    gpio_isr_handler_add(gpio, key_gpio_isr_handle, (void *)((uint32_t)gpio));
}

static void key_mng_init(void)
{
    int idx;

    gpio_install_isr_service(0);
    for (idx = 0; idx < KEY_MAX; idx++) {
        key_pool[idx].key = idx;
        key_pool[idx].gpio = key_gpio_map[idx];
        key_gpio_config(key_pool[idx].gpio);
        key_pool[idx].state = gpio_get_level(key_pool[idx].gpio);
        ESP_LOGD(TAG, "gpio[%d] level: %d\n", key_pool[idx].gpio, key_pool[idx].state);
        key_pool[idx].tv = 0;
        key_pool[idx].cb = NULL;
    }
}

static key_type_e get_key_from_gpio(uint8_t gpio)
{
    key_type_e type;

    for (type = 0; type < KEY_MAX; type++) {
        if (gpio == key_gpio_map[type]) {
            return type;
        }
    }
    return KEY_MAX;
}

static void key_mng_handler(void *arg)
{
    int i;
    struct timespec ts;
    key_msg_t msg;
    key_type_e key;

    for(;;) {
        if(xQueueReceive(key_evt_queue, &msg, 200 / portTICK_PERIOD_MS)) {
            clock_gettime(CLOCK_REALTIME, &ts);
            ESP_LOGD(TAG, "key_gpio[%d] evt: %d\n", msg.gpio, msg.evt);
            key = get_key_from_gpio(msg.gpio);
            if (msg.evt == KEY_ISR_FALLING) {
                key_pool[key].state = KEY_STATE_DOWN;
                key_pool[key].tv = ts.tv_sec * 1000 + ts.tv_nsec / 1000000;
            } else if (msg.evt == KEY_ISR_RISING) {
                if (key_pool[key].state == KEY_STATE_DOWN) {
                    if (key_pool[key].cb) {
                        key_pool[key].cb(key_pool[key].key, KEY_EVT_SHORT_CLICK);
                    } else {
                        key_evt_default_callback(key_pool[key].key, KEY_EVT_SHORT_CLICK);
                    }
                    key_pool[key].state = KEY_STATE_UP;
                }
            }
        } else {
            clock_gettime(CLOCK_REALTIME, &ts);
            for (i = 0; i < KEY_MAX; i++) {
                if (key_pool[i].state == KEY_STATE_DOWN && (ts.tv_sec * 1000 + ts.tv_nsec / 1000000 - key_pool[i].tv) >= KEY_LONG_PRESS_MS) {
                    key_pool[i].state = KEY_STATE_UP;
                    if (key_pool[i].cb) {
                        key_pool[i].cb(key_pool[i].key, KEY_EVT_LONG_PRESS);
                    } else {
                        key_evt_default_callback(key_pool[i].key, KEY_EVT_LONG_PRESS);
                    }
                }
            }
        }
    }
}

esp_err_t key_process_start(void)
{
    esp_err_t retval = ESP_OK;

    ESP_LOGI(TAG, "ready to create key process\n");
    key_mng_init();

    key_evt_queue = xQueueCreate(5, sizeof(key_msg_t));
    if (key_evt_queue == NULL) {
        ESP_LOGE(TAG, "failed create key msg queue\n");
        return ESP_FAIL;
    }

    xTaskCreate(key_mng_handler, "key_mng_handler", 2048, NULL, 10, NULL);
    return retval;
}

esp_err_t key_func_register(key_type_e key, key_evt_callback_f cb)
{
    int i;
    esp_err_t retval = ESP_OK;

    for (i = 0; i < KEY_MAX; i++) {
        if (key_pool[i].key == key && key_pool[i].cb == NULL) {
            key_pool[i].cb = cb;
        }
    }

    if (i >= KEY_MAX) {
        retval = ESP_FAIL;
    }

    return retval;
}

void key_evt_default_callback(key_type_e key, key_evt_e evt)
{
    ESP_LOGI(TAG, "user_key[%d] evt: %d\n", key, evt);
}
