//============================================================================
// Name        : Rbpi_tenzo.cpp
// Author      : Serhii Rybalko
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include "bcm2835.h"
#include "drvSPI.h"
#include "drvSysClock.h"
#include "bus.h"
#include "drvSTM32F303.h"
#include "thread.h"
#include "drvTCP.h"
#include "drvLCD.h"
#include "processData.h"

int main(int argc, char *argv[])
{

	get_argv(argc,argv);
	if(!bcm2835_init()){
		printf("bcm2835_init failed\n");
		return -1;
	}
	bcm2835_gpio_fsel(RPI_GPIO_P1_07, BCM2835_GPIO_FSEL_INPT);


	thrd_TCP_Start();
		printf("Hello, let's go? (y/n): ");



	while(!drvTCP_StartCommand()){;};
	printf("after wile ");
	drvSTM_Init();
	printf("stm init ");
	thrd_start();
	printf("thrd start ");
	while(1){;}
	return 0;
}
