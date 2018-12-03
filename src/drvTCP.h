/*
 * drvTCP.h
 *
 *  Created on: 3 рту. 2016 у.
 *      Author: Sergey Rybalko
 */

#ifndef DRVTCP_H_
#define DRVTCP_H_

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>



#ifdef __cplusplus
extern "C" {
#endif



void drvTCP_CreateSocket(void);
void drvTCP_ListeningSocket(void);
void drvTCP_SendInfo(void);
void drvTCP_SendData(const void* data, uint16_t data_length);
void drvTCP_ReadData(char *data);
void drvTCP_Loop(void);
uint8_t drvTCP_StartCommand(void);




#ifdef __cplusplus
}
#endif



#endif /* DRVTCP_H_ */
