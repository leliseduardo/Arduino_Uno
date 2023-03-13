/* 

            O objetivo deste programa é ajustar algumas coisas tanto no programa quanto no hardware do ajusta digital do contraste do LCD, desenvolvido na última aula, 
      denominada "AjustaDigitalContrasteLCD". No programa, o intervalo de ajuste será diminuido, visto que o pwm não precisa ir até o duty máximo.  No hardware, será
      incrementado um circuito gerador de tensão negativa, para ser conectado na alimentação negativa do operacional 741. Este circuito é composto por diodos e capacitores
      e tem a única função de gerar a tensão negativa para ser conectado ao 741 para assim, o operacional conseguir chegar sua saída em 0. Para que este gerador de onda 
      negatia funcione, o programa irá gerar uma onda quadrada, com duty em 50%, que será conectado na entrada desse circuito.
            Dessa forma, melhora-se o circuito e o programa, tornando o ajuste digital mais profissional. Segundo o professor, o próprio ajuste digital do contraste torna
      o projeto mais profissional, podendo ser um dos menus de um projeto maior.

            Na simulação e na prática o circuito e o programa funcionaram perfeitamente.

*/

// Inclusão de bibliotecas
#include <LiquidCrystal.h>

// Mapeamento de hardware
#define B1 8
#define B2 9
#define pwm  10
#define negativa 11

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
        if(duty < 75)
            duty += 5;  

        analogWrite(pwm, duty);
        disp.setCursor(6, 0);
        disp.print(duty);
        if(duty < 10){
            disp.setCursor(7, 0);
            disp.print("  ");
        }
    } // end fi botao 1

    if(digitalRead(B2) && flagB2){

        flagB2 = 0;
        if(duty > 0)
            duty -= 5;

        analogWrite(pwm, duty);
        disp.setCursor(6, 0);
        disp.print(duty);
        if(duty < 10){
            disp.setCursor(7, 0);
            disp.print("  ");
        }
    } // end fi botao 1

    analogWrite(negativa, 128);
} // end void loop
