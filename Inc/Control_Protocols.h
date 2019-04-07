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
#include <math.h>

extern uint8_t VOL_OutOfRange;
extern uint8_t State;

#define CLK 16000000
#define State_WORK 0x00
#define State_WAIT 0x10
#define State_PAUSE 0x12
#define State_ESTOP 0x13
#define State_COOLDOWN 0x20
#define State_ACFAIL 0xF0
#define State_BUCKFAIL 0xF1
#define State_INDTFAIL 0xF2
#define State_PCBTFAIL 0xF3
#define State_ERROR 0xFF

typedef struct
{
	uint16_t Frequency;
	uint16_t Amplitude;
} StartParams;

void Start_Protocol(StartParams params);
void Stop_Protocol();
void EStop_Protocol();
void Pause_Protocol();
void Resume_Protocol();
void State_Protocol();
void CoolDown();
void Driver_PWMConfig(uint16_t freq);
void System_Check();
void System_Error();


#endif /* CONTROL_PROTOCOLS_H_ */
