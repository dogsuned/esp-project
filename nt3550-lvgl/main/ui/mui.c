// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.0.5
// LVGL VERSION: 8.2
// PROJECT: SquareLine_Project

#include "mui.h"
#include "mui_helpers.h"

///////////////////// VARIABLES ////////////////////
lv_obj_t * ui_Screen1;
lv_obj_t * ui_SpCenter;
lv_obj_t * ui_CwCenter;
lv_obj_t * ui_TextHW;
lv_obj_t * ui_BT1;
lv_obj_t * ui_TextArea2;

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 16
    #error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
#endif
#if LV_COLOR_16_SWAP !=0
    #error "#error LV_COLOR_16_SWAP should be 0 to match SquareLine Studio's settings"
#endif

///////////////////// ANIMATIONS ////////////////////

///////////////////// FUNCTIONS ////////////////////

///////////////////// SCREENS ////////////////////
void ui_Screen1_screen_init(void)
{

    // ui_Screen1

    ui_Screen1 = lv_obj_create(NULL);

    lv_obj_clear_flag(ui_Screen1, LV_OBJ_FLAG_SCROLLABLE);

    // ui_SpCenter

    ui_SpCenter = lv_spinner_create(ui_Screen1, 1000, 90);

    lv_obj_set_width(ui_SpCenter, 200);
    lv_obj_set_height(ui_SpCenter, 200);

    lv_obj_set_x(ui_SpCenter, 0);
    lv_obj_set_y(ui_SpCenter, 0);

    lv_obj_set_align(ui_SpCenter, LV_ALIGN_CENTER);

    lv_obj_clear_flag(ui_SpCenter, LV_OBJ_FLAG_CLICKABLE);

    // ui_CwCenter

    ui_CwCenter = lv_colorwheel_create(ui_Screen1, true);

    lv_obj_set_width(ui_CwCenter, 200);
    lv_obj_set_height(ui_CwCenter, 200);

    lv_obj_set_x(ui_CwCenter, -120);
    lv_obj_set_y(ui_CwCenter, 271);

    lv_obj_set_align(ui_CwCenter, LV_ALIGN_CENTER);

    // ui_TextHW

    ui_TextHW = lv_textarea_create(ui_Screen1);

    lv_obj_set_width(ui_TextHW, 150);
    lv_obj_set_height(ui_TextHW, 70);

    lv_obj_set_x(ui_TextHW, -115);
    lv_obj_set_y(ui_TextHW, -229);

    lv_obj_set_align(ui_TextHW, LV_ALIGN_CENTER);

    // if("" == "") lv_textarea_set_accepted_chars(ui_TextHW, NULL);
    if(1) lv_textarea_set_accepted_chars(ui_TextHW, NULL);
    else lv_textarea_set_accepted_chars(ui_TextHW, "");

    lv_textarea_set_text(ui_TextHW, "Hello World!\n2022/06/28");
    lv_textarea_set_placeholder_text(ui_TextHW, "Placeholder...");

    lv_obj_set_style_text_font(ui_TextHW, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_BT1

    ui_BT1 = lv_btn_create(ui_Screen1);

    lv_obj_set_width(ui_BT1, 100);
    lv_obj_set_height(ui_BT1, 50);

    lv_obj_set_x(ui_BT1, 110);
    lv_obj_set_y(ui_BT1, -303);

    lv_obj_set_align(ui_BT1, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_BT1, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_clear_flag(ui_BT1, LV_OBJ_FLAG_SCROLLABLE);

    // ui_TextArea2

    ui_TextArea2 = lv_textarea_create(ui_Screen1);

    lv_obj_set_width(ui_TextArea2, 150);
    lv_obj_set_height(ui_TextArea2, 70);

    lv_obj_set_x(ui_TextArea2, 121);
    lv_obj_set_y(ui_TextArea2, 227);

    lv_obj_set_align(ui_TextArea2, LV_ALIGN_CENTER);

    // if("" == "") lv_textarea_set_accepted_chars(ui_TextArea2, NULL);
    if(1) lv_textarea_set_accepted_chars(ui_TextArea2, NULL);
    else lv_textarea_set_accepted_chars(ui_TextArea2, "");

    lv_textarea_set_text(ui_TextArea2, "My name is Allen");
    lv_textarea_set_placeholder_text(ui_TextArea2, "Placeholder...");

    lv_obj_set_style_text_font(ui_TextArea2, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);

}

void ui_init(void)
{
    lv_disp_t * dispp = lv_disp_get_default();
    lv_theme_t * theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
                                               true, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    ui_Screen1_screen_init();
    lv_disp_load_scr(ui_Screen1);
}

