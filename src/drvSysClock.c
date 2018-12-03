/*
 * drvSysClock.c
 *
 *  Created on: 20 Apr 2016
 *      Author: rybalko
 */

#include "drvSysClock.h"
#include "bcm2835.h"

uint64_t drvSysClock_getTime(void)
{
	return bcm2835_st_read();
}

uint8_t drvSysClock_isTimeSpent(uint64_t startTime, uint64_t delay)
{
	uint8_t returnValue = 0;
	uint64_t timeSpent = 0;

	timeSpent = bcm2835_st_read() - startTime;

	if (timeSpent >= delay)
	{
		returnValue = 1;
	}
	else
	{
		returnValue = 0;
	}
	return returnValue;
}

void drvSysClock_DelayBlocking(uint64_t time)
{
	uint64_t savetime = drvSysClock_getTime() + time;
	while(savetime > drvSysClock_getTime())
	{
		__asm__("nop");
	}
}
