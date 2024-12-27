
#include "main.h"

#define SYSTEM_BUFFER_SIZE 4
#define SYSTEM_ROTARY_ENCODER_STEP_SIZE 4
#define SYSTEM_LAMP_MODE_COUNT 3

static void lvgl_time_task(void *param);

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


	gc9a01_displayInit();
	displayConfig();
	systimer_init();
	xTaskCreatePinnedToCore(lvgl_time_task, "lvgl_time_task", 10000, NULL, 4, NULL, 1);
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
