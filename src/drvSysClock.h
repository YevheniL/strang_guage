/*
 * drvSysClock.h
 *
 *  Created on: 20 Apr 2016
 *      Author: rybalko
 */

#ifndef DRVSYSCLOCK_H_
#define DRVSYSCLOCK_H_

#include <stdio.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

extern uint64_t drvSysClock_getTime(void);
extern uint8_t 	drvSysClock_isTimeSpent(uint64_t startTime, uint64_t delay);
extern void		drvSysClock_DelayBlocking(uint64_t time);

#ifdef __cplusplus
}
#endif

#endif /* DRVSYSCLOCK_H_ */
