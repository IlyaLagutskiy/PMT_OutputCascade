/*
 * Control_Protocols.c
 *
 *  Created on: 3 ���. 2019 �.
 *      Author: ilyal
 */

#include "Control_Protocols.h"

uint8_t VOL_OutOfRange = 0x00;
uint8_t State;

void Start_Protocol(StartParams params)
{
	AWDG_Config(0,0);
	HAL_GPIO_WritePin(BUCK_DIS_GPIO_Port, BUCK_DIS_Pin, GPIO_PIN_RESET);
	HAL_TIM_PWM_Start(&htim14, TIM_CHANNEL_1);
	while (VOL_OutOfRange)
	{
		HAL_Delay(1);
	}
	HAL_GPIO_WritePin(DRIVER_DIS_GPIO_Port, DRIVER_DIS_Pin, GPIO_PIN_RESET);
	State = State_WORK;
}

void Stop_Protocol()
{
	State = State_WAIT;
	HAL_GPIO_WritePin(BUCK_DIS_GPIO_Port, BUCK_DIS_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(DRIVER_DIS_GPIO_Port, DRIVER_DIS_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(INHIBIT_GPIO_Port, INHIBIT_Pin, GPIO_PIN_RESET);
	HAL_TIM_PWM_Stop(&htim14, TIM_CHANNEL_1);
	HAL_TIM_PWM_Stop(&htim17, TIM_CHANNEL_1);
	CoolDown();
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
	State = State_ESTOP;
}

void CoolDown()
{
	State = State_COOLDOWN;

	State = State_WAIT;
}

void HAL_ADC_LevelOutOfWindowCallback(ADC_HandleTypeDef* hadc)
{
	VOL_OutOfRange = 0xFF;
}

void AWDG_Config(uint32_t High, uint32_t Low)
{
	  ADC_AnalogWDGConfTypeDef AnalogWDGConfig = {0};
	  AnalogWDGConfig.WatchdogMode = ADC_ANALOGWATCHDOG_SINGLE_REG;
	  AnalogWDGConfig.Channel = ADC_CHANNEL_8;
	  AnalogWDGConfig.ITMode = ENABLE;
	  AnalogWDGConfig.HighThreshold = High;
	  AnalogWDGConfig.LowThreshold = Low;
	  if (HAL_ADC_AnalogWDGConfig(&hadc, &AnalogWDGConfig) != HAL_OK)
	  {
	    Error_Handler();
	  }
}
