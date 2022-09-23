#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_timer.h"
#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_vendor.h"
#include "esp_lcd_panel_ops.h"
#include "driver/gpio.h"
#include "esp_err.h"
#include "esp_log.h"
#include "lvgl.h"
#include "ui.h"

#define LCD_PIXEL_CLOCK_HZ     (10 * 1000 * 1000)
#define LCD_GPIO_STATE_ON  1
#define LCD_GPIO_STATE_OFF !LCD_GPIO_STATE_ON

#define LCD_PWR_GPIO      (0)
#define LCD_BK_LIGHT_GPIO (35)
#define LCD_RST_GPIO      (-1)
#define LCD_CS_GPIO       (17)
#define LCD_RD_GPIO       (18)
#define LCD_DC_GPIO       (47)
#define LCD_PCLK_GPIO     (48)

#define LCD_DATA0_GPIO    (1)
#define LCD_DATA1_GPIO    (2)
#define LCD_DATA2_GPIO    (3)
#define LCD_DATA3_GPIO    (4)
#define LCD_DATA4_GPIO    (5)
#define LCD_DATA5_GPIO    (6)
#define LCD_DATA6_GPIO    (7)
#define LCD_DATA7_GPIO    (8)
#define LCD_DATA8_GPIO    (9)
#define LCD_DATA9_GPIO    (10)
#define LCD_DATA10_GPIO   (11)
#define LCD_DATA11_GPIO   (12)
#define LCD_DATA12_GPIO   (13)
#define LCD_DATA13_GPIO   (14)
#define LCD_DATA14_GPIO   (15)
#define LCD_DATA15_GPIO   (16)

// The pixel number in horizontal and vertical
#define LCD_H_RES              480
#define LCD_V_RES              800
// Bit number used to represent command and parameter
#define LCD_CMD_BITS           16
#define LCD_PARAM_BITS         16

#define LVGL_TICK_PERIOD_MS    2

static const char *TAG = "lcd";
extern void example_lvgl_demo_ui(lv_obj_t *scr);

static bool notify_lvgl_flush_ready(esp_lcd_panel_io_handle_t panel_io, esp_lcd_panel_io_event_data_t *edata, void *user_ctx)
{
    lv_disp_drv_t *disp_driver = (lv_disp_drv_t *)user_ctx;
    lv_disp_flush_ready(disp_driver);
    return false;
}

static void lvgl_flush_cb(lv_disp_drv_t *drv, const lv_area_t *area, lv_color_t *color_map)
{
    esp_lcd_panel_handle_t panel_handle = (esp_lcd_panel_handle_t) drv->user_data;
    int offsetx1 = area->x1;
    int offsetx2 = area->x2;
    int offsety1 = area->y1;
    int offsety2 = area->y2;
    // copy a buffer's content to a specific area of the display
    esp_lcd_panel_draw_bitmap(panel_handle, offsetx1, offsety1, offsetx2 + 1, offsety2 + 1, color_map);
}

static void lvgl_tick_increase(void *arg)
{
    /* Tell LVGL how many milliseconds has elapsed */
    lv_tick_inc(LVGL_TICK_PERIOD_MS);
}

static void lcd_task_handler(void *arg)
{
    while (1) {
        // raise the task priority of LVGL and/or reduce the handler period can improve the performance
        vTaskDelay(pdMS_TO_TICKS(10));
        // The task running lv_timer_handler should have lower priority than that running `lv_tick_inc`
        lv_timer_handler();
    }
}

