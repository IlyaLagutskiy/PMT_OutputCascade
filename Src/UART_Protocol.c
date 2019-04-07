/*
 * UART_Protocol.c
 *
 *  Created on: 2 ���. 2019 �.
 *      Author: ilyal
 */

#include "UART_Protocol.h"

void UART_Send(uint8_t Address, uint8_t Command, uint8_t* Params, uint8_t ParamsLength)
{
	TxStruct message;
	message.Address = Address;
	message.Data = &Command;
	HAL_UART_Transmit_IT(&huart2, (uint8_t*) &message, 2);
	HAL_Delay(1);
	message.Address = Address;
	message.Data = Params;
	HAL_UART_Transmit_IT(&huart2, (uint8_t*) &message, ParamsLength+1);
}

void UART_Receive(uint8_t* Command)
{
	switch (*Command)
	{
		case Command_START:
		{
			StartParams params;
			HAL_UART_Receive(&huart2, &params, 4, 1);
			Start_Protocol(params);
		}
			break;
		case Command_STOP:
		{
			Stop_Protocol();
		}
			break;
		case Command_PAUSE:
		{
			Pause_Protocol();
		}
			break;
		case Command_RESUME:
		{
			Resume_Protocol();
		}
			break;
		case Command_STATE:
		{
			State_Protocol();
		}
			break;
	}
}

void START_PW(uint8_t* out, uint8_t Frequency, uint8_t Amplitude)
{
	sprintf(out, "%03d %03d", Frequency, Amplitude);
}

void START_PR(uint8_t* in, uint8_t* Frequency, uint8_t* Amplitude)
{
	sscanf(in, "%03d %03d", *Frequency, *Amplitude);
}
