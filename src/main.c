#include <nrf.h>
#include <zephyr.h>
#include <kernel.h>

#include "penManager/penGUIn.h"
#include "hx8357D/nrf52840_util.h"

#include "./lvgl_master/lvgl.h"
#include "./lvgl_master/src/core/lv_obj.h"

#include "./hx8357D/tft.h"
#include "./lv_port_disp.h"
#include "./hx8357D/touchscreen.h"

#include "./hx8357D/analog.h"

#define LV_CALLBACK_DELAY 5
#define MY_STACK_SIZE	  100

K_THREAD_STACK_DEFINE(my_stack_area, MY_STACK_SIZE);

static void lv_callback(void){
	tchscrn_pnt_t	ts;
	
	lv_tick_inc(LV_CALLBACK_DELAY); 

	lv_timer_handler_run_in_period(LV_CALLBACK_DELAY);

	printk("is pressed: %d", TchScrn_isPressed());

	// printk("X: %d  Y: %d", ts.x, ts.y);

	// printk("Hello world");
}

static void lvgl_tick(void * a, void * b, void * c){
	static int64_t time_stamp, lv_callback_time;

	time_stamp = k_uptime_get();

	lv_callback_time = time_stamp + LV_CALLBACK_DELAY;

	while(1){
		time_stamp = k_uptime_get();
		
		if(time_stamp > lv_callback_time){
			lv_callback();

			lv_callback_time = time_stamp + LV_CALLBACK_DELAY;

			k_msleep(1);
		}
	}

	lv_callback_time = time_stamp + LV_CALLBACK_DELAY;
}

void main(void)
{
	// lv_init();

	// lv_port_disp_init();
	// disp_enable_update();


	//  lv_obj_t * scrn = lv_scr_act();

    // lv_obj_t * btn = lv_btn_create(lv_scr_act());     /*Add a button the current screen*/
    // lv_obj_set_pos(btn, 100, 100);                            /*Set its position*/
    // lv_obj_set_size(btn, 120, 50);                          /*Set its size*/
	// // lv_style_set_bg_color(btn->styles, lv_color_white());
    // // lv_obj_add_event_cb(btn, btn_event_cb, LV_EVENT_ALL, NULL);           /*Assign a callback to the button*/

    // lv_obj_t * label = lv_label_create(btn);          /*Add a label to the button*/
    // lv_label_set_text(label, "Button");                     /*Set the labels text*/
    // lv_obj_center(label);

	// struct k_thread tick_thread;
	// // k_tid_t my_tid;

	// k_thread_create(&tick_thread, my_stack_area, MY_STACK_SIZE, lvgl_tick,
	// 	NULL, NULL, NULL, 4, 0,
	// 	K_NO_WAIT);

	tchscrn_pnt_t	ts;
// config_gpio_analog(ANALIN_PORT_0_PIN_3);
// config_gpio_analog(ANALIN_PORT_0_PIN_4);

}