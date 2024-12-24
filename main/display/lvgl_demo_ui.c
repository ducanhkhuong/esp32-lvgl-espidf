/*
 * SPDX-FileCopyrightText: 2021-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

// This demo UI is adapted from LVGL official example: https://docs.lvgl.io/master/widgets/extra/meter.html#simple-meter

#include "lvgl_demo_ui.h"
#include "core/lv_obj.h"
#include "extra/widgets/colorwheel/lv_colorwheel.h"

static lv_style_t bgStyle;

watch_t realTime = {0};

lv_obj_t *dis;
lv_obj_t *ui_label;
void example_lvgl_demo_ui(lv_disp_t *disp)
{
    // Kiểm tra disp để tránh lỗi NULL
    if (disp == NULL)
    {
        return;
    }

    // Lấy màn hình mặc định từ disp
    lv_obj_t *scr = lv_disp_get_scr_act(disp);
    lv_obj_clean(scr);
    // Thiết lập phong cách cho màn hình chính (scr)
    lv_obj_set_style_bg_opa(scr, LV_OPA_90, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(scr, lv_color_hex(0x0000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_size(scr, 240, 240);

    // Tạo và cấu hình đối tượng arc trên màn hình chính
    lv_obj_t *arc = lv_arc_create(scr);
    lv_arc_set_mode(arc, LV_ARC_MODE_NORMAL);
    lv_arc_set_range(arc, 0, 100);
    lv_arc_set_bg_angles(arc, 135, 45);
    lv_arc_set_value(arc, 70);
    lv_arc_set_rotation(arc, 0);
    lv_obj_set_pos(arc, 19, 19);
    lv_obj_set_size(arc, 200, 200);

    // Cài đặt phong cách cho arc
    lv_obj_set_style_arc_width(arc, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_color(arc, lv_color_hex(0xe6e6e6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_width(arc, 12, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_color(arc, lv_color_hex(0x2195f6), LV_PART_INDICATOR | LV_STATE_DEFAULT);

    // Tạo và cấu hình nhãn trên màn hình chính
    lv_obj_t *label = lv_label_create(scr);
    lv_label_set_text(label, "15:00");
    lv_label_set_long_mode(label, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(label, 41, 105);
    lv_obj_set_size(label, 165, 42);

    // Cài đặt phong cách cho nhãn
    lv_obj_set_style_text_color(label, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(label, &lv_font_montserrat_40, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Xóa padding và shadow không cần thiết
    lv_obj_set_style_pad_all(label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Gắn màn hình (scr) vào bộ hiển thị
    lv_disp_load_scr(scr);
}
