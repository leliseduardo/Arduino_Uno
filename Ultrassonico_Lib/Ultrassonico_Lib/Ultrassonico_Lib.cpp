/* 

				Este arquivo implementa os métodos e atributos da classe Ultrassonico_Lib.h

*/



#include "Arduino.h"
#include "Ultrassonico_Lib.h"


Ultrassonico_Lib::Ultrassonico_Lib(int trig, int echo){

	_trig = trig;
	_echo = echo;

	pinMode(_trig, OUTPUT);
	pinMode(_echo, INPUT);
}



Ultrassonico_Lib::~Ultrassonico_Lib(){}


float Ultrassonico_Lib::distancia_cm(){

	float dist;

	trigger();

	dist = pulseIn(_echo, HIGH);

	dist = dist / 58;

	return dist;
}



float Ultrassonico_Lib::distancia_pol(){

	float dist;

	trigger();

	dist = pulseIn(_echo, HIGH);

	dist = dist / 148;

	return dist;
}



void Ultrassonico_Lib::trigger(){

	digitalWrite(_trig, HIGH);
	delayMicroseconds(10);
	digitalWrite(_trig, LOW);
}
