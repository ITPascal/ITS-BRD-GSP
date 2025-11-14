/**
  ******************************************************************************
  * @file    input.c
  * @author  Julius Sawilski
  * @brief   Modul für Input
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/

#include <stm32f4xx_hal.h>
#include <stm32f429xx.h>

#define MASK_F0 0x3 
#define MASK_F1 0x3 << 2

int initInput(void) {
    GPIOF -> MODER = GPIOF -> MODER & ~(MASK_F0 & MASK_F1);
}

// EOF
