#include "rotary_led.h"
#include "stm32f4xx_hal.h"
#include "rotary_calculator.h"

void setLEDCounter(int phasencounter) {
    int on = phasencounter & 0xFF;
    int off = (~on) & 0xFF;

    GPIOD->BSRR = on | (off << 16);
}

void setErrorLED(){
    GPIOE->BSRR = 1 << 5;
}

void clearErrorLED(){
    GPIOE->BSRR = 1 << (5 + 16);
}

void setLEDDirection(int state)
{
    switch (state) {
        case STATE_FORWARD:
            GPIOE->BSRR = (1 << 7) | (1 << (6 + 16));
            break;
        case STATE_BACKWARDS:
            GPIOE->BSRR = (1 << 6) | (1 << (7 + 16));
            break;
    }
}




