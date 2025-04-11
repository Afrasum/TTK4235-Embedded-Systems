#include "gpio.h"

void button_init(void) { 
    GPIO->PIN_CNF[13] = (3 << 2);
    GPIO->PIN_CNF[14] = (3 << 2);
}
