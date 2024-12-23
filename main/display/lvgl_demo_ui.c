/*
 * SPDX-FileCopyrightText: 2021-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

// This demo UI is adapted from LVGL official example: https://docs.lvgl.io/master/widgets/extra/meter.html#simple-meter

#include "lvgl_demo_ui.h"
#include "core/lv_obj.h"
#include "extra/widgets/colorwheel/lv_colorwheel.h"


static void ui_screen_main(void);
static void ui_label_screen_init(void);


static lv_disp_t *lv_display;
static lv_style_t bgStyle;

static lv_color_hsv_t ui_color_wheel_obj = {0};

watch_t realTime = {0};

lv_obj_t *dis;
lv_obj_t * ui_label;



void example_lvgl_demo_ui(lv_disp_t *disp)
{
	 lv_color_t bgColor;
	lv_display = disp;
	
	lv_obj_t *scr = lv_disp_get_scr_act(disp);

	bgColor = lv_color_hex(0x101418);
	lv_style_init(&bgStyle);


	dis = lv_obj_create(NULL);
    lv_obj_set_size(dis, 240, 240);
    lv_obj_set_scrollbar_mode(dis, LV_SCROLLBAR_MODE_OFF);

    lv_obj_set_style_bg_opa(dis, 227, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(dis, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(dis, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    dis = lv_arc_create(dis);
    lv_arc_set_mode(dis, LV_ARC_MODE_NORMAL);
    lv_arc_set_range(dis, 0, 100);
    lv_arc_set_bg_angles(dis, 135, 45);
    lv_arc_set_value(dis, 70);
    lv_arc_set_rotation(dis, 0);
    lv_obj_set_style_arc_rounded(dis, 0,  LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_rounded(dis, 0, LV_STATE_DEFAULT);
    lv_obj_set_pos(dis, 0, 0);
    lv_obj_set_size(dis, 240, 240);

    lv_obj_set_style_bg_opa(dis, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(dis, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(dis, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(dis, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_width(dis, 12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(dis, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_color(dis, lv_color_hex(0xe6e6e6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(dis, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(dis, 20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(dis, 20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(dis, 20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(dis, 20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(dis, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    lv_obj_set_style_arc_width(dis, 12, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(dis, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_color(dis, lv_color_hex(0x2195f6), LV_PART_INDICATOR|LV_STATE_DEFAULT);

    lv_obj_set_style_bg_opa(dis, 255, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(dis, lv_color_hex(0x2195f6), LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(dis, LV_GRAD_DIR_NONE, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_all(dis, 5, LV_PART_KNOB|LV_STATE_DEFAULT);

	ui_label_screen_init();
}







static void ui_label_screen_init(void){
    ui_label = lv_label_create(dis);
    lv_label_set_text(ui_label, "15:00");
    lv_label_set_long_mode(ui_label, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_label, 41, 105);
    lv_obj_set_size(ui_label, 20, 20);

    lv_obj_set_style_border_width(ui_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui_label, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_label, &lv_font_montserrat_14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_label, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui_label, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
}