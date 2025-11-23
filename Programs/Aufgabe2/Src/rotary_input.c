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

#include <stdint.h>
#include <stm32f4xx_hal.h>
#include <stm32f429xx.h>
#include <rotary_input.h>

#define MODEM_F0 0x3 
#define MODEM_F1 0x3 << 2
#define IDR_F0 0x1
#define IDR_F1 0x2

void initInput(void) {
    GPIOF -> MODER = GPIOF -> MODER & ~(MODEM_F0 | MODEM_F1);
}

int readInput(uint32_t *in) {
    if (in == NULL) {
        return -1;
    }

    *in = (GPIOF->IDR) & (IDR_F0 | IDR_F1);
    return 0;
} 
// EOF
