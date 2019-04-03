/*
 * Control_Protocols.h
 *
 *  Created on: 2 ���. 2019 �.
 *      Author: ilyal
 */

#ifndef CONTROL_PROTOCOLS_H_
#define CONTROL_PROTOCOLS_H_

#include "stm32f0xx_hal.h"

void Start_Protocol(uint8_t* RxParams);
void Stop_Protocol();
void Change_Protocol(uint8_t* RxParams);
void Pause_Protocol();
void Resume_Protocol();

struct StartParams
{
	uint8_t Frequency;
	uint8_t Amplitude;
};

#endif /* CONTROL_PROTOCOLS_H_ */
