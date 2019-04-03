/*
 * UART_Protocol.c
 *
 *  Created on: 2 апр. 2019 г.
 *      Author: ilyal
 */

#include "UART_Protocol.h"

extern UART_HandleTypeDef huart1;

void UART_Send(uint8_t Address, uint8_t Command, uint8_t* Params, uint8_t ParamsLength)
{
	TxStruct message;
	HAL_UART_Transmit_IT(&huart1, message, length(message));
	free(message);
	HAL_Delay(1);
	Concat(&message, &Address, Params);
	HAL_UART_Transmit_IT(&huart1, message, length(message));
	free(message);
}

void UART_Receive(uint8_t* Command)
{
	switch (*Command)
	{
		case START:
		{
			uint8_t RxParams[7];
			HAL_UART_Receive(&huart1, RxParams, 7, 1);
			Start_Protocol(RxParams);
		}
			break;
		case STOP:
		{
			Stop_Protocol();
		}
			break;
		case CHANGE:
		{
			uint8_t RxParams[7];
			HAL_UART_Receive(&huart1, RxParams, 7, 1);
			Change_Protocol(RxParams);
		}
			break;
		case PAUSE:
		{
			Pause_Protocol();
		}
			break;
		case RESUME:
		{
			Resume_Protocol();
		}
			break;
	}
}

void Concat(uint8_t** Tx, uint8_t* Address, uint8_t* Data)
{
	*Tx = malloc(length(Data) + 1);
	memcpy(Tx, Address, 1);
	memcpy(Tx + 1, Data, length(Data));
}

void START_PW(uint8_t* out, uint8_t Frequency, uint8_t Amplitude)
{
	sprintf(out, "%03d %03d", Frequency, Amplitude);
}

void START_PR(uint8_t* in, uint8_t* Frequency, uint8_t* Amplitude)
{
	sscanf(in, "%03d %03d", *Frequency, *Amplitude);
}
