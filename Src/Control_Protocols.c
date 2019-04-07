/*
 * Control_Protocols.c
 *
 *  Created on: 3 апр. 2019 г.
 *      Author: ilyal
 */

#include "Control_Protocols.h"

uint8_t VOL_OutOfRange = 0x00;
uint8_t State;

void Start_Protocol(StartParams params)
{
	System_Check();
	if (State == State_WAIT)
	{

		Driver_PWMConfig(params.Frequency);

		HAL_GPIO_WritePin(BUCK_DIS_GPIO_Port, BUCK_DIS_Pin, GPIO_PIN_RESET);
		HAL_TIM_PWM_Start(&htim14, TIM_CHANNEL_1);

		uint16_t counter = 0;
		while (VOL_OutOfRange)
		{
			HAL_Delay(1);
			++counter;
			if (counter > 5000)
			{
				State = State_BUCKFAIL;
				System_Error();
			}
		}

		HAL_TIM_PWM_Start(&htim17, TIM_CHANNEL_1);
		HAL_GPIO_WritePin(DRIVER_DIS_GPIO_Port, DRIVER_DIS_Pin, GPIO_PIN_RESET);

		State = State_WORK;
	}
	else
	{
		System_Error();
	}
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

void Pause_Protocol()
{
	HAL_GPIO_WritePin(BUCK_DIS_GPIO_Port, BUCK_DIS_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(DRIVER_DIS_GPIO_Port, DRIVER_DIS_Pin, GPIO_PIN_SET);
	HAL_TIM_PWM_Stop(&htim14, TIM_CHANNEL_1);
	HAL_TIM_PWM_Stop(&htim17, TIM_CHANNEL_1);
	State = State_PAUSE;
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

void Driver_PWMConfig(uint16_t freq)
{
	uint16_t psc;
	uint16_t arr;
	uint16_t ccr;
	if (freq >= 1 && freq <= 5)
		psc = 250;
	else if (freq >= 6 && freq <= 32)
		psc = 50;
	else
		psc = 10;
	arr = roundf(CLK / psc);
	ccr = CLK / 1000 / psc;
	TIM17->PSC = psc;
	TIM17->ARR = arr;
	TIM17->CCR1 = ccr;
}
