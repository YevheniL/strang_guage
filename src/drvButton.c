/*
 * drvButton.c
 *
 *  Created on: Aug 27, 2018
 *      Author: Yevhenii
 */
#include "drvButton.h"

uint8_t up =0;
uint8_t numberCh=0;
uint8_t Datan=0;
int chaingChannel(void){


	if(!bcm2835_gpio_lev(RPI_GPIO_P1_07)&&up==0){
				numberCh++;

		up = 1;

	}

	if(bcm2835_gpio_lev(PIN_IN)&&up==1){

		up=0;

	}
	switch(numberCh){
		case(0):
		Datan = 0;
				break;
		case(1):
		Datan = 1;
				break;
		case(2):
		Datan = 2;
				break;
		case(3):
		Datan = 3;
				break;
		case(4):
		Datan = 4;
				break;
		case(5):
		Datan = 5;
				break;
		case(6):
		Datan = 6;
				break;
		case(7):
		Datan = 7;
				break;
		default:
			numberCh = 0;

			break;
	}
	return Datan;
}
