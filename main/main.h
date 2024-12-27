/**
 ******************************************************************************
 *							USEFUL ELECTRONICS
 ******************************************************************************/
/**
 ******************************************************************************
 * @file    :  main.h
 * @author  :  WARD ALMASARANI
 * @version :  v.1.0
 * @date    :  Jan 30, 2023
 * @link    :  https://www.youtube.com/@usefulelectronics
 *			   Hold Ctrl button and click on the link to be directed to
			   Useful Electronics YouTube channel
 ******************************************************************************/

#ifndef MAIN_MAIN_H_
#define MAIN_MAIN_H_

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
/* INCLUDES ------------------------------------------------------------------*/

#include <stdio.h>
#include <ctype.h>

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
#include "display.h"
#include "esp_err.h"
#include "nvs_flash.h"
#include "speaker_ns4168.h"
#include "ble_server_lib.h"
#include "id_sign.h"

/* MACROS --------------------------------------------------------------------*/
#define SYS_TICK() xTaskGetTickCount() * portTICK_PERIOD_MS



/* ENUMORATIONS --------------------------------------------------------------*/

/* STRUCTURES & TYPEDEFS -----------------------------------------------------*/

/* VARIABLES -----------------------------------------------------------------*/
extern TaskHandle_t hMain_uiTask;
extern TaskHandle_t hMain_eventTask;
/* FUNCTIONS DECLARATION -----------------------------------------------------*/

#endif /* MAIN_MAIN_H_ */

/*************************************** USEFUL ELECTRONICS*****END OF FILE****/
