
#include "main.h"

#define TAG "MAIN"
#define SYSTEM_BUFFER_SIZE 4
#define SYSTEM_ROTARY_ENCODER_STEP_SIZE 4
#define SYSTEM_LAMP_MODE_COUNT 3 // see lv_colorwheel_mode_t

static void lvgl_time_task(void *param);

typedef struct
{
	uint8_t position_1;
	uint8_t position_2;
	uint8_t position_3;
	uint16_t distance_to_ps_2;
	uint16_t distance_to_ps_3;
} sign_display_on_watch_t;

sign_display_on_watch_t get_sign_display_on_watch(sign_data_t sign_data)
{
	sign_display_on_watch_t sign_display = {0};
	sign_display.position_1 = sign_data.current_speed.current_speed;

	if (sign_data.next_speed.next_speed == 0)
	{
		bool ps_2 = false;
		bool ps_3 = false;
		if (sign_data.traffic_sign.number_of_sign > 0)
		{
			for (int i = 0; i < sign_data.traffic_sign.number_of_sign; i++)
			{
				ESP_LOGW(TAG, "test");
				if (sign_data.traffic_sign.traffic_id_sign[i] == ID_TS_ENTER_URBAN_AREA ||
					sign_data.traffic_sign.traffic_id_sign[i] == ID_TS_EXIT_URBAN_AREA)
				{
					sign_display.position_2 = sign_data.traffic_sign.traffic_id_sign[i];
					sign_display.distance_to_ps_2 = sign_data.traffic_sign.distance[i][0] << 8 | sign_data.traffic_sign.distance[i][1];
					ps_2 = true;
				}
			}
		}
		if (sign_data.camera_sign.number_of_sign > 0)
		{
			for (int i = 0; i < sign_data.camera_sign.number_of_sign; i++)
			{
				if (ps_2 == false)
				{
					sign_display.position_2 = sign_data.camera_sign.traffic_id_sign[i];
					sign_display.distance_to_ps_2 = sign_data.camera_sign.distance[i][0] << 8 | sign_data.camera_sign.distance[i][1];
					ps_2 = true;
					goto next_camera_sign;
				}

				if (ps_2 == true && ps_3 == false)
				{
					sign_display.position_3 = sign_data.camera_sign.traffic_id_sign[i];
					sign_display.distance_to_ps_3 = sign_data.camera_sign.distance[i][0] << 8 | sign_data.camera_sign.distance[i][1];
					ps_3 = true;
				}
			next_camera_sign:
				ESP_LOGI(TAG, "next camera sign");
			}
		}

		if (sign_data.traffic_sign.number_of_sign > 0 && ps_3 == false)
		{
			for (int i = 0; i < sign_data.traffic_sign.number_of_sign; i++)
			{
				if (sign_data.traffic_sign.traffic_id_sign[i] != ID_TS_ENTER_URBAN_AREA &&
					sign_data.traffic_sign.traffic_id_sign[i] != ID_TS_EXIT_URBAN_AREA)
				{
					if (ps_2 == false)
					{
						sign_display.position_2 = sign_data.traffic_sign.traffic_id_sign[i];
						sign_display.distance_to_ps_2 = sign_data.traffic_sign.distance[i][0] << 8 | sign_data.traffic_sign.distance[i][1];
						ps_2 = true;
						goto next_traffic_sign;
					}

					if (ps_2 == true)
					{
						sign_display.position_3 = sign_data.traffic_sign.traffic_id_sign[i];
						sign_display.distance_to_ps_3 = sign_data.traffic_sign.distance[i][0] << 8 | sign_data.traffic_sign.distance[i][1];
						ps_3 = true;
					}
				next_traffic_sign:
					ESP_LOGI(TAG, "Go to next traffic sign");
				}
			}
		}

		if (sign_data.other_sign.number_of_sign > 0 && ps_3 == false)
		{
			for (int i = 0; i < sign_data.other_sign.number_of_sign; i++)
			{

				if (ps_2 == false)
				{
					sign_display.position_2 = sign_data.other_sign.traffic_id_sign[i];
					sign_display.distance_to_ps_2 = sign_data.other_sign.distance[i][0] << 8 | sign_data.other_sign.distance[i][1];
					ps_2 = true;
					goto next_other_sign;
				}

				if (ps_2 == true)
				{
					sign_display.position_3 = sign_data.other_sign.traffic_id_sign[i];
					sign_display.distance_to_ps_3 = sign_data.other_sign.distance[i][0] << 8 | sign_data.traffic_sign.distance[i][1];
					ps_3 = true;
				}
			next_other_sign:
				ESP_LOGI(TAG, "Go to next other sign");
			}
		}
	}
	else
	{
		sign_display.position_2 = sign_data.next_speed.next_speed;
		sign_display.distance_to_ps_2 = sign_data.next_speed.distance[0] << 8 | sign_data.next_speed.distance[1];
		bool sign_3 = false;
		// ESP_LOGI(TAG, "%d", )
		if (sign_data.traffic_sign.number_of_sign > 0)
		{
			for (int i = 0; i < sign_data.traffic_sign.number_of_sign; i++)
			{
				ESP_LOGW(TAG, "test");
				if (sign_data.traffic_sign.traffic_id_sign[i] == ID_TS_ENTER_URBAN_AREA ||
					sign_data.traffic_sign.traffic_id_sign[i] == ID_TS_EXIT_URBAN_AREA)
				{
					sign_display.position_3 = sign_data.traffic_sign.traffic_id_sign[i];
					sign_display.distance_to_ps_3 = sign_data.traffic_sign.distance[i][0] << 8 | sign_data.traffic_sign.distance[i][1];
					sign_3 = true;
				}
			}
		}
		ESP_LOGW(TAG, "Number of cam : %d", sign_data.camera_sign.number_of_sign);
		if (sign_data.camera_sign.number_of_sign > 0)
		{
			for (int i = 0; i < sign_data.camera_sign.number_of_sign; i++)
			{
				ESP_LOGI(TAG, "Check here, %d", sign_3);
				if (sign_3 == false)
				{
					ESP_LOGI(TAG, "Check here now");
					ESP_LOGI(TAG, "%d", sign_data.camera_sign.traffic_id_sign[i]);
					sign_display.position_3 = sign_data.camera_sign.traffic_id_sign[i];
					sign_display.distance_to_ps_3 = sign_data.camera_sign.distance[i][0] << 8 | sign_data.camera_sign.distance[i][1];
					sign_3 = true;
				}
			}
		}

		if (sign_data.traffic_sign.number_of_sign > 0 && sign_3 == false)
		{
			for (int i = 0; i < sign_data.traffic_sign.number_of_sign; i++)
			{
				if (sign_data.traffic_sign.traffic_id_sign[i] != ID_TS_ENTER_URBAN_AREA &&
					sign_data.traffic_sign.traffic_id_sign[i] != ID_TS_EXIT_URBAN_AREA)
				{
					if (sign_3 == false)
					{
						sign_display.position_3 = sign_data.traffic_sign.traffic_id_sign[i];
						sign_display.distance_to_ps_3 = sign_data.traffic_sign.distance[i][0] << 8 | sign_data.traffic_sign.distance[i][1];
						sign_3 = true;
					}
				}
			}
		}

		if (sign_data.other_sign.number_of_sign > 0 && sign_3 == false)
		{
			for (int i = 0; i < sign_data.other_sign.number_of_sign; i++)
			{

				if (sign_3 == false)
				{
					sign_display.position_3 = sign_data.other_sign.traffic_id_sign[i];
					sign_display.distance_to_ps_3 = sign_data.other_sign.distance[i][0] << 8 | sign_data.other_sign.distance[i][1];
					sign_3 = true;
				}
			}
		}
	}
	return sign_display;
}

void ble_recv_callback(uint8_t *data, uint16_t len)
{
	sign_data_t sign_data = sign_handle(data, len);
	sign_display_on_watch_t sign_display = get_sign_display_on_watch(sign_data);
	ESP_LOGI(TAG, "Position 1, sign id = %d", sign_display.position_1);
	ESP_LOGI(TAG, "position 2, sign_id = %d, distance = %d", sign_display.position_2, sign_display.distance_to_ps_2);
	ESP_LOGI(TAG, "position 3, sign_id = %d, distance = %d", sign_display.position_3, sign_display.distance_to_ps_3);
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
