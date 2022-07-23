#include <nrf.h>
#include <zephyr.h>
#include <kernel.h>
#include <stdint.h>

#include "penManager/penGUIn.h"
#include "hx8357D/nrf52840_util.h"

#include "./lvgl_master/lvgl.h"
#include "./lvgl_master/src/core/lv_obj.h"

#include "./hx8357D/tft.h"
#include "./lv_port_disp.h"
#include "./hx8357D/touchscreen.h"

#include "./hx8357D/analog.h"
#include "./hx8357D/spi_driver.h"

#define LV_CALLBACK_DELAY 5
#define MY_STACK_SIZE	  100


#define MISO_PIN 1
#define SPI_MOSI_PIN 5
#define SPI_SCK_PIN  0
#define SPI_CS_PIN   13



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

void my_input_read(lv_indev_drv_t * drv, lv_indev_data_t*data)
{
	tchscrn_pnt_t ts;
	
	if(TchScrn_isPressed()) {
		TchScrn_getPoint(&ts);
		data->point.x = ts.x;
		data->point.y = ts.y;
		data->state = LV_INDEV_STATE_PRESSED;
	} else {
		data->state = LV_INDEV_STATE_RELEASED;
	}
}

static void event_cb(lv_event_t * e)
{
    LV_LOG_USER("Clicked");

    static uint32_t cnt = 1;
    lv_obj_t * btn = lv_event_get_target(e);
    lv_obj_t * label = lv_obj_get_child(btn, 0);
    lv_label_set_text_fmt(label, "%"LV_PRIu32, cnt);
    cnt++;
}

void main(void)
{
	// lv_init();

	// lv_port_disp_init();
	// disp_enable_update();

	// //  port over input
	// static lv_indev_drv_t indev_drv;
	// lv_indev_drv_init(&indev_drv);      /*Basic initialization*/
	// indev_drv.type = LV_INDEV_TYPE_POINTER;                 /*See below.*/
	// indev_drv.read_cb =my_input_read;            /*See below.*/
	// /*Register the driver in LVGL and save the created input device object*/
	// lv_indev_t * my_indev = lv_indev_drv_register(&indev_drv);


	// //  end port over input

	// // spi_transceive


    // lv_obj_t * btn = lv_btn_create(lv_scr_act());
    // lv_obj_set_size(btn, 100, 50);
    // lv_obj_center(btn);
    // lv_obj_add_event_cb(btn, event_cb, LV_EVENT_CLICKED, NULL);

    // lv_obj_t * label = lv_label_create(btn);
    // lv_label_set_text(label, "Click me!");
    // lv_obj_center(label);

	// struct k_thread tick_thread;
	// // k_tid_t my_tid;

	// k_thread_create(&tick_thread, my_stack_area, MY_STACK_SIZE, lvgl_tick,
	// 	NULL, NULL, NULL, 4, 0,
	// 	K_NO_WAIT);
	printk("Hit fault\n");
	spi_settings_t my_sets;
	uint8_t * tx_buff = SPI_getTXBuff();
	uint8_t rx_buff[RX_TX_BUFFER_SIZE];
	int rx_size;

	my_sets.max_speed = M8;
	my_sets.data_order = MSB_FIRST;
	my_sets.data_mode = SPI_MODE_0;
	my_sets.gpio_port = 0;
	my_sets.miso_pin = MISO_PIN;
	my_sets.mosi_pin = SPI_MOSI_PIN;
	my_sets.sck_pin = SPI_SCK_PIN;
	my_sets.cs_pin = SPI_CS_PIN;

	SPI_init(&my_sets);

 
	while(1){
		tx_buff[0] = 3;
		tx_buff[1] = 4;


	// rx_buff[0] = 0;
	// rx_buff[1] = 0;



	// 	printk("byte 0:  %d   byte 1:  %d \n", rx_buff[0], rx_buff[1]);

	// SPI_init(&my_sets);

			SPI_transfer(rx_buff, &rx_size);


	// printk("End of sleep\n");

	printk("0 : %d   1:  %d\n",  rx_buff[0], rx_buff[1]);

	// SPI_stopTransfer();

	}

}