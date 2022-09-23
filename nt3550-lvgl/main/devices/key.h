#ifndef __KEY_H_
#define __KEY_H_

typedef enum {
    KEY_0 = 0,
    KEY_1,
    KEY_2,
    KEY_3,
    KEY_MAX
} key_type_e;

typedef enum {
    KEY_EVT_SHORT_CLICK,
    KEY_EVT_LONG_PRESS
} key_evt_e;

typedef void (*key_evt_callback_f)(key_type_e key, key_evt_e evt);
void key_evt_default_callback(key_type_e key, key_evt_e evt);
esp_err_t key_func_register(key_type_e key, key_evt_callback_f cb);
esp_err_t key_process_start(void);

#endif
