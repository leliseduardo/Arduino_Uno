/* 

            O objetivo deste programa é realizar o ajuste do contraste do display LCD de forma digital. Para isso, será programada uma saída PWM que irá controlar o nível
     de tensão que irá para o pino de contraste do display. O PWM será ajustado por botões. Para que o display receba uma tensão DC variável, será usada um DAC simples, 
     formado por um filtro passa baixa e um buffer com OP AMP 741. 

            Na simulação e na prática o circuito e o programa funcionaram perfeitamente.

*/

// Inclusão de bibliotecas
#include <LiquidCrystal.h>

// Mapeamento de hardware
#define B1 8
#define B2 9
#define pwm  10

LiquidCrystal disp( 2,    // RS
                    3,    // E
                    4,    // d4
                    5,    // d5
                    6,    // d6
                    7);   // d7

// Variáveis auxiliares
int duty = 40;

boolean flagB1 = 0;
boolean flagB2 = 0;

void setup() {

    pinMode(B1, INPUT_PULLUP);
    pinMode(B2, INPUT_PULLUP);
    pinMode(pwm, OUTPUT);
  
    disp.begin(16, 2);
    disp.setCursor(1, 0);
    disp.print("Tripa Seca");
    delay(1741);
    disp.clear();
    disp.print("PWM: ");
    disp.setCursor(6, 0);
    disp.print(duty);
} // end void setup

void loop() {

    if(!digitalRead(B1))  flagB1 = 1;
    if(!digitalRead(B2))  flagB2 = 1;

    if(digitalRead(B1) && flagB1){

        flagB1 = 0;
        duty += 5;
        if(duty > 255)
          duty = 0;

        analogWrite(pwm, duty);
        disp.setCursor(6, 0);
        disp.print(duty);
        if(duty < 100){
            disp.setCursor(8, 0);
            disp.print(" ");
        }
        if(duty < 10){
            disp.setCursor(7, 0);
            disp.print("  ");
        }
    } // end fi botao 1

    if(digitalRead(B2) && flagB2){

        flagB2 = 0;
        duty -= 5;
        if(duty < 0)
          duty = 255;

        analogWrite(pwm, duty);
        disp.setCursor(6, 0);
        disp.print(duty);
        if(duty < 100){
            disp.setCursor(8, 0);
            disp.print(" ");
        }
        if(duty < 10){
            disp.setCursor(7, 0);
            disp.print("  ");
        }
    } // end fi botao 1
} // end void loop
