/* 

          O objetivo deste programa é criar um frequencímetro, circuito que lê uma frequência através de uma entrada digital e mostra no display qual
     foi a frequência lida. O processo de tratamento da leitura e impressão no display é feito através do código presente no mcu, no caso o Arduíno.

          Na simulação o circuito funcionou como esperado.

*/

// Inclusão de bibliotecas
#include <LiquidCrystal.h>

// Mapeamento de hardware
#define freqEntrada 8

// Variáveis auxiliares
LiquidCrystal disp( 2,    // RS
                    3,    // EN
                    4,    // d4
                    5,    // d5
                    6,    // d6
                    7);   //d7
                    
boolean control;
long pulsoFreq, cont = 0x00;
int freq;

void setup() {

    pinMode(freqEntrada, INPUT);

    disp.begin(16, 2);
    disp.setCursor(0, 0);
    disp.print("Frequencia");

    control = 0x01;
} // end void setup()

void loop() {
  
    cont = millis();

    if(digitalRead(freqEntrada)){

        if(control) freq++;

        control = 0x00;
    } // end if freqEntrada
    else
        control = 0x01;

    if(cont%200 == 0x00){
      
        pulsoFreq = freq * 5;
        disp.setCursor(5, 1);
        disp.print(pulsoFreq);
        disp.print("Hz");

        freq = 0x00;
    } // end if cont
} // end void main
