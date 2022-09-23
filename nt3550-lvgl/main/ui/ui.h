// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.1.0
// LVGL VERSION: 8.2
// PROJECT: weather

#ifndef _WEATHER_UI_H
#define _WEATHER_UI_H

#ifdef __cplusplus
extern "C" {
#endif

#if defined __has_include
#if __has_include("lvgl.h")
#include "lvgl.h"
#elif __has_include("lvgl/lvgl.h")
#include "lvgl/lvgl.h"
#else
#include "lvgl.h"
#endif
#else
#include "lvgl.h"
#endif

void show_keyboard_Animation(lv_obj_t * TargetObject, int delay);
void hide_keyboard_Animation(lv_obj_t * TargetObject, int delay);
void show_calendar_Animation(lv_obj_t * TargetObject, int delay);
void hide_calendar_Animation(lv_obj_t * TargetObject, int delay);
void ui_event_scmain(lv_event_t * e);
extern lv_obj_t * ui_scmain;
extern lv_obj_t * ui_Calendar;
extern lv_obj_t * ui_lbtitle;
extern lv_obj_t * ui_Keyboard;


LV_IMG_DECLARE(ui_img_bg_png);    // assets\bg.png




void ui_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
