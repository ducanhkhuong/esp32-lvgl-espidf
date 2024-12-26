/**
 ******************************************************************************
 *							USEFUL ELECTRONICS
 ******************************************************************************/
/**
 ******************************************************************************
 * @file    :  lvgl_demo_ui.h
 * @author  :  WARD ALMASARANI
 * @version :  v.1.0
 * @date    :  Feb 1, 2023
 * @link    :  https://www.youtube.com/@usefulelectronics
 *			   Hold Ctrl button and click on the link to be directed to
			   Useful Electronics YouTube channel	
 ******************************************************************************/

#ifndef MAIN_LVGL_DEMO_UI_H_
#define MAIN_LVGL_DEMO_UI_H_


/* INCLUDES ------------------------------------------------------------------*/
#include "lvgl.h"
#include "core/lv_obj.h"
#include "extra/widgets/colorwheel/lv_colorwheel.h"
/* MACROS --------------------------------------------------------------------*/

/* ENUMORATIONS --------------------------------------------------------------*/

/* STRUCTURES & TYPEDEFS -----------------------------------------------------*/
typedef union
{
	char time[6];
	struct
	{
		uint16_t hour;
		uint8_t  semi;
		uint16_t minute;
		uint8_t  reserved;
	}sel;
}watch_t;

/* VARIABLES -----------------------------------------------------------------*/



/* FUNCTIONS DECLARATION -----------------------------------------------------*/
void ui_init(void);



#endif /* MAIN_LVGL_DEMO_UI_H_ */

/*************************************** USEFUL ELECTRONICS*****END OF FILE****/
