#include "led.h"


void LED_Init()
{
	LED_Disp(0x00);
	HAL_Delay(500);
	LED_Disp(0xFF);
	HAL_Delay(500);
	LED_Disp(0x00);
	HAL_Delay(500);
	
	LED_Disp(0xFF);
	HAL_Delay(500);
	LED_Disp(0x00);
	HAL_Delay(500);
}

void LED_Disp(uint8_t dsLED)
{
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_All, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOC, dsLED << 8, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, GPIO_PIN_RESET);
}

