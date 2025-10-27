#include "led.h"



void toggleGPIO(const GPIO_Pin* gpio) {
  HAL_GPIO_TogglePin(gpio->port, gpio->pin);
}