#include "hv_pump.h"

extern TIM_HandleTypeDef htim15;
extern ADC_HandleTypeDef hadc1;

bool HVpumpInit = false;
bool HVonePulse = false;
uint16_t adcHVvalue = 0;


void initHV()
{
	HAL_ADCEx_Calibration_Start(&hadc1, ADC_SINGLE_ENDED);
	startPump();
	do
	{
		if(HVpumpInit == true)
		{
			GPIO_To_ADC();
			startADC();
			if(adcHVvalue >= HV_REF_VALUE)
				break;
			else
			{
				HVpumpInit = false;
				startPump();
			}
		}

	}
	while(true);
}


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

void ADC_To_GPIO()
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    HAL_ADC_DeInit(&hadc1);
    // Настройка PA0 как выход (GPIO_OUTPUT)
    GPIO_InitStruct.Pin = GPIO_PIN_0;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_RESET);
}

void GPIO_To_ADC()
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    ADC_ChannelConfTypeDef sConfig = {0};

    HAL_GPIO_DeInit(GPIOC, GPIO_PIN_0);  // Деинициализация GPIO
    // Настройка PA0 как аналогового входа (режим для АЦП)
//    GPIO_InitStruct.Pin = GPIO_PIN_0;
//    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
//    GPIO_InitStruct.Pull = GPIO_NOPULL;
//    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);


    hadc1.Instance = ADC1;
      hadc1.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV1;
      hadc1.Init.Resolution = ADC_RESOLUTION_12B;
      hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
      hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
      hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
      hadc1.Init.LowPowerAutoWait = DISABLE;
      hadc1.Init.ContinuousConvMode = DISABLE;
      hadc1.Init.NbrOfConversion = 1;
      hadc1.Init.DiscontinuousConvMode = DISABLE;
      hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
      hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
      hadc1.Init.DMAContinuousRequests = DISABLE;
      hadc1.Init.Overrun = ADC_OVR_DATA_PRESERVED;
      hadc1.Init.OversamplingMode = DISABLE;
      if (HAL_ADC_Init(&hadc1) != HAL_OK)
      {
        Error_Handler();
      }

      sConfig.Channel = ADC_CHANNEL_1;
      sConfig.Rank = ADC_REGULAR_RANK_1;
      sConfig.SamplingTime = ADC_SAMPLETIME_2CYCLES_5;
      sConfig.SingleDiff = ADC_SINGLE_ENDED;
      sConfig.OffsetNumber = ADC_OFFSET_NONE;
      sConfig.Offset = 0;
      if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
      {
        Error_Handler();
      }
}
