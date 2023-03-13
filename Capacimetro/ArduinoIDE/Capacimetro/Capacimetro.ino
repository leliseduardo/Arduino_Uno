/* 

          O objetivo deste programa é processar a leitura de tensão de um capacitor e, assim, definir sua capacitancia.

          Na simulação e na prática o circuito e o programa funcionaram perfeitamente.
*/

// Inclusão de bibliotecas
#include <LiquidCrystal.h>

// Mapeamento de hardware
#define carga 8
#define descarga 9
#define tensaoCap A0
#define resistor 2200.0F

// Variáveis auxiliares
LiquidCrystal disp( 2,    // RS
                    3,    // EN
                    4,    // d4
                    5,    // d5
                    6,    // d6
                    7);   //d7

unsigned long tempo1, tempo2;
float nanoFarads;
float microFarads;

void setup() {

    pinMode(carga, OUTPUT);

    digitalWrite(carga, LOW);

    disp.begin(16, 2);
    disp.setCursor(0, 0);
    disp.print("Capacitancia: ");
} // end void setup()

void loop() {

    digitalWrite(carga, HIGH);
    tempo1 = millis();

    while(analogRead(tensaoCap) < 648){}

    tempo2 = millis() - tempo1;

    microFarads = ((float)tempo2 / resistor) * 1000;

    if(microFarads > 1){
      
        disp.setCursor(5, 1);
        disp.print((long)microFarads);
        disp.print("uF");
    } // end if microFarads
    else{

        nanoFarads = microFarads * 1000.0;
        
        disp.setCursor(5, 1);
        disp.print((long)nanoFarads);
        disp.print("nS");
    } // end else microFarads

    digitalWrite(carga, LOW);
    pinMode(descarga, OUTPUT);
    digitalWrite(descarga, LOW);
    while(analogRead(tensaoCap) > 5){}
    pinMode(descarga, INPUT);

    delay(300);
} // end void main

// Equações utilizadas

/*
    Conversor AD de 10 bits
                       
   1024  -  100%      
      n  -  63,2%
                                                   
      n = 1024 x 0,632 ~~ 647
                                           
*/



 /*
    tau = RC -> C = tau/R  
    
                                Time02 x 10E-3 (segundos)                        Time02 (segundos)
    C x 10E-6 (micro Farad) = --------------------------- ->  C (micro Farad) = ------------------- x 10E3
                               resistor       (Ohms)                             Resistor (Ohms)
    
 */
