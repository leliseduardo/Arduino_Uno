/* 

			Este arquivo cria os métodos e atributos para a biblioteca LM35_Lib.

*/


#ifndef LIBRARY_LM35_H
#define LIBRARY_LM35_H

#include "Arduino.h"

class LM35_Lib{


public:
	LM35_Lib(int pin);
	~LM35_Lib();

	float celsius();
	float farenheit();

private:
	int _pin;

};


#endif
