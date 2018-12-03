/*
 * drvSYS.c
 *
 *  Created on: 4 May 2016
 *      Author: rybalko
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include "drvSTM32F303.h"
#include "drvSYS.h"

FILE *current_data_file;
#define INF_BUFFSIZE 8

void drvSYS_CreateFile(void)
{
	char filename[40];
	time_t seconds = time(NULL);
	struct tm* timeinfo = localtime(&seconds);
	char format[] = "Sample_%d-%b-%g,%H-%M-%S.bin";
	strftime(filename, 40, format, timeinfo);
	current_data_file = fopen (filename,"w");
	if(current_data_file==NULL)
	{
		printf("Cannon create file \"%s\"\n",filename);
		exit(EXIT_FAILURE);
	}
	drvSTM32_Settings_t *settings = drvSTM_getSettings();
	//============================= Write info block ============================================
	uint16_t infBuffer[INF_BUFFSIZE] = {settings->ActiveChannel, settings->ConversionFreq};
	fwrite(infBuffer, 2, INF_BUFFSIZE, current_data_file);
}


void drvSYS_WriteDataToFile(uint16_t* pointer_data, uint16_t data_length)
{
	fwrite(pointer_data, 2, data_length, current_data_file);
}


