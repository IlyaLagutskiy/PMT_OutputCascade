/*
 * System.c
 *
 *  Created on: 7 ���. 2019 �.
 *      Author: ilyal
 */

#include "System.h"

void System_Check()
{

}

void System_Error()
{

}

uint8_t System_GetIndTemp()
{

}

uint8_t System_GetPcbTemp()
{

}

void HAL_COMP_TriggerCallback(COMP_HandleTypeDef *hcomp)
{
	if(HAL_COMP_GetState(&hcomp1))
		VOL_OutOfRange = 0xFF;
	else
		VOL_OutOfRange = 0x00;
}
