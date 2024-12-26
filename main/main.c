
#include "main.h"

#define SYSTEM_BUFFER_SIZE 4
#define SYSTEM_ROTARY_ENCODER_STEP_SIZE 4
#define SYSTEM_LAMP_MODE_COUNT 3 // see lv_colorwheel_mode_t

static void lvgl_time_task(void *param);

void app_main(void)
{
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
