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
#include <stdint.h>
#include <stm32f429xx.h>
#include <stm32f4xx_hal.h>

#define MODEM_F0 0x3U
#define MODEM_F1 0x3U << 2
#define IDR_F0 0x1U
#define IDR_F1 0x2U

void initInput(void) {
  uint32_t test1 = (GPIOF->MODER);
  uint32_t test2 = ~(MODEM_F0 | MODEM_F1);
  uint32_t test3 = test1 & test2;

  GPIOF->MODER = test1;
}

int readInput(uint32_t *in) {
    if (in == NULL) {
        return -1;
    }
    *in = (GPIOF->IDR) & (IDR_F0 | IDR_F1);
    return 0;
} 
// EOF
