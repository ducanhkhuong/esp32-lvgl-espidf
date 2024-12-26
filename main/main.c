/**
 ******************************************************************************
 *							USEFUL ELECTRONICS
 ******************************************************************************/
/**
 ******************************************************************************
 * @file    :  main.c
 * @author  :  WARD ALMASARANI
 * @version :  v.1.0
 * @date    :  Jan 30, 2023
 * @link    :  https://www.youtube.com/@usefulelectronics
 *			   Hold Ctrl button and click on the link to be directed to
			   Useful Electronics YouTube channel
 ******************************************************************************/

/* INCLUDES ------------------------------------------------------------------*/
#include "main.h"
// #include "extra/widgets/colorwheel/lv_colorwheel.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "gc9a01.h"
#include "lvgl_demo_ui.h"
#include "ui_helpers.h"

#include "time.h"
#include <math.h>
#include "systimer.h"

#include "gpio_config.h"
#include "esp_log.h"
#include <stdbool.h>
#include "freertos/queue.h"
#include "display.h"

/* MACROS --------------------------------------------------------------------*/
#define SYSTEM_BUFFER_SIZE 4
#define SYSTEM_ROTARY_ENCODER_STEP_SIZE 4
#define SYSTEM_LAMP_MODE_COUNT 3 // see lv_colorwheel_mode_t
/* DEFINITIONS ---------------------------------------------------------------*/

/* PRIVATE STRUCTRES ---------------------------------------------------------*/
typedef struct
{
	uint8_t packet_size;
	uint16_t data[SYSTEM_BUFFER_SIZE];
} system_packet;

typedef struct
{
	int16_t hue;
	int8_t saturation;
	int8_t brightness;
} system_hsv_t;

/* VARIABLES -----------------------------------------------------------------*/
char targetString[10] = {0};

static QueueHandle_t system_queue;

TaskHandle_t hMain_uiTask = NULL;
TaskHandle_t hMain_eventTask = NULL;
/* PRIVATE FUNCTIONS DECLARATION ---------------------------------------------*/

static void lvgl_time_task(void *param);

/* FUNCTION PROTOTYPES -------------------------------------------------------*/
/**
 * @brief 	Initialize system peripherals and create FreeRTOS tasks
 *
 */
void app_main(void)
{
	gc9a01_displayInit();
	displayConfig();
	systimer_init();
	system_queue = xQueueCreate(10, sizeof(system_packet));
	xTaskCreatePinnedToCore(lvgl_time_task, "lvgl_time_task", 10000, NULL, 4, NULL, 1);
}
/**
 * @brief 	LVGL library timer task. Necessary to run once every 10ms
 *
 */
void lvgl_time_task(void *param)
{
	TickType_t xLastWakeTime = xTaskGetTickCount();

	while (1)
	{

		lv_timer_handler();
		vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(10));
	}
}
