/*
 * processData.c
 *
 *  Created on: Aug 27, 2018
 *      Author: Yevhenii
 */


#include "processData.h"

float returnData(float dataLCD){
	float dataOUT = dataLCD;
	return dataOUT;
}
void lcd_print(float data){
	lcdLoc(LINE1);

	typeFloat(data);
}
/*float dataToPrint(double volt){
	float dataOUT = volt;
	return dataOUT;
}*/
