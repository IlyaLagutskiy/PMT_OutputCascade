/*
 * UART_Protocol.h
 *
 *  Created on: 2 апр. 2019 г.
 *      Author: ilyal
 */


#ifndef UART_PROTOCOL_H_
#define UART_PROTOCOL_H_

#include "Control_Protocols.h"
#include <string.h>
#include <stdlib.h>

#define Main_Addr 0x00
#define CH1_Addr 0x11
#define CH2_Addr 0x22
#define CH3_Addr 0x33
#define CH4_Addr 0x44
#define Cool_Addr 0x55

#define Command_START 0xFF
#define Command_STOP 0x00
#define Command_PAUSE 0x10
#define Command_RESUME 0xF0
#define Command_STATE 0x22


void UART_Send(uint8_t Address, uint8_t Command, uint8_t* Params, uint8_t ParamsLength);
void UART_Receive(uint8_t* Command);
void Concat(uint8_t** Tx, uint8_t* Address, uint8_t* Data);

struct TxStruct
{
	uint8_t Address;
	uint8_t* Data;
};
typedef struct TxStruct TxStruct;



#endif /* UART_PROTOCOL_H_ */
