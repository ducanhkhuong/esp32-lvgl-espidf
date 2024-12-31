
#include "main.h"

#define TAG "MAIN"
#define SYSTEM_BUFFER_SIZE 4
#define SYSTEM_ROTARY_ENCODER_STEP_SIZE 4
#define SYSTEM_LAMP_MODE_COUNT 3 // see lv_colorwheel_mode_t

static void lvgl_time_task(void *param);

typedef struct
{
	uint8_t current_speed;
} current_speed_t;

typedef struct
{
	uint8_t unique_id[3];
	uint8_t next_speed;
	uint8_t distance[2];
} next_speed_t;

typedef struct
{
	uint8_t number_of_sign;
	uint8_t unique_id[3][3];
	uint8_t traffic_id_sign[3];
	uint8_t distance[2][3];
} camera_sign_t;

typedef struct
{
	uint8_t number_of_sign;
	uint8_t unique_id[3][3];
	uint8_t traffic_id_sign[3];
	uint8_t distance[2][3];
} traffic_sign_t;

typedef struct
{
	uint8_t number_of_sign;
	uint8_t unique_id[3][3];
	uint8_t traffic_id_sign[3];
	uint8_t distance[2][3];
} other_sign_t;

typedef struct
{
	current_speed_t current_speed;
	next_speed_t next_speed;
	camera_sign_t camera_sign;
	traffic_sign_t traffic_sign;
	other_sign_t other_sign;

} sign_data_t;
void ble_recv_callback(uint8_t *data, uint16_t len)
{
	// priority
	// 1 - limit speed (current speed -> next speed)
	// 2 - enter or exit urban
	// 3 - camera
	// 4 - other

	bool next_speed = false;
	bool ex_traffic_sign = false;
	bool camera = false;
	bool other_sign = false;
	sign_data_t sign_data = {0}; // Initialize the structure to zero
	uint8_t offset = 0;
	if (data == NULL)
	{
		ESP_LOGE(TAG, "Received null data");
		return;
	}

	ESP_LOGI(TAG, "Data received:");
	for (uint16_t i = 0; i < len; i++)
	{
		ESP_LOGI(TAG, "Byte[%d]: 0x%02X", i, data[i]);
	}

	// Parse the data
	while (offset < len)
	{
		uint8_t header = data[offset];
		switch (header)
		{
		case HEADER_CURRENT_SPEED:
			sign_data.current_speed.current_speed = data[offset + 1];
			ESP_LOGI(TAG, "Current Speed: %d", sign_data.current_speed.current_speed);
			offset += 2; // Move to the next header
			break;

		case HEADER_NEXT_SPEED:
			memcpy(sign_data.next_speed.unique_id, &data[offset + 1], 3);
			sign_data.next_speed.next_speed = data[offset + 4];
			memcpy(sign_data.next_speed.distance, &data[offset + 5], 2);
			ESP_LOGI(TAG, "Next Speed Unique ID: 0x%02X%02X%02X",
					 sign_data.next_speed.unique_id[0],
					 sign_data.next_speed.unique_id[1],
					 sign_data.next_speed.unique_id[2]);
			ESP_LOGI(TAG, "Next Speed: %d, Distance: 0x%02X%02X",
					 sign_data.next_speed.next_speed,
					 sign_data.next_speed.distance[0],
					 sign_data.next_speed.distance[1]);
			offset += 7;
			break;

		case HEADER_CAMERA:
			sign_data.camera_sign.number_of_sign = data[offset + 1];
			if (sign_data.camera_sign.number_of_sign == 0)
			{
				ESP_LOGI(TAG, "Dont have camera");
				offset += 2;
			}
			offset += 2;
			for (int i = 0; i < sign_data.camera_sign.number_of_sign; i++)
			{
				memcpy(sign_data.camera_sign.unique_id[i], &data[offset], 3);
				sign_data.camera_sign.traffic_id_sign[i] = data[offset + 3];
				memcpy(sign_data.camera_sign.distance[i], &data[offset + 4], 2);
				offset += 6;
				ESP_LOGI(TAG, "Camera Sign[%d]: Unique ID: 0x%02X%02X%02X, Traffic ID: 0x%02X, Distance: 0x%02X%02X",
						 i + 1,
						 sign_data.camera_sign.unique_id[i][0],
						 sign_data.camera_sign.unique_id[i][1],
						 sign_data.camera_sign.unique_id[i][2],
						 sign_data.camera_sign.traffic_id_sign[i],
						 sign_data.camera_sign.distance[i][0],
						 sign_data.camera_sign.distance[i][1]);
			}
			break;

		case HEADER_TRAFFIC:
			sign_data.traffic_sign.number_of_sign = data[offset + 1];
			if (sign_data.traffic_sign.number_of_sign == 0)
			{
				ESP_LOGI(TAG, "Don't have traffic sign");
				offset += 2;
			}
			else
			{
				offset += 2;
				for (int i = 0; i < sign_data.traffic_sign.number_of_sign; i++)
				{
					memcpy(sign_data.traffic_sign.unique_id[i], &data[offset], 3);
					sign_data.traffic_sign.traffic_id_sign[i] = data[offset + 3];
					memcpy(sign_data.traffic_sign.distance[i], &data[offset + 4], 2);
					offset += 6;

					ESP_LOGI(TAG, "Traffic Sign[%d]: Unique ID: 0x%02X%02X%02X, Traffic ID: 0x%02X, Distance: 0x%02X%02X",
							 i + 1,
							 sign_data.traffic_sign.unique_id[i][0],
							 sign_data.traffic_sign.unique_id[i][1],
							 sign_data.traffic_sign.unique_id[i][2],
							 sign_data.traffic_sign.traffic_id_sign[i],
							 sign_data.traffic_sign.distance[i][0],
							 sign_data.traffic_sign.distance[i][1]);
				}
			}
			break;

		case HEADER_OTHER:
			sign_data.other_sign.number_of_sign = data[offset + 1];
			if (sign_data.other_sign.number_of_sign == 0)
			{
				ESP_LOGI(TAG, "Don't have other traffic sign");
				offset += 2;
			}
			else
			{
				offset += 2;
				for (int i = 0; i < sign_data.other_sign.number_of_sign; i++)
				{
					memcpy(sign_data.other_sign.unique_id[i], &data[offset], 3);
					sign_data.other_sign.traffic_id_sign[i] = data[offset + 3];
					memcpy(sign_data.other_sign.distance[i], &data[offset + 4], 2);
					offset += 6;

					ESP_LOGI(TAG, "Other Sign[%d]: Unique ID: 0x%02X%02X%02X, Traffic ID: 0x%02X, Distance: 0x%02X%02X",
							 i + 1,
							 sign_data.other_sign.unique_id[i][0],
							 sign_data.other_sign.unique_id[i][1],
							 sign_data.other_sign.unique_id[i][2],
							 sign_data.other_sign.traffic_id_sign[i],
							 sign_data.other_sign.distance[i][0],
							 sign_data.other_sign.distance[i][1]);
				}
			}
			break;

		default:
			// ESP_LOGW(TAG, "Unknown header: 0x%02X at offset %d", header, offset);
			offset++;
			break;
		}
	}

	ESP_LOGI(TAG, "Finished parsing BLE data.");
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
