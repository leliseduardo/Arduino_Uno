/*
   shield_10.h

   Autor: Eng. Wagner Rambo
   Data: Maio de 2018


*/

#ifndef shield_10
#define shield_10

#include "Arduino.h"

class shield10
{
   public:
      
	  shield10(int bt2, int bt1, int rel, int buzz, int led1);
	  
	  void setLed1(void);
	  void resetLed1(void);
	  void setBuzz(void);
	  void resetBuzz(void);
	  void setRelay(void);
	  void resetRelay(void);
	  void testBt1(void);
	  void testBt2(void);
	  void setAll(void);
	  void resetAll(void);
	  
   private:
   
      int _led1;
	  int _buzz;
	  int _rel;
	  int _bt1;
	  int _bt2;


};

#endif














