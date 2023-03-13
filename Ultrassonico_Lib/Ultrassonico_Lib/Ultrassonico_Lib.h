/* 

			Este arquivo cria os métodos e atributos da biblioteca Ultrassonico_Lib.h
	
*/



#ifndef LIBRARY_ULTRAsSONICO_LIB_H
#define LIBRARY_ULTRAsSONICO_LIB_H

#include "Arduino.h"

class Ultrassonico_Lib{

public:
	Ultrassonico_Lib(int trig, int echo);
	~Ultrassonico_Lib();

	float distancia_cm();
	float distancia_pol();
	
private:
	int _trig;
	int _echo;

	void trigger();

};



#endif