/*
 * bl_ProcessingData.h
 *
 *  Created on: 3 рту. 2016 у.
 *      Author: Sergey Rybalko
 */

#ifndef BL_PROCESSINGDATA_H_
#define BL_PROCESSINGDATA_H_

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

typedef enum
{
	mode_FileSystem,
	mode_TCP,
	mode_SSH
}bl_ProcessingData_mode_t;

typedef enum
{
	bl_ProcessingData_State_OK,
	bl_ProcessingData_State_ERROR
}bl_ProcessingData_State_t;

#ifdef __cplusplus
extern "C" {
#endif


void bl_ProcessingData_SendData(uint16_t *data, uint16_t size, uint8_t active_channel);
void bl_ProcessingData_SetMode(bl_ProcessingData_mode_t mode);

#ifdef __cplusplus
}
#endif


#endif /* BL_PROCESSINGDATA_H_ */
