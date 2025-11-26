/**
  ******************************************************************************
  * @file    rotary_input.c
  * @author  Julius Sawilski
  * @brief   module designed to read input of photodyodes from pins PF0 and PF1.
             for additional information on the hardware specification consult
             "Anschluss_Drehgeber.pdf"
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/

#include <rotary_input.h>
#include <stm32f429xx.h>
#include <stm32f4xx_hal.h>

int readInput(void) {
    return GPIOF->IDR & 0x03;
} 

int buttonS6_pressed(void) {
    return !(GPIOF->IDR & (1 << 6));
} 