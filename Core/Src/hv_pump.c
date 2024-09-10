#include "hv_pump.h"

extern TIM_HandleTypeDef htim15;
extern ADC_HandleTypeDef hadc1;


void startPump()
{
	HAL_TIM_PWM_Start_IT(&htim15, TIM_CHANNEL_1);
	//HAL_GPIO_WritePin(COUNTER_ENABLE_PORT, COUNTER_ENABLE_PIN, DISAB);
}

void stopPump()
{
	HAL_TIM_PWM_Stop_IT(&htim15, TIM_CHANNEL_1);
	//HAL_GPIO_WritePin(COUNTER_ENABLE_PORT, COUNTER_ENABLE_PIN, EN);
}

void startADC()
{
	HAL_ADC_Start_IT(&hadc1);
}

void stopADC()
{
	HAL_ADC_Stop_IT(&hadc1);
}

uint16_t measureHV()
{
	return HAL_ADC_GetValue(&hadc1);
}
