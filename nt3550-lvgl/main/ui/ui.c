// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.1.0
// LVGL VERSION: 8.2
// PROJECT: weather

#include "ui.h"
#include "ui_helpers.h"

///////////////////// VARIABLES ////////////////////
void show_keyboard_Animation(lv_obj_t * TargetObject, int delay);
void hide_keyboard_Animation(lv_obj_t * TargetObject, int delay);
void show_calendar_Animation(lv_obj_t * TargetObject, int delay);
void hide_calendar_Animation(lv_obj_t * TargetObject, int delay);
void ui_event_handler(lv_event_t * e);
lv_obj_t * ui_scmain;
lv_obj_t * ui_Calendar;
lv_obj_t * ui_lbtitle;
lv_obj_t * ui_Keyboard;

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 16
    #error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
#endif
#if LV_COLOR_16_SWAP !=0
    #error "LV_COLOR_16_SWAP should be 0 to match SquareLine Studio's settings"
#endif

///////////////////// ANIMATIONS ////////////////////
void show_keyboard_Animation(lv_obj_t * TargetObject, int delay)
{
    lv_anim_t PropertyAnimation_0;
    lv_anim_init(&PropertyAnimation_0);
    lv_anim_set_time(&PropertyAnimation_0, 300);
    lv_anim_set_user_data(&PropertyAnimation_0, TargetObject);
    lv_anim_set_custom_exec_cb(&PropertyAnimation_0, _ui_anim_callback_set_y);
    lv_anim_set_values(&PropertyAnimation_0, 300, 180);
    lv_anim_set_path_cb(&PropertyAnimation_0, lv_anim_path_ease_in_out);
    lv_anim_set_delay(&PropertyAnimation_0, delay + 0);
    lv_anim_set_playback_time(&PropertyAnimation_0, 0);
    lv_anim_set_playback_delay(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_count(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_delay(&PropertyAnimation_0, 0);
    lv_anim_set_early_apply(&PropertyAnimation_0, false);
    lv_anim_start(&PropertyAnimation_0);

}
void hide_keyboard_Animation(lv_obj_t * TargetObject, int delay)
{
    lv_anim_t PropertyAnimation_0;
    lv_anim_init(&PropertyAnimation_0);
    lv_anim_set_time(&PropertyAnimation_0, 300);
    lv_anim_set_user_data(&PropertyAnimation_0, TargetObject);
    lv_anim_set_custom_exec_cb(&PropertyAnimation_0, _ui_anim_callback_set_y);
    lv_anim_set_values(&PropertyAnimation_0, 180, 300);
    lv_anim_set_path_cb(&PropertyAnimation_0, lv_anim_path_ease_in);
    lv_anim_set_delay(&PropertyAnimation_0, delay + 0);
    lv_anim_set_playback_time(&PropertyAnimation_0, 0);
    lv_anim_set_playback_delay(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_count(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_delay(&PropertyAnimation_0, 0);
    lv_anim_set_early_apply(&PropertyAnimation_0, false);
    lv_anim_start(&PropertyAnimation_0);

}
void show_calendar_Animation(lv_obj_t * TargetObject, int delay)
{
    lv_anim_t PropertyAnimation_0;
    lv_anim_init(&PropertyAnimation_0);
    lv_anim_set_time(&PropertyAnimation_0, 500);
    lv_anim_set_user_data(&PropertyAnimation_0, TargetObject);
    lv_anim_set_custom_exec_cb(&PropertyAnimation_0, _ui_anim_callback_set_y);
    lv_anim_set_values(&PropertyAnimation_0, 360, 120);
    lv_anim_set_path_cb(&PropertyAnimation_0, lv_anim_path_overshoot);
    lv_anim_set_delay(&PropertyAnimation_0, delay + 0);
    lv_anim_set_playback_time(&PropertyAnimation_0, 0);
    lv_anim_set_playback_delay(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_count(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_delay(&PropertyAnimation_0, 0);
    lv_anim_set_early_apply(&PropertyAnimation_0, false);
    lv_anim_start(&PropertyAnimation_0);

}
void hide_calendar_Animation(lv_obj_t * TargetObject, int delay)
{
    lv_anim_t PropertyAnimation_0;
    lv_anim_init(&PropertyAnimation_0);
    lv_anim_set_time(&PropertyAnimation_0, 500);
    lv_anim_set_user_data(&PropertyAnimation_0, TargetObject);
    lv_anim_set_custom_exec_cb(&PropertyAnimation_0, _ui_anim_callback_set_y);
    lv_anim_set_values(&PropertyAnimation_0, 120, 360);
    lv_anim_set_path_cb(&PropertyAnimation_0, lv_anim_path_ease_out);
    lv_anim_set_delay(&PropertyAnimation_0, delay + 0);
    lv_anim_set_playback_time(&PropertyAnimation_0, 0);
    lv_anim_set_playback_delay(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_count(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_delay(&PropertyAnimation_0, 0);
    lv_anim_set_early_apply(&PropertyAnimation_0, false);
    lv_anim_start(&PropertyAnimation_0);

}

///////////////////// FUNCTIONS ////////////////////
void ui_event_handler(lv_event_t * e)
{
    uint32_t idx;
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);

    if (event_code == LV_EVENT_CLICKED) {
        idx = (uint32_t)(e->user_data);
        switch (idx) {
            case 0:
                show_keyboard_Animation(ui_Keyboard, 0);
                break;
            case 1:
                hide_keyboard_Animation(ui_Keyboard, 0);
                break;
            case 2:
                show_calendar_Animation(ui_Calendar, 0);
                break;
            case 3:
                hide_calendar_Animation(ui_Calendar, 0);
                break;
            default:
                break;
        }
    }
}

///////////////////// SCREENS ////////////////////
void ui_scmain_screen_init(void)
{
    ui_scmain = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_scmain, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_img_src(ui_scmain, &ui_img_bg_png, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Calendar = lv_calendar_create(ui_scmain);
    lv_obj_set_size(ui_Calendar, lv_pct(30), lv_pct(50));  // force: 280
    lv_obj_align(ui_Calendar, LV_ALIGN_CENTER, 280, 360);

    ui_lbtitle = lv_label_create(ui_scmain);
    lv_obj_set_width(ui_lbtitle, 800);
    lv_obj_set_height(ui_lbtitle, 24);
    lv_obj_set_x(ui_lbtitle, 0);
    lv_obj_set_y(ui_lbtitle, -228);
    lv_obj_set_align(ui_lbtitle, LV_ALIGN_CENTER);
    lv_label_set_text(ui_lbtitle, "2022/9/23  22:00");
    lv_obj_set_style_text_color(ui_lbtitle, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_lbtitle, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_lbtitle, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_lbtitle, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_lbtitle, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Keyboard = lv_keyboard_create(ui_scmain);
    lv_obj_set_height(ui_Keyboard, 120);
    lv_obj_set_width(ui_Keyboard, lv_pct(50));
    lv_obj_set_x(ui_Keyboard, 0);
    lv_obj_set_y(ui_Keyboard, 300);
    lv_obj_set_align(ui_Keyboard, LV_ALIGN_CENTER);
    lv_obj_set_style_radius(ui_Keyboard, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Keyboard, lv_color_hex(0xEC7440), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Keyboard, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // lv_obj_add_event_cb(ui_scmain, ui_event_handler, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_Keyboard, ui_event_handler, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(ui_Calendar, ui_event_handler, LV_EVENT_CLICKED, NULL);
}

void ui_init(void)
{
    lv_disp_t * dispp = lv_disp_get_default();
    lv_theme_t * theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
                                               false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    ui_scmain_screen_init();
    lv_disp_load_scr(ui_scmain);
}
