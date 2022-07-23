#include <stdbool.h>
#include <nrf.h>
#include <zephyr.h>

#include "./touchscreen.h"
#include "./analog.h"
#include "./nrf52840_util.h"

//  Touchscreen driver
//  TODO: update these definitions
#define ADC_SIZE            1023
#define PRESS_THRESHOLD     10

#define TSCH_PORT           0

#define X_PLUS_PIN          4
#define X_MINUS_PIN         30
#define Y_PLUS_PIN          28
#define Y_MINUS_PIN         31
#define Y_PLUS_PIN_ANALOG   ANALIN_PORT_0_PIN_28
#define X_PLUS_PIN_ANALOG  ANALIN_PORT_0_PIN_4

#define MAX_SAMPLES         5

//  MIN & MAXES for touchscreen mapping
#define X_TCH_MAX   740    
#define X_TCH_MIN   200
#define Y_TCH_MAX   715
#define Y_TCH_MIN   354

#define SCREEN_WIDTH    480
#define SCREEN_LENGTH   320


static int map(int x, int in_min, int in_max, int out_min, int out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

static void reset_tsch_pins(void){
    //  reset configuration for analog pins
    remove_config_gpio(Y_PLUS_PIN, TSCH_PORT);
    remove_config_gpio(X_MINUS_PIN, TSCH_PORT);
    remove_config_gpio(Y_MINUS_PIN, TSCH_PORT);
    remove_config_gpio(X_PLUS_PIN, TSCH_PORT);
    remove_config_gpio_analog(Y_PLUS_PIN_ANALOG);
    remove_config_gpio_analog(X_PLUS_PIN_ANALOG);
}

static int get_x(void){
    int sum=0, i;
    reset_tsch_pins();

    config_gpio_input(X_MINUS_PIN, TSCH_PORT);

    config_gpio_output(Y_PLUS_PIN, TSCH_PORT);
    config_gpio_output(Y_MINUS_PIN, TSCH_PORT);

    config_gpio_analog(X_PLUS_PIN_ANALOG);

    PORT0_PIN_LOW(Y_MINUS_PIN);
    PORT0_PIN_HIGH(Y_PLUS_PIN);

    for(i=0; i< MAX_SAMPLES; i++){
        sum += read_gpio_analog(X_PLUS_PIN_ANALOG);
    }

    //  remove the configuration for x_minus
    remove_config_gpio_analog(X_PLUS_PIN_ANALOG);


    return map((sum / MAX_SAMPLES), X_TCH_MIN, X_TCH_MAX, 0, SCREEN_WIDTH);
}

static int get_y(void){
    int i, sum =0;

    reset_tsch_pins();

    //  read x
    config_gpio_input(Y_MINUS_PIN, TSCH_PORT);

    config_gpio_output(X_PLUS_PIN, TSCH_PORT);
    config_gpio_output(X_MINUS_PIN, TSCH_PORT);

    config_gpio_analog(Y_PLUS_PIN_ANALOG);

    PORT0_PIN_LOW(X_MINUS_PIN);
    PORT0_PIN_HIGH(X_PLUS_PIN);

    for(i=0; i< MAX_SAMPLES; i++){
        sum += read_gpio_analog(Y_PLUS_PIN_ANALOG);
    }

    //  remove the configuration for Y_plus
    remove_config_gpio_analog(Y_PLUS_PIN_ANALOG);

    return map((sum / MAX_SAMPLES), Y_TCH_MAX, Y_TCH_MIN, 0, SCREEN_LENGTH);
}

bool TchScrn_isPressed(void){
    //  X floats negative

    return get_x() > 0;
}

void TchScrn_getPoint(tchscrn_pnt_t * point_p){

    point_p->x = get_x();
    point_p->y = get_y();   
}