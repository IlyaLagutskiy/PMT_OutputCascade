/*
 * System.c
 *
 *  Created on: 7 апр. 2019 г.
 *      Author: ilyal
 */

#include "System.h"

StateData System_Check()
{
	StateData data;

	return data;
}

void System_Error()
{
	HAL_GPIO_WritePin(FAIL_GPIO_Port, FAIL_Pin, GPIO_PIN_SET);
}

uint16_t System_GetIndTemp()
{
	uint16_t temp;
	uint32_t adc = ADCData[1];
	temp = adc/4096*3.3/IND_Sensitivity + IND_Zero;
	return temp;
}

uint16_t System_GetPcbTemp()
{
	uint16_t temp;
	uint32_t adc = ADCData[0];
	temp = adc/4096*3.3/PCB_Sensitivity + PCB_Zero;
	return temp;
}

void HAL_COMP_TriggerCallback(COMP_HandleTypeDef *hcomp)
{
	if(HAL_COMP_GetState(&hcomp1))
		VOL_OutOfRange = 0xFF;
	else
		VOL_OutOfRange = 0x00;
}
