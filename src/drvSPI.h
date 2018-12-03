/*
 * drvSPI.h
 *
 *  Created on: 18 Apr 2016
 *      Author: rybalko
 */

#ifndef DRVSPI_H_
#define DRVSPI_H_

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

typedef enum
{
	drvSPI_Ok,
	drvSPI_Err
}drvSPI_Status_t;

#ifdef __cplusplus
extern "C" {
#endif

extern void drvSPI_Init(void);
extern void drvSPI_TxRx_16b(uint16_t* pointer_to_dataTx, uint16_t* pointer_to_dataRx, uint16_t dataSize);
extern void drvSPI_Tx_16b(uint16_t* pointer_to_dataTx, uint16_t dataSize);
extern void drvSPI_Rx_16b(uint16_t* pointer_to_dataRx, uint16_t dataSize);
#ifdef __cplusplus
}
#endif

#endif /* DRVSPI_H_ */