esp_err_t lcd_process_start(void)
{
    static lv_disp_draw_buf_t disp_buf; // contains internal graphic buffer(s) called draw buffer(s)
    static lv_disp_drv_t disp_drv;      // contains callback functions
    gpio_config_t bk_gpio_config = {
        .mode = GPIO_MODE_OUTPUT,
        .pin_bit_mask = 1ULL << LCD_BK_LIGHT_GPIO | 1ULL << LCD_PWR_GPIO | 1ULL << LCD_RD_GPIO
    };
    esp_lcd_i80_bus_handle_t i80_bus = NULL;
    esp_lcd_i80_bus_config_t bus_config = {
        .dc_gpio_num = LCD_DC_GPIO,
        .wr_gpio_num = LCD_PCLK_GPIO,
        .data_gpio_nums = {
            LCD_DATA0_GPIO,
            LCD_DATA1_GPIO,
            LCD_DATA2_GPIO,
            LCD_DATA3_GPIO,
            LCD_DATA4_GPIO,
            LCD_DATA5_GPIO,
            LCD_DATA6_GPIO,
            LCD_DATA7_GPIO,
            LCD_DATA8_GPIO,
            LCD_DATA9_GPIO,
            LCD_DATA10_GPIO,
            LCD_DATA11_GPIO,
            LCD_DATA12_GPIO,
            LCD_DATA13_GPIO,
            LCD_DATA14_GPIO,
            LCD_DATA15_GPIO,
        },
        .bus_width = 16,
        .max_transfer_bytes = LCD_H_RES * 40 * sizeof(uint16_t)
    };
    esp_lcd_panel_io_handle_t io_handle = NULL;
    esp_lcd_panel_io_i80_config_t io_config = {
        .cs_gpio_num = LCD_CS_GPIO,
        .pclk_hz = LCD_PIXEL_CLOCK_HZ,
        .trans_queue_depth = 10,
        .dc_levels = {
            .dc_idle_level = 0,
            .dc_cmd_level = 0,
            .dc_dummy_level = 0,
            .dc_data_level = 1,
        },
        .on_color_trans_done = notify_lvgl_flush_ready,
        .user_ctx = &disp_drv,
        .lcd_cmd_bits = LCD_CMD_BITS,
        .lcd_param_bits = LCD_PARAM_BITS,
    };
    esp_lcd_panel_handle_t panel_handle = NULL;
    esp_lcd_panel_dev_config_t panel_config = {
        .reset_gpio_num = LCD_RST_GPIO,
        .color_space = ESP_LCD_COLOR_SPACE_RGB,
        .bits_per_pixel = 16,
    };

    ESP_LOGI(TAG, "Turn off LCD backlight");
    ESP_ERROR_CHECK(gpio_config(&bk_gpio_config));
    gpio_set_level(LCD_BK_LIGHT_GPIO, LCD_GPIO_STATE_OFF);
    gpio_set_level(LCD_PWR_GPIO, LCD_GPIO_STATE_OFF);
    gpio_set_level(LCD_RD_GPIO, LCD_GPIO_STATE_ON);

    ESP_LOGI(TAG, "Initialize Intel 8080 bus");
    ESP_ERROR_CHECK(esp_lcd_new_i80_bus(&bus_config, &i80_bus));
    ESP_ERROR_CHECK(esp_lcd_new_panel_io_i80(i80_bus, &io_config, &io_handle));

    ESP_LOGI(TAG, "Install LCD driver of nt35510");
    ESP_ERROR_CHECK(esp_lcd_new_panel_nt35510(io_handle, &panel_config, &panel_handle));

    esp_lcd_panel_reset(panel_handle);
    esp_lcd_panel_init(panel_handle);
    esp_lcd_panel_invert_color(panel_handle, true);
    // the gap is LCD panel specific, even panels with the same driver IC, can have different gap value
    esp_lcd_panel_set_gap(panel_handle, 0, 0);

    ESP_LOGI(TAG, "Turn on LCD backlight");
    gpio_set_level(LCD_BK_LIGHT_GPIO, LCD_GPIO_STATE_ON);

    ESP_LOGI(TAG, "Initialize LVGL library");
    lv_init();
    // alloc draw buffers used by LVGL
    // it's recommended to choose the size of the draw buffer(s) to be at least 1/10 screen sized
    lv_color_t *buf1 = heap_caps_malloc(LCD_H_RES * 20 * sizeof(lv_color_t), MALLOC_CAP_DMA);
    assert(buf1);
    lv_color_t *buf2 = heap_caps_malloc(LCD_H_RES * 20 * sizeof(lv_color_t), MALLOC_CAP_DMA);
    assert(buf2);
    // initialize LVGL draw buffers
    lv_disp_draw_buf_init(&disp_buf, buf1, buf2, LCD_H_RES * 20);

    ESP_LOGI(TAG, "Register display driver to LVGL");
    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res = LCD_H_RES;
    disp_drv.ver_res = LCD_V_RES;
    disp_drv.flush_cb = lvgl_flush_cb;
    disp_drv.draw_buf = &disp_buf;
    disp_drv.user_data = panel_handle;
    lv_disp_t *disp = lv_disp_drv_register(&disp_drv);

    ESP_LOGI(TAG, "Install LVGL tick timer");
    // Tick interface for LVGL (using esp_timer to generate 2ms periodic event)
    const esp_timer_create_args_t lvgl_tick_timer_args = {
        .callback = &lvgl_tick_increase,
        .name = "lvgl_tick"
    };
    esp_timer_handle_t lvgl_tick_timer = NULL;
    ESP_ERROR_CHECK(esp_timer_create(&lvgl_tick_timer_args, &lvgl_tick_timer));
    ESP_ERROR_CHECK(esp_timer_start_periodic(lvgl_tick_timer, LVGL_TICK_PERIOD_MS * 1000));

    ESP_LOGI(TAG, "Display LVGL animation");
    // lv_obj_t *scr = lv_disp_get_scr_act(disp);
    // example_lvgl_demo_ui(scr);
    ui_init();

    xTaskCreate(lcd_task_handler, "lcd_task_handler", 4096, NULL, 6, NULL);
    return ESP_OK;
}