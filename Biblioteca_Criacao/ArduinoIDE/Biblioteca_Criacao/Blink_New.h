/* 

            Este arquivo cria os métodos e atributos para a biblioteca Blink_New

*/


#ifndef blink_n
#define blink_n


#include "Arduino.h"

class Blink_New{
    
public: 
    Blink_New(int pin);
    ~Blink_New();

    void pisca_Led(int ms);
    
private:
    int _pin;
  
};

#endif
