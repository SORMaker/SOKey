#ifndef _ISR_H
#define _ISR_H

#include "main.h"
#include "tim.h"
#include "key.h"


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);

#endif
