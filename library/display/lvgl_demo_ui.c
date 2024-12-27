//--------------------------------------------------------------------//

#include "lvgl_demo_ui.h"
#include "esp_log.h"
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"


static const char *TAG = "lvgl_demo_ui.c";

//image
#include "../img/notright.c"
#include "../img/khudancu.c"
#include "../img/tocdo90.c"
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
    lv_obj_set_style_bg_color(scr, lv_color_hex(0x130709), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_size(scr, 240, 240);
    ESP_LOGI(TAG, "Loading screen");

    lv_obj_t *img = lv_img_create(scr);
    lv_img_set_src(img, &tocdo90);
    lv_img_set_pivot(img, 50,50);
    lv_img_set_angle(img, 0);
    lv_obj_set_pos(img, 81, 158);
    lv_obj_set_size(img, 80, 80);
    lv_obj_set_style_radius(img, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(img, true, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(img, LV_OPA_COVER, LV_PART_MAIN | LV_STATE_DEFAULT);

    

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
    lv_arc_set_range(arc, 10, 130);
    lv_arc_set_bg_angles(arc, 135, 45);
    lv_arc_set_value(arc, 40);
    lv_arc_set_rotation(arc, 0);
    lv_obj_set_pos(arc, 17, 17);
    lv_obj_set_size(arc, 190, 190);
    lv_obj_remove_style(arc, NULL, LV_PART_KNOB);
    lv_obj_center(arc);
    lv_obj_add_event_cb()

    lv_obj_t *label2 = lv_label_create(scr);
    lv_label_set_text(label2, "10");
    lv_label_set_long_mode(label2, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(label2,20,172);
    lv_obj_set_size(label2,30,30);
    lv_obj_set_style_text_color(label2, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(label2, &lumi_font_helvetica_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(label2, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *label3 = lv_label_create(scr);
    lv_label_set_text(label3, "20");
    lv_label_set_long_mode(label3, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(label3,6,137);
    lv_obj_set_size(label3,30,30);
    lv_obj_set_style_text_color(label3, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(label3, &lumi_font_helvetica_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(label3, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *label4 = lv_label_create(scr);
    lv_label_set_text(label4, "30");
    lv_label_set_long_mode(label4, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(label4,2,99);
    lv_obj_set_size(label4,30,30);
    lv_obj_set_style_text_color(label4, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(label4, &lumi_font_helvetica_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(label4, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN   | LV_STATE_DEFAULT);

    lv_obj_t *label5 = lv_label_create(scr);
    lv_label_set_text(label5, "40");
    lv_label_set_long_mode(label5, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(label5,11,62);
    lv_obj_set_size(label5,30,30);
    lv_obj_set_style_text_color(label5, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(label5, &lumi_font_helvetica_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(label5, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN   | LV_STATE_DEFAULT);

    lv_obj_t *label6 = lv_label_create(scr);
    lv_label_set_text(label6, "50");
    lv_label_set_long_mode(label6, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(label6,35,28);
    lv_obj_set_size(label6,30,30);
    lv_obj_set_style_text_color(label6, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(label6, &lumi_font_helvetica_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(label6, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN   | LV_STATE_DEFAULT);

    lv_obj_t *label7 = lv_label_create(scr);
    lv_label_set_text(label7, "60");
    lv_label_set_long_mode(label7, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(label7,73,5);
    lv_obj_set_size(label7,30,30);
    lv_obj_set_style_text_color(label7, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(label7, &lumi_font_helvetica_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(label7, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN   | LV_STATE_DEFAULT);

    lv_obj_t *label8 = lv_label_create(scr);
    lv_label_set_text(label8, "70");
    lv_label_set_long_mode(label8, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(label8,110,-2);
    lv_obj_set_size(label8,30,30);
    lv_obj_set_style_text_color(label8, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(label8, &lumi_font_helvetica_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(label8, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN   | LV_STATE_DEFAULT);

    lv_obj_t *label9 = lv_label_create(scr);//80
    lv_label_set_text(label9, "80");
    lv_label_set_long_mode(label9, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(label9,130,5);
    lv_obj_set_size(label9,40,40);
    lv_obj_set_style_text_color(label9, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(label9, &lumi_font_helvetica_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(label9, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);


    lv_obj_t *label10 = lv_label_create(scr);//90
    lv_label_set_text(label10, "90");
    lv_label_set_long_mode(label10, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(label10,163,28);
    lv_obj_set_size(label10,40,40);
    lv_obj_set_style_text_color(label10, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(label10, &lumi_font_helvetica_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(label10, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);


    lv_obj_t *label11 = lv_label_create(scr);//100
    lv_label_set_text(label11, "100");
    lv_label_set_long_mode(label11, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(label11,190,62);
    lv_obj_set_size(label11,40,40);
    lv_obj_set_style_text_color(label11, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(label11, &lumi_font_helvetica_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(label11, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);


    lv_obj_t *label12 = lv_label_create(scr);//110
    lv_label_set_text(label12, "110");
    lv_label_set_long_mode(label12, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(label12,200,99);
    lv_obj_set_size(label12,40,40);
    lv_obj_set_style_text_color(label12, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(label12, &lumi_font_helvetica_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(label12, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *label13 = lv_label_create(scr);//120
    lv_label_set_text(label13, "120");
    lv_label_set_long_mode(label13, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(label13,196,137);
    lv_obj_set_size(label13,40,40);
    lv_obj_set_style_text_color(label13, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(label13, &lumi_font_helvetica_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(label13, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *label14 = lv_label_create(scr);//130
    lv_label_set_text(label14, "130");
    lv_label_set_long_mode(label14, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(label14,182,172);
    lv_obj_set_size(label14,40,40);
    lv_obj_set_style_text_color(label14, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(label14, &lumi_font_helvetica_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(label14, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_disp_load_scr(scr);
}
