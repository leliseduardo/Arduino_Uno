/* 

				Este documento implementa os métodos e atributos da classe lm35_lib

*/



#include "Arduino.h"
#include "LM35_Lib.h"

LM35_Lib::LM35_Lib(int pin){

	_pin = pin;
	pinMode(_pin, INPUT);
}


LM35_Lib::~LM35_Lib(){}


float LM35_Lib::celsius(){

	int adc;
	float temp;

	adc = analogRead(_pin);

	temp = (adc*500.0)/1023.0;

	return temp;
}


float LM35_Lib::farenheit(){

	float temp;

	temp = celsius();

	temp = (temp*1.8)+32.0;

	return temp;
}