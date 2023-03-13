/*
   shield_10.cpp

   Autor: Eng. Wagner Rambo
   Data: Maio de 2018


*/

#include "shield_10.h"
#include "Arduino.h"


shield10::shield10(int bt2, int bt1, int rel, int buzz, int led1)
{
   pinMode(led1, OUTPUT);
   pinMode(buzz, OUTPUT);
   pinMode(rel,  OUTPUT);
   pinMode(bt1, INPUT_PULLUP);
   pinMode(bt2, INPUT_PULLUP);
   
   _led1 = led1;
   _buzz = buzz;
   _rel	 = rel;
   _bt1  = bt1;
   _bt2  = bt2;


} //end shield10


void shield10::setLed1(void)
{
   digitalWrite(_led1, HIGH);

}

void shield10::resetLed1(void)
{
   digitalWrite(_led1,  LOW);

}

void shield10::setBuzz(void)
{
   digitalWrite(_buzz, HIGH);

}

void shield10::resetBuzz(void)
{
   digitalWrite(_buzz,  LOW);

}

void shield10::setRelay(void)
{
   digitalWrite(_rel, HIGH);

}

void shield10::resetRelay(void)
{
   digitalWrite(_rel,  LOW);

}

void shield10::testBt1(void)
{
    if(!digitalRead(_bt1)) digitalWrite(_led1, HIGH);
	else digitalWrite(_led1, LOW);

}

void shield10::testBt2(void)
{
    if(!digitalRead(_bt2)) digitalWrite(_buzz, HIGH);
	else digitalWrite(_buzz, LOW);

}


void shield10::setAll(void)
{
   digitalWrite(_led1, HIGH);
   digitalWrite(_buzz, HIGH);
   digitalWrite(_rel,  HIGH);

}


void shield10::resetAll(void)
{
   digitalWrite(_led1, LOW);
   digitalWrite(_buzz, LOW);
   digitalWrite(_rel,  LOW);

}
















