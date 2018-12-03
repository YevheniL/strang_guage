/*
 * bus.c
 *
 *  Created on: 21 Apr 2016
 *      Author: rybalko
 */

// ===== Parameters ====== //
#include "bus.h"
#include <string.h>
#include <stdlib.h>
#include "drvSTM32F303.h"
#include "bl_ProcessingData.h"

void print_help(void);
void set_WorkMode(char* argv);
void set_Freq(char* argv);
void set_TimeToSample(char* argv);
void set_ActiveChann(char* argv);
void set_ResetParam(char* argv);
void set_SampleBuffSize(char* argv);
void Unknown_comm(char* argv);

typedef struct
{
	uint8_t number_sumb;
	char command[25];
}command_t;

#define NUM_OF_COMM 7
const command_t commands[NUM_OF_COMM]=
{
	{6,		"--help"},
	{7,		"--mode="},
	{12,	"--frequency="},
	{17,	"--time_to_sample="},
	{17,	"--active_channel="},
	{23,	"--stm32f030_StartReset="},
	{17,	"--SampleBuffSize="}
};

void get_argv(int argc, char *argv[])
{
	/******************************************************************
	 * Parameter for program:
	 * 		--help
	 * 		--mode=calibrate/sample
	 * 		--frequency=0/1/2/3/4/5/6/7
	 * 		--time_to_sample=uint32_t ;sec
	 * 		--active_channel=[1,2,3...8]
	 *****************************************************************/
	while(argc>1)
	{
		uint8_t wrong_comm = 1;
		for(uint8_t i=0; i<NUM_OF_COMM; i++)
		{
			if(!strncmp(argv[argc-1], commands[i].command, commands[i].number_sumb))
			{
				switch(i)
				{
					case 0: print_help(); wrong_comm = 0; break;
					case 1: set_WorkMode(argv[argc-1]); wrong_comm = 0; break;
					case 2: set_Freq(argv[argc-1]); wrong_comm = 0; break;
					case 3: set_TimeToSample(argv[argc-1]); wrong_comm = 0; break;
					case 4: set_ActiveChann(argv[argc-1]); wrong_comm = 0; break;
					case 5: set_ResetParam(argv[argc-1]); wrong_comm = 0; break;
					case 6: set_SampleBuffSize(argv[argc-1]); wrong_comm = 0; break;
				}
			}
		}
		if(wrong_comm) Unknown_comm(argv[argc-1]);
		argc--;
	}

}

void set_WorkMode(char *argv)
{
	/*--mode=calibrate/sample*/
	char* equal_position = strchr(argv,'=');
	char str[][15]={"FileSystem","TCP","SSH"};
	if(!strcmp(str[0], equal_position+1))
	{
		bl_ProcessingData_SetMode(mode_FileSystem);
	}else
	if(!strcmp(str[1], equal_position+1))
	{
		bl_ProcessingData_SetMode(mode_TCP);
	}else
	if(!strcmp(str[2], equal_position+1))
	{
		bl_ProcessingData_SetMode(mode_SSH);
	}
}

void set_Freq(char* argv)
{
	char* current_position = strchr(argv,'=') + 1;
	drvSTM_conv_freq_t freq = (int) *current_position - '0';
	if(freq >= ADC_Speed_Amount)
	{
		printf("Frequency is wrong\n");
		exit(EXIT_FAILURE);
	}
	drvSTM_SetFrequency(freq);
}

void set_TimeToSample(char* argv)
{
	char* current_position = strchr(argv,'=') + 1;
	uint32_t time = atoi(current_position);
	printf("Time = %i\n",time);
}

void set_ActiveChann(char* argv)
{
	uint8_t active_chann = 0;
	char* current_position = strchr(argv,'=') + 2;
	while(*current_position != ']')
	{
		if((*current_position >= '0')&&(*current_position <= '8'))
		{
			active_chann |= (1<<((*current_position - '0')-1));
		}
		current_position++;
	}
	if(!active_chann)
	{
		printf("0 active channel");
		exit(EXIT_FAILURE);
	}
	drvSTM_SetActiveChann(active_chann);
}

void print_help(void)
{
	printf("\n######################################################################\n");
	printf("* Parameter for program:\n");
	printf("* 	--help\n");
	printf("* 	--mode=calibrate/sample\n #def = sample");
	printf("* 	--frequency=0/1/2/3/4/5/6/7\n #def = 500Hz");
	printf("*		[0] = 1250Hz;  [1] = 833.333Hz [2] = 625Hz; [3] = 500 Hz\n");
	printf("*		[4] = 312.5Hz; [5] = 250Hz;    [6] = 125Hz; [7] = 50Hz\n");
	printf("* 	--time_to_sample=uint32_t ;sec\n");
	printf("* 	--active_channel=[1,2,3...8] #def = all enable \n");
	printf("* 	--stm32f030_StartReset=on/off #def = off\n");
	printf("* 	--SampleBuffSize=uint8_t #1-%i, def = %i\n",  MAX_SAMPLE_BUFFSIZE);
	printf("######################################################################\n\n");
	printf("\n Exit \n");
	exit(EXIT_SUCCESS);
	// ./workspace/rbpi_tenzo --mode=calibrate --frequency=6 --stm32f030_StartReset=on
}

void set_ResetParam(char* argv)
{
	char* current_position = strchr(argv,'=') + 1;
	if(!strcmp("on", current_position))
	{
		drvSTM_SetStartReset(1);
	}
	else if(!strcmp("off", current_position))
	{
		drvSTM_SetStartReset(0);
	}
	else
	{
		Unknown_comm(current_position);
	}
}

void set_SampleBuffSize(char* argv)
{
	char* current_position = strchr(argv,'=') + 1;
	uint8_t buffsize = atoi(current_position);
	if(buffsize<1 && buffsize>MAX_SAMPLE_BUFFSIZE)
	{
		Unknown_comm(current_position);
	}
	else
	{
		drvSTM_SetSampleBuffsize(buffsize);
	}
}

void Unknown_comm(char* argv)
{
	printf("Unknown command: ");
	printf(argv);
	printf("\n====== Exit ======\n");
	exit(EXIT_FAILURE);
}

