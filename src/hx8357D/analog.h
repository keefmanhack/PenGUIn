#include <stdint.h>

//  pin-port mappings for analog inputs
#define ANALIN_PORT_0_PIN_31    7
#define ANALIN_PORT_0_PIN_30    6
#define ANALIN_PORT_0_PIN_29    5
#define ANALIN_PORT_0_PIN_28    4
#define ANALIN_PORT_0_PIN_5     3
#define ANALIN_PORT_0_PIN_4     2
#define ANALIN_PORT_0_PIN_3     1
#define ANALIN_PORT_0_PIN_2     0

#define MAX_ANALOG_INPUTS       8

void config_gpio_analog(uint8_t input);
void remove_config_gpio_analog(uint8_t input);
int read_gpio_analog(uint8_t input);