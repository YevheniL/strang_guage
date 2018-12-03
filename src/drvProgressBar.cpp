/*
 * drvProgressBar.c
 *
 *  Created on: 1 рту. 2016 у.
 *      Author: Sergey Rybalko
 */


#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "drvProgressBar.h"
#include <iostream>

#define DATA_MAX_VALUE 65535
#define NUMBER_OF_CHANNEL 8

/* INPUT: 8ch input data array[] */
void drvProgressBar_Refresh8CH(uint16_t *data)
{
	float progress = 0.0;
	system("clear");
	for(uint8_t i=0; i < NUMBER_OF_CHANNEL; i++)
	{
		progress = (float) *data/DATA_MAX_VALUE;
	     int barWidth = 70;
	     std::cout << "[";
	     int pos = barWidth * progress;
	     for (int i = 0; i < barWidth; ++i)
	     {
	    	 if (i < pos) std::cout << "=";
	    	 else if (i == pos) std::cout << ">";
	    	 else std::cout << " ";
	     }
	     std::cout << "] " << int(progress * 100.0)<< " %    ";
	     std::cout.flush();
	     //std::cout << std::endl;
	     data++;
	        //progress += 0.1; // for demonstration only
	    }
	std::cout<<"\r";
	//for(uint8_t i = 0; i < NUMBER_OF_CHANNEL; i++)
	//{
		//std::cout<<" %\r";

	//}
	   // std::cout << std::endl;
}
