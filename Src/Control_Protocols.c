/*
 * Control_Protocols.c
 *
 *  Created on: 3 апр. 2019 г.
 *      Author: ilyal
 */

#include "Control_Protocols.h"

uint8_t ADC_OutOfRange = 0x00;

void Start_Protocol(StartParams params)
{
	HAL_GPIO_WritePin(BUCK_DIS_GPIO_Port, BUCK_DIS_Pin, GPIO_PIN_RESET);
	HAL_TIM_PWM_Start(&htim14, TIM_CHANNEL_1);

	HAL_GPIO_WritePin(DRIVER_DIS_GPIO_Port, DRIVER_DIS_Pin, GPIO_PIN_SET);
}

void Stop_Protocol()
{
	HAL_GPIO_WritePin(BUCK_DIS_GPIO_Port, BUCK_DIS_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(DRIVER_DIS_GPIO_Port, DRIVER_DIS_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(INHIBIT_GPIO_Port, INHIBIT_Pin, GPIO_PIN_RESET);
	HAL_TIM_PWM_Stop(&htim14, TIM_CHANNEL_1);
	HAL_TIM_PWM_Stop(&htim17, TIM_CHANNEL_1);
	TIM16->CCR1 = 800;
	HAL_ADC_Stop_DMA(&hadc);
}

void Change_Protocol(StartParams params)
{

}

void Pause_Protocol()
{

}

void Resume_Protocol()
{

}

void State_Protocol()
{

}

void EStop_Protocol()
{
	HAL_GPIO_WritePin(BUCK_DIS_GPIO_Port, BUCK_DIS_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(DRIVER_DIS_GPIO_Port, DRIVER_DIS_Pin, GPIO_PIN_SET);
}

void HAL_ADC_LevelOutOfWindowCallback(ADC_HandleTypeDef* hadc)
{
	ADC_OutOfRange = 0xFF;
}
