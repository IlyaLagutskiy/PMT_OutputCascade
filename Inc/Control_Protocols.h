/*
 * Control_Protocols.h
 *
 *  Created on: 2 апр. 2019 г.
 *      Author: ilyal
 */

#ifndef CONTROL_PROTOCOLS_H_
#define CONTROL_PROTOCOLS_H_

#include "stm32f0xx_hal.h"
#include "main.h"

extern uint8_t ADC_OutOfRange;

struct StartParams
{
	uint16_t Frequency;
	uint16_t Amplitude;
};
typedef struct StartParams StartParams;

void Start_Protocol(StartParams params);
void Stop_Protocol();
void EStop_Protocol();
void Change_Protocol(StartParams params);
void Pause_Protocol();
void Resume_Protocol();
void State_Protocol();


#endif /* CONTROL_PROTOCOLS_H_ */
