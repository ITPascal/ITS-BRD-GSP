/**
  ******************************************************************************
  * @file    rotary_input.c
  * @author  Julius Sawilski & Paskal Sendecky
  * @brief   module designed to read input of photodyodes from pins PF0 and PF1
             for further information regarding the intendet hardware consult
             "Anschluss_Drehgeber.pdf" and "nucleo-f429zi.pdf"
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

// EOF