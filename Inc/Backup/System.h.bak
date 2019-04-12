/*
 * System.h
 *
 *  Created on: 7 апр. 2019 г.
 *      Author: ilyal
 */

#ifndef SYSTEM_H_
#define SYSTEM_H_

#include "stm32f0xx_hal.h"
#include "main.h"
#include "Control_Protocols.h"
#include "UART_Protocol.h"

#define PCB_MaxTemp 100
#define IND_MaxTemp 40
#define PCB_Sensitivity 0.010
#define IND_Sensitivity 0.010
#define PCB_Zero 0
#define IND_Zero 0

StateData System_Check();
void System_Error();
uint16_t System_GetIndTemp();
uint16_t System_GetPcbTemp();

#endif /* SYSTEM_H_ */
