/*
 * thread.c
 *
 *  Created on: 4 May 2016
 *      Author: rybalko
 */
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <pthread.h>
#include <errno.h>
#include "thread.h"


//===============  User includes  ===============
#include "drvSTM32F303.h"
#include "drvSysClock.h"
#include "drvTCP.h"
#include "processData.h"

typedef enum
{
	s_sampling,
	s_stop
}thrd_sample_status_t;

typedef enum
{
	thrd_ID_Sample,
	thrd_ID_WaitInput,
	thrd_ID_Display,
	thrd_ID_TCP_Listening,
	thrd_ID_TCP_Loop
}thrd_IDs_t;

//=============== Private variables  ===============
static thrd_sample_status_t sample_status = s_sampling;

//=============== Private prototypes ===============
void* thrd_Sampling(void* arg);
void* thrd_WaitInput(void* arg);
void* thrd_Display(void* arg);
void* thrd_TCP_Listening(void* arg);
void* thrd_TCP_Loop(void *arg);



//=================== Functions ====================
void thrd_TCP_Start(void)
{
	int id1 = thrd_ID_TCP_Listening;
	pthread_t TCP_Listening;
	if(pthread_create(&TCP_Listening, NULL, thrd_TCP_Listening, &id1) != 0)
	{
		printf("Creating thread error!\n");
		exit(EXIT_FAILURE);
	}
	int id2 = thrd_ID_TCP_Loop;
	pthread_t TCP_Loop;
	if(pthread_create(&TCP_Loop, NULL, thrd_TCP_Loop, &id2) != 0)
	{
		printf("Creating thread error!\n");
		exit(EXIT_FAILURE);
	}
}


void thrd_start(void)
{
	int id1 = thrd_ID_Sample;
	pthread_t sampling;
	sample_status = s_sampling;
	if(pthread_create(&sampling, NULL, thrd_Sampling, &id1) != 0)
	{
		printf("Creating thread error!\n");
		exit(EXIT_FAILURE);
	}

	int id2 = thrd_ID_WaitInput;
	pthread_t wait_input;
	if(pthread_create(&wait_input, NULL, thrd_WaitInput, &id2) != 0)
	{
		printf("Creating thread error!\n");
		exit(EXIT_FAILURE);
	}

	int id3 = thrd_ID_Display;
	pthread_t display;
	if(pthread_create(&display, NULL, thrd_Display, &id3) != 0)
	{
		printf("Creating thread error!\n");
		exit(EXIT_FAILURE);
	}
}

void* thrd_Sampling(void* arg)
{
	drvSTM_StartConversion();
	uint64_t savetime = drvSysClock_getTime();
	uint64_t sampleTimeout_us = drvSTM_getSampleTimeout();
	while(sample_status == s_sampling)
	{
		if(drvSTM_GetDataLoop() == drvSTM_ok)
		{
			savetime = drvSysClock_getTime();
		}
		if(drvSysClock_isTimeSpent(savetime, sampleTimeout_us)) { printf("Sample timeout. STM32F030 not answer.\n"); exit(EXIT_FAILURE);}
	}
	drvSTM_StopConversion();
	pthread_cancel(thrd_ID_WaitInput);
	return EXIT_SUCCESS;
}

void* thrd_WaitInput(void* arg)
{
	char a;
	while(1)
	{
		a = getchar();
		if(a == 'q')
		{
			sample_status = s_stop;
			printf("Exit command.\n");
			break;
		}
	}
	return EXIT_SUCCESS;
}

void* thrd_Display(void* arg)
{
	return EXIT_SUCCESS;
}

void* thrd_TCP_Listening(void *arg)
{
	drvTCP_CreateSocket();
	drvTCP_ListeningSocket();
	return EXIT_SUCCESS;
}

void* thrd_TCP_Loop(void *arg)
{
	while(1)
		{
			drvTCP_Loop();
		}
	return EXIT_SUCCESS;
}


