
#include "main.h"

#define TAG "MAIN"
#define SYSTEM_BUFFER_SIZE 4
#define SYSTEM_ROTARY_ENCODER_STEP_SIZE 4
#define SYSTEM_LAMP_MODE_COUNT 3 // see lv_colorwheel_mode_t

static void lvgl_time_task(void *param);

void ble_recv_callback(uint8_t *data, uint16_t len)
{
	sign_handle(data, len);
}
void app_main(void)
{
	esp_err_t err;
	err = nvs_flash_init();
	if (err == ESP_ERR_NVS_NO_FREE_PAGES)
	{
		ESP_ERROR_CHECK(nvs_flash_erase());
		err = nvs_flash_init();
	}
	ESP_ERROR_CHECK(err);
	BLE_SERVER_INIT();
	ble_callback_register_callback(ble_recv_callback);

	// init_sound_spiffs();
	// speaker_config();
	// sap_toi_bien_toc_do_gioi_han_40();

	// sap_toi_bien_toc_do_gioi_han_50();

	// sap_toi_bien_toc_do_gioi_han_60();

	// sap_toi_bien_toc_do_gioi_han_70();

	// sap_toi_bien_toc_do_gioi_han_90();

	// sap_toi_bien_toc_do_gioi_han_100();

	// sap_toi_bien_toc_do_gioi_han_120();

	// sap_vao_khu_dan_cu();

	// sap_thoat_khoi_khu_dan_cu();

	// sap_toi_tram_thu_phi();

	// qua_toc_do_cho_phep();

	// het_duong_cam_vuot();

	// vao_duong_cam_vuot();

	// giam_toc_do_gioi_han();

	// co_camera_giao_thong();

	// beep();

	// camera_theo_doi_toc_do();

	// while(1){

	// }

	// gc9a01_displayInit();
	// displayConfig();
	// systimer_init();
	// xTaskCreatePinnedToCore(lvgl_time_task, "lvgl_time_task", 10000, NULL, 4, NULL, 1);
}

void lvgl_time_task(void *param)
{
	TickType_t xLastWakeTime = xTaskGetTickCount();

	while (1)
	{

		lv_timer_handler();
		vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(10));
	}
}
