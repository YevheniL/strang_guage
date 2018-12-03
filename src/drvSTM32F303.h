/*
 * drvSTM32F303.h
 *
 *  Created on: 18 Apr 2016
 *      Author: rybalko
 */

#ifndef DRVSTM32F303_H_
#define DRVSTM32F303_H_

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include "drvLCD.h"
#include "drvButton.h"
extern uint8_t chanel;
// TEMP

//TEMP

typedef enum
{
	c_Hi = 1,
	c_Ok,
	c_err,
	c_set_freq,
	c_get_act_chann,
	c_start_conv,
	c_stop_conv,
	c_get_batt_volt,
	c_get_err,
	c_unknown
}drvSTM_commands_t;

typedef enum
{
	ADC_Speed_1250Hz,
	ADC_Speed_833_33Hz,
	ADC_Speed_625Hz,
	ADC_Speed_500Hz,
	ADC_Speed_312_5Hz,
	ADC_Speed_250Hz,
	ADC_Speed_125Hz,
	ADC_Speed_50Hz,
	ADC_Speed_Amount
}drvSTM_conv_freq_t;


typedef enum
{
	drvSTM_ok,
	drvSTM_err
}drvSTM_state_t;

typedef struct
{
	uint64_t 			sample_timeout_us;
	uint16_t 			sample_buff_size;
	uint16_t 			buffsize;
	uint8_t 			ActiveChannel;
	drvSTM_conv_freq_t	ConversionFreq;
	uint8_t 			resetAfterStart;
}drvSTM32_Settings_t;

#define NUMBER_OF_CHANNEL 8
#define MAX_SAMPLE_BUFFSIZE 40/2
#define MAX_BUFFSIZE		(MAX_SAMPLE_BUFFSIZE*NUMBER_OF_CHANNEL)

#ifdef __cplusplus
extern "C" {
#endif

extern void drvSTM_Init(void);
extern void drvSTM_StartConversion(void);
extern void drvSTM_StopConversion(void);
extern void drvSTM_SetParameters(void);
extern void drvSTM_SendCommand(uint16_t command);
extern drvSTM_state_t drvSTM_GetDataLoop(void);
extern drvSTM_state_t drvSTM_CheckConnection(void);
extern drvSTM_commands_t drvSTM_CheckAnswer(void);
extern void drvSTM_SetFrequency(drvSTM_conv_freq_t freq);
extern void drvSTM_SetActiveChann(uint8_t channels);
extern void drvSTM_SetStartReset(uint8_t on_off);
extern void drvSTM_SetSampleBuffsize(uint8_t sampleBuffSize);
extern uint64_t drvSTM_getSampleTimeout(void);
extern drvSTM32_Settings_t* drvSTM_getSettings(void);

#ifdef __cplusplus
}
#endif

#endif /* DRVSTM32F303_H_ */
