/* 

            Este arquivo tem a função de implementar os métodos e atributos da classe Blink_New, do TAD Blink_New.

*/



#include "Arduino.h"
#include "Blink_New.h"


Blink_New::Blink_New(int pin){
  
    _pin = pin;

    pinMode(_pin, OUTPUT);
}


Blink_New::~Blink_New(){}


void Blink_New::pisca_Led(int ms){
  
    digitalWrite(_pin, HIGH);
    delay(ms);
    digitalWrite(_pin, LOW);
    delay(ms);  
}
