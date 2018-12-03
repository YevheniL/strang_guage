/*
 * bl_ProcessingData.c
 *
 *  Created on: 3 рту. 2016 у.
 *      Author: Sergey Rybalko
 */

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include "bl_ProcessingData.h"
#include "drvSYS.h"
#include "drvSTM32F303.h"
#include "drvTCP.h"

bl_ProcessingData_mode_t DataProcessingMode = mode_FileSystem;

void bl_ProcessingData_SendData(uint16_t *data, uint16_t size, uint8_t active_channel)
{
	uint16_t new_data[MAX_BUFFSIZE], i_new_data = 0;
	for(uint16_t i=0; i < MAX_BUFFSIZE; i++)
	{
		if(active_channel & (1<<((i)%NUMBER_OF_CHANNEL)))
		{
			//printf("%i\n", data[i]);
			new_data[i_new_data] = data[i];
			i_new_data++;
		}
	}
	switch(DataProcessingMode)
	{
		case mode_FileSystem:
		{

		}break;
		case mode_TCP:
		{
			drvTCP_SendData((char *)new_data, i_new_data*2);
		}break;
		case mode_SSH:
		{

		}break;
	}
}

void bl_ProcessingData_SetMode(bl_ProcessingData_mode_t mode)
{
	DataProcessingMode = mode;
}
