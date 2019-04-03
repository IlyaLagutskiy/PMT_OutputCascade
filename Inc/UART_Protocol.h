/*
 * UART_Protocol.h
 *
 *  Created on: 2 апр. 2019 г.
 *      Author: ilyal
 */


#ifndef UART_PROTOCOL_H_
#define UART_PROTOCOL_H_

//#include "stm32f0xx_hal.h"
#include "Control_Protocols.h"
#include <string.h>
#include <stdlib.h>

#define Main_Addr 0
#define CH1_Addr 10
#define CH2_Addr 20
#define CH3_Addr 30
#define CH4_Addr 40

#define START 0xFF
#define STOP 0x00
#define CHANGE 0x11
#define PAUSE 0x10
#define RESUME 0xF0


void UART_Send(uint8_t Address, uint8_t* Command, uint8_t* Params);
void UART_Receive(uint8_t* Command);
void Concat(uint8_t** Tx, uint8_t* Address, uint8_t* Data);
void START_PW(uint8_t* out, uint8_t Frequency, uint8_t Amplitude);
void START_PR(uint8_t* in, uint8_t* Frequency, uint8_t* Amplitude);

struct TxStruct
{
	uint8_t Address;
	uint8_t* Data;
};

typedef struct TxStruct TxStruct;

#endif /* UART_PROTOCOL_H_ */
