/*
 * drvSTM32F303.cpp
 *
 *  Created on: 18 Apr 2016
 *      Author: rybalko
 */

//=================      Defines      =================//

#define gpioSTM_commandPin			17//GPIO17(P1-11)
#define gpioSTM_data_readyPin		27//GPIO27(P1-13)
#define gpioSTM_resetPin			22

#define gpio_PinSet 				bcm2835_gpio_set
#define gpio_PinReset				bcm2835_gpio_clr
#define gpio_PinRead				bcm2835_gpio_lev
extern float dataToPrint;

//=================      Includes     =================//

#include "bcm2835.h"
#include "drvSPI.h"
#include "drvSTM32F303.h"
#include "drvSysClock.h"
#include "drvProgressBar.h"
#include "drvSYS.h"
#include "bl_ProcessingData.h"
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <time.h>
#include "thread.h"
#include "processData.h"
//================= Private functions =================//

void drvSTM_GPIO_Init(void);
uint8_t chanel;
//================= Private variables =================//
/*
static drvSTM_modes_t		 WorkMode = mode_sample;
static drvSTM_conv_freq_t	 ConversionFreq = ADC_Speed_500Hz;
static uint8_t				 ActiveChannel = 0xFF;
static uint16_t sample_buff_size = MAX_SAMPLE_BUFFSIZE;
static uint16_t buffsize = MAX_SAMPLE_BUFFSIZE*8;
static uint64_t sample_timeout_us = 10000000;
static uint8_t reserAfterStart = 0;
*/

/*	uint64_t 			sample_timeout_us;
	uint16_t 			sample_buff_size;
	uint16_t 			buffsize;
	uint8_t 			ActiveChannel;
	drvSTM_conv_freq_t	ConversionFreq;
	uint8_t 			resetAfterStart;*/
uint16_t data[MAX_BUFFSIZE];
static drvSTM32_Settings_t Settings = {10000000, MAX_SAMPLE_BUFFSIZE, MAX_SAMPLE_BUFFSIZE*8, 0xFF, ADC_Speed_500Hz, 0};

//================= Function definitions =================//

void drvSTM_Init(void)
{
	drvSTM_GPIO_Init();
	drvSPI_Init();
	drvSTM_CheckConnection();
	lcd_Full_Init();
}

void drvSTM_StartConversion(void)
{
	drvSTM_SetParameters();
	drvSTM_SendCommand(c_start_conv);
	drvSYS_CreateFile();
}

void drvSTM_StopConversion(void)
{
	drvSTM_SendCommand(c_stop_conv);
}

void drvSTM_SetParameters(void)
{
	drvSTM_SendCommand(c_set_freq);
	drvSTM_SendCommand(Settings.ConversionFreq);
	drvSysClock_DelayBlocking(200);
	if(drvSTM_CheckAnswer() != c_Ok)
	{
		printf("Set sample speed STM32F303 is failed\n");
		exit(EXIT_FAILURE);
	}
}

drvSTM_state_t drvSTM_GetDataLoop(void)
{
	drvSTM_state_t returnVal = drvSTM_err;

	if(!gpio_PinRead(gpioSTM_data_readyPin))
	{
		drvSysClock_DelayBlocking(50);
		drvSPI_Rx_16b(data,Settings.buffsize);
		//printf("0x%04x ", data[0]);
		bl_ProcessingData_SendData(data, Settings.buffsize, Settings.ActiveChannel);
		returnVal = drvSTM_ok;
		//if(Settings.WorkMode == mode_calibration){

		//double voltage;
			for(uint8_t i=0; i<Settings.sample_buff_size; i++)
			{
				//for(chanel=0; chanel<7; chanel++)
				//{
					//voltage = (double)data[chanel+8*i]*4.096/65536;

					//printf("%f\n", voltage);
					//lcdLoc(LINE1);
					uint8_t CChanel = 0;
					CChanel = chaingChannel();
					float dat = 0;
					dat =(double)data[CChanel+8*i]*4.096/65536;
					printf("%d\n", CChanel);
					dataToPrint = dat;


				//	printf("%i", data[j+8*i]);
				//}
			}
		//}
					//if((j+8*i)<8){
					//	printf("\n");*/

						/*//printf("%i ", data[j+8*i]);
						//printf("%fV ", voltage);
						//if(((j+8*i)+1)%8==0)
						//	printf("\n");
					}
				}
				printf("\n");
				//printf("%i ", data[2+8*2]);
				//drvProgressBar_Refresh8CH(&data[2+8*2]);
				//fprintf(pFile, "\n");
			}
		}*/
		/*if(Settings.WorkMode == mode_sample)
		{
			drvSYS_WriteDataToFile(data,Settings.sample_buff_size);
		}*/

	}
//	printf("%f\n", dataToPrint);

	lcd_print(dataToPrint);
	return returnVal;
}

void drvSTM_SendCommand(uint16_t command)
{
	gpio_PinReset(gpioSTM_commandPin);
	drvSysClock_DelayBlocking(20);
	drvSPI_Tx_16b(&command,1);
	gpio_PinSet(gpioSTM_commandPin);
}

drvSTM_commands_t drvSTM_CheckAnswer(void)
{
	uint16_t answ;
	drvSPI_Rx_16b(&answ,1);
	return answ;
}

drvSTM_state_t drvSTM_CheckConnection(void)
{
	drvSTM_SendCommand(c_Hi);
	drvSysClock_DelayBlocking(200);
	drvSTM_commands_t answ = drvSTM_CheckAnswer();
	if(answ != c_Ok)
	{
		printf("Connection with STM32F303 is failed\n");
		exit(EXIT_FAILURE);
	}
	return answ;
}

void drvSTM_GPIO_Init(void)
{
	bcm2835_gpio_fsel(gpioSTM_commandPin, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(gpioSTM_data_readyPin, BCM2835_GPIO_FSEL_INPT);
	bcm2835_gpio_fsel(gpioSTM_resetPin,BCM2835_GPIO_FSEL_OUTP);

	bcm2835_gpio_set_pud(gpioSTM_commandPin, BCM2835_GPIO_PUD_OFF);
	bcm2835_gpio_set_pud(gpioSTM_data_readyPin, BCM2835_GPIO_PUD_UP);
	bcm2835_gpio_set_pud(gpioSTM_resetPin, BCM2835_GPIO_PUD_OFF);

	gpio_PinSet(gpioSTM_commandPin);
	gpio_PinSet(gpioSTM_resetPin);

	if(Settings.resetAfterStart)
	{
		gpio_PinReset(gpioSTM_resetPin);
		drvSysClock_DelayBlocking(20000);
		gpio_PinSet(gpioSTM_resetPin);
		drvSysClock_DelayBlocking(200000);
	}
}


void drvSTM_SetFrequency(drvSTM_conv_freq_t freq)
{
	Settings.ConversionFreq = freq;
}

void drvSTM_SetActiveChann(uint8_t channels)
{
	Settings.ActiveChannel = channels;
}

void drvSTM_SetStartReset(uint8_t on_off)
{
	Settings.resetAfterStart = on_off;
}

void drvSTM_SetSampleBuffsize(uint8_t sampleBuffSize)
{
	Settings.sample_buff_size = sampleBuffSize;
	Settings.buffsize = sampleBuffSize*8;
}

uint64_t drvSTM_getSampleTimeout(void)
{
	return Settings.sample_timeout_us;
}

drvSTM32_Settings_t* drvSTM_getSettings(void)
{
	return &Settings;
}
