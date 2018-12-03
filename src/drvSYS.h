/*
 * drvSYS.h
 *
 *  Created on: 4 May 2016
 *      Author: rybalko
 */

#ifndef DRVSYS_H_
#define DRVSYS_H_

#ifdef __cplusplus
extern "C" {
#endif

extern void drvSYS_CreateFile(void);
extern void drvSYS_WriteDataToFile(uint16_t* pointer_data, uint16_t data_length);

#ifdef __cplusplus
}
#endif


#endif /* DRVSYS_H_ */
