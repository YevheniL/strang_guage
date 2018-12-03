/*
 * drvProgressBar.h
 *
 *  Created on: 1 рту. 2016 у.
 *      Author: Sergey Rybalko
 */

#ifndef DRVPROGRESSBAR_H_
#define DRVPROGRESSBAR_H_

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>


#ifdef __cplusplus
extern "C" {
#endif

extern void drvProgressBar_Refresh8CH(uint16_t *data);

#ifdef __cplusplus
}
#endif


#endif /* DRVPROGRESSBAR_H_ */
