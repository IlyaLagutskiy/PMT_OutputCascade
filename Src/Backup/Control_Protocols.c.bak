/*
 * Control_Protocols.c
 *
 *  Created on: 3 апр. 2019 г.
 *      Author: ilyal
 */

#include "Control_Protocols.h"
#include "UART_Protocol.h"
#include "System.h"

uint8_t VOL_OutOfRange = 0x00;
uint8_t IND_OutOfRange = 0x00;
uint8_t PCB_OutOfRange = 0x00;
uint8_t State;

void Start_Protocol(StartParams params)
{
	System_Check();
	if (State == State_WAIT)
	{
		HAL_GPIO_WritePin(INHIBIT_GPIO_Port, INHIBIT_Pin, GPIO_PIN_SET);
		HAL_TIM_PWM_Start_IT(&htim16, TIM_CHANNEL_1);
		Driver_PWMConfig(params.Frequency);
		Buck_DACConfig(params.Amplitude);
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
				return;
			}
		}

		HAL_TIM_PWM_Start(&htim17, TIM_CHANNEL_1);
		HAL_GPIO_WritePin(DRIVER_DIS_GPIO_Port, DRIVER_DIS_Pin, GPIO_PIN_RESET);

		State = State_WORK;
	}
	else
	{
		System_Error();
		return;
	}
}

void Stop_Protocol()
{
	Pause_Protocol();
	HAL_GPIO_WritePin(INHIBIT_GPIO_Port, INHIBIT_Pin, GPIO_PIN_RESET);
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
	HAL_GPIO_WritePin(BUCK_DIS_GPIO_Port, BUCK_DIS_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(DRIVER_DIS_GPIO_Port, DRIVER_DIS_Pin, GPIO_PIN_RESET);
	HAL_TIM_PWM_Start(&htim14, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim17, TIM_CHANNEL_1);
	State = State_WORK;
}

void State_Protocol()
{
	StateData data = System_Check();
	UART_Send(Main_Addr, Command_STATE, (uint8_t*) &data, 6);
}

void EStop_Protocol()
{
	HAL_GPIO_WritePin(BUCK_DIS_GPIO_Port, BUCK_DIS_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(DRIVER_DIS_GPIO_Port, DRIVER_DIS_Pin, GPIO_PIN_SET);
	State = State_ESTOP;
}

void Reset_Protocol()
{
	HAL_GPIO_WritePin(FAIL_GPIO_Port, FAIL_Pin, GPIO_PIN_RESET);
	Stop_Protocol();
}

void CoolDown()
{
	State = State_COOLDOWN;
	TIM16->CCR1 = TIM16->ARR-1;
	while (PCB_OutOfRange)
	{
		HAL_Delay(1000);
	}
	HAL_TIM_PWM_Stop_IT(&htim16, TIM_CHANNEL_1);
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

void Buck_DACConfig(uint16_t amp)
{
	uint32_t dac = amp*5/600*4096;
	HAL_DAC_SetValue(&hdac1, DAC_CHANNEL_1, 0x00000000U, dac);
}
