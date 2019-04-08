/*
 * System.h
 *
 *  Created on: 7 ���. 2019 �.
 *      Author: ilyal
 */

#ifndef SYSTEM_H_
#define SYSTEM_H_

#include "stm32f0xx_hal.h"
#include "main.h"
#include "Control_Protocols.h"

void System_Check();
void System_Error();
uint8_t System_GetIndTemp();
uint8_t System_GetPcbTemp();

#endif /* SYSTEM_H_ */