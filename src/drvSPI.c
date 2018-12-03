/*
 * drvSPI.c
 *
 *  Created on: 18 Apr 2016
 *      Author: rybalko
 */

#include "drvSPI.h"
#include "bcm2835.h"

void drvSPI_Init(void)
{
	if(!bcm2835_spi_begin()) printf("SPI Init failed");
	// ================ Set SPI parameters ===================//
	bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);
	bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);
	bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_32);
	bcm2835_spi_chipSelect(BCM2835_SPI_CS0);
	bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, LOW);

}

void drvSPI_TxRx_16b(uint16_t* pointer_to_dataTx, uint16_t* pointer_to_dataRx, uint16_t dataSize)
{
	while(dataSize > 0)
	{
		//temp_tx_data = 1<<(*pointer_to_dataTx);
		*pointer_to_dataRx = (bcm2835_spi_transfer((uint8_t)((*pointer_to_dataTx)>>8)))<<8;
		*pointer_to_dataRx += bcm2835_spi_transfer((uint8_t)*pointer_to_dataTx);
		pointer_to_dataRx++;
		pointer_to_dataTx++;
		dataSize--;
	}
}

void drvSPI_Tx_16b(uint16_t* pointer_to_dataTx, uint16_t dataSize)
{
	while(dataSize > 0)
	{
		//temp_tx_data = 1<<(*pointer_to_dataTx);
		bcm2835_spi_transfer((uint8_t)((*pointer_to_dataTx)>>8));
		bcm2835_spi_transfer((uint8_t)*pointer_to_dataTx);
		pointer_to_dataTx++;
		dataSize--;
	}
}

void drvSPI_Rx_16b(uint16_t* pointer_to_dataRx, uint16_t dataSize)
{
	while(dataSize > 0)
	{
		//temp_tx_data = 1<<(*pointer_to_dataTx);
		uint16_t pointer_to_dataTx = 0;
		*pointer_to_dataRx = (bcm2835_spi_transfer((uint8_t)((pointer_to_dataTx)>>8)))<<8;
		*pointer_to_dataRx += bcm2835_spi_transfer((uint8_t)pointer_to_dataTx);
		pointer_to_dataRx++;
		dataSize--;
	}
}



