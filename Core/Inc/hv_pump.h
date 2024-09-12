#ifndef __HV_PUMP__
#define __HV_PUMP_

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32l4xx.h"
#include "stdbool.h"
#include "main.h"

#define HV_REF_VALUE 1500

#define COUNTER_ENABLE_PORT GPIOC
#define COUNTER_ENABLE_PIN  GPIO_PIN_13

#define EN  1
#define DISAB 0

void startPump();
void stopPump();

void startADC();
void stopADC();

uint16_t measureHV();
void initHV();

void ADC_To_GPIO();
void GPIO_To_ADC();

#endif
