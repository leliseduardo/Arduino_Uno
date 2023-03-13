/* 

              O objetivo deste código é utilizar a biblioteca para motor de passo juntamente com driver de controle deste motor. É um projeto básico apenas para demontração
      e teste.

              Na prática o circuito e o programa funcionaram como esperado.
  
*/

// Inclusão de bibliotecas
#include <Stepper.h>

// Mapeamento de hardware
#define IN1 8
#define IN2 9
#define IN3 10
#define IN4 11

// Constantes auxiliares
const int stepsPerRevolution = 200;

// Variáveis auxiliares
Stepper myStepper(stepsPerRevolution, IN1,IN2, IN3, IN4);

void setup() {

    // set the speed at 60 rpm:
    myStepper.setSpeed(60);
}

void loop() {
  
   myStepper.step(stepsPerRevolution);
   delay(500);
   myStepper.step(-stepsPerRevolution);
   delay(500);
}
