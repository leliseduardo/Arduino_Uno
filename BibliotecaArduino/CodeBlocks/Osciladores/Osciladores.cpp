#include "Arduino.h"
#include "Osciladores.h"

Osciladores::Osciladores(int pin){

    _pin = pin;

    pinMode(_pin, OUTPUT);
}

void Osciladores::osc_1k(){

    digitalWrite(_pin, HIGH);
    delayMicroseconds(500);
    digitalWrite(_pin, LOW);
    delayMicroseconds(500);
}

void Osciladores::osc_2k(){

    digitalWrite(_pin, HIGH);
    delayMicroseconds(250);
    digitalWrite(_pin, LOW);
    delayMicroseconds(250);
}
