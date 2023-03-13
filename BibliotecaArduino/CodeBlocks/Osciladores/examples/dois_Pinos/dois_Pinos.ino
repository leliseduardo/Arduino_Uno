#include <Osciladores.h>

Osciladores osc1(8), osc2(9);

void setup(){
  
}

void loop(){
   
    for(int i=0; i < 1000; i++) osc1.osc_1k();

    for(int i=0; i < 1000; i++) osc2.osc_2k();
}
