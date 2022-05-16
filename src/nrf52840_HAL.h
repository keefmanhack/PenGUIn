#include <stdint.h>

#define MAX_ANALOG_INPUTS 8

void setAnalog(uint8_t input);
void unsetAnalog(uint8_t input);
int readAnalog(uint8_t input);