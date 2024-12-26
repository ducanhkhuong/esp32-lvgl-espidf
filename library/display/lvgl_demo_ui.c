//--------------------------------------------------------------------//

#include "lvgl_demo_ui.h"
#include "esp_log.h"
static const char *TAG = "lvgl_demo_ui.c";

//image
#include "../img/notright.c"

//font
#include "../font/lumi_font_helvetica_14.c"
#include "../font/lumi_font_helvetica_20.c"
#include "../font/lumi_font_helvetica_30.c"
#include "../font/lumi_font_helvetica_40.c"

watch_t realTime = {0};

void example_lvgl_demo_ui(lv_disp_t *disp)
{
    if (disp == NULL)
    {
        return;
        ESP_LOGE(TAG, "Display is NULL");           
    }

    lv_obj_t *scr = lv_disp_get_scr_act(disp);
    lv_obj_clean(scr);
    lv_obj_set_style_bg_opa(scr, LV_OPA_90, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(scr, lv_color_hex(0x2a323f), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_size(scr, 240, 240);
    ESP_LOGI(TAG, "Loading screen");

    lv_obj_t *img = lv_img_create(scr);
    lv_img_set_src(img, &notright);
    lv_img_set_pivot(img, 50,50);
    lv_img_set_angle(img, 0);
    lv_obj_set_pos(img, 81, 158);
    lv_obj_set_size(img, 80, 80);
    lv_obj_set_style_img_recolor_opa(img, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(img, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(img, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(img, false, LV_PART_MAIN|LV_STATE_DEFAULT);


    lv_obj_t *label = lv_label_create(scr);
    lv_label_set_text(label, "15:00");
    lv_label_set_long_mode(label, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(label, 60, 105);
    lv_obj_set_size(label, 120, 50);
    lv_obj_set_style_text_color(label, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(label, &lumi_font_helvetica_40, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *arc = lv_arc_create(scr);
    lv_arc_set_mode(arc, LV_ARC_MODE_NORMAL);
    lv_arc_set_range(arc, 0, 100);
    lv_arc_set_bg_angles(arc, 135, 45);
    lv_arc_set_value(arc, 70);
    lv_arc_set_rotation(arc, 0);
    lv_obj_set_pos(arc, 28, 25);
    lv_obj_set_size(arc, 180, 180);
    lv_obj_remove_style(arc, NULL, LV_PART_KNOB);
    lv_obj_center(arc);

    lv_obj_t *label2 = lv_label_create(scr);
    lv_label_set_text(label2, "10");
    lv_label_set_long_mode(label2, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(label2,17,168);
    lv_obj_set_size(label2,30,30);
    lv_obj_set_style_text_color(label2, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(label2, &lumi_font_helvetica_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(label2, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *label3 = lv_label_create(scr);
    lv_label_set_text(label3, "20");
    lv_label_set_long_mode(label3, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(label3,8,142);
    lv_obj_set_size(label3,30,30);
    lv_obj_set_style_text_color(label3, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(label3, &lumi_font_helvetica_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(label3, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *label4 = lv_label_create(scr);
    lv_label_set_text(label4, "30");
    lv_label_set_long_mode(label4, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(label4,0,113);
    lv_obj_set_size(label4,30,30);
    lv_obj_set_style_text_color(label4, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(label4, &lumi_font_helvetica_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(label4, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN   | LV_STATE_DEFAULT);

    lv_obj_t *label5 = lv_label_create(scr);
    lv_label_set_text(label5, "40");
    lv_label_set_long_mode(label5, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(label5,6,74);
    lv_obj_set_size(label5,30,30);
    lv_obj_set_style_text_color(label5, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(label5, &lumi_font_helvetica_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(label5, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN   | LV_STATE_DEFAULT);

    lv_obj_t *label6 = lv_label_create(scr);
    lv_label_set_text(label6, "50");
    lv_label_set_long_mode(label6, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(label6,25,40);
    lv_obj_set_size(label6,30,30);
    lv_obj_set_style_text_color(label6, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(label6, &lumi_font_helvetica_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(label6, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN   | LV_STATE_DEFAULT);

    lv_obj_t *label7 = lv_label_create(scr);
    lv_label_set_text(label7, "60");
    lv_label_set_long_mode(label7, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(label7,64,13);
    lv_obj_set_size(label7,30,30);
    lv_obj_set_style_text_color(label7, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(label7, &lumi_font_helvetica_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(label7, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN   | LV_STATE_DEFAULT);

    lv_obj_t *label8 = lv_label_create(scr);
    lv_label_set_text(label8, "70");
    lv_label_set_long_mode(label8, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(label8,110,2);
    lv_obj_set_size(label8,30,30);
    lv_obj_set_style_text_color(label8, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(label8, &lumi_font_helvetica_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(label8, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN   | LV_STATE_DEFAULT);

    lv_disp_load_scr(scr);
}
