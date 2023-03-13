/* 

        O objetivo deste programa é realizar o controle suave de servo motores, fazendo ele se deslocar a um ângulo a outro em determinado tempo. Para isso, será utilizada
    a biblioteca do servo, denominada "Servo.h". Esta biblioteca faz o controle dos motores a partir das interrupções do microcontrolador ATMega328P, presente no Arduíno, 
    fazendo com que o código fique limpo, não sofrendo com delays que travam a execução.
        Difrentemente do professor, na função "movimentoSuave", eu programei o tempo de giro do motor como sendo o tempo real que foi passado para a função, em milisegundos.
    Na função análoga do professor, o tempo passado tem que ser multiplicado pelo intervalo de angulos em que o motor irá girar. Isto é, na função do professor, se é passado
    o valor 1000ms = 1s, e os angulos de inicio = 0 e fim = 180, o servo irá demorar 180*1000ms = 180s, que dá mais de 2min. Se passar o tempo de 10ms, 180*10ms = 1.8s. Logo,
    na minha função eu preferi passar o tempo real, dividindo o tempo passado pelo intervalo de ângulos. Ex: Na minha função, se eu passar 1000ms, e os angulos 0 e 180, o tempo
    de rotação será t = (1000/(180-0))*180 = 1000ms = 1s. Dessa forma, o tempo de rotação é o mesmo tempo passado. Para se entender melhor, basta ver o código da função
    "movimentoSuave" escrito abaixo.

        Na simulação e na prática o circuito e o programa funcionaram perfeitamente.     

*/

// Inclusão de bibliotecas
#include <Servo.h>

// Mapeamento de hardware
#define servoPin 12                                      // Cria mnemônico para o pino 12 do Arduino

// Variáveis auxiliares
Servo motor;

// Funções auxiliares
void movimentoSuave(const int tempo, int inicio, int fim);

void setup() {

    pinMode(servoPin, OUTPUT);                              // Configura servoPin como saída. Com a utilização da biblioteca Servo não é necessário, mas é boa prática

    motor.attach(servoPin);                                 // Configura o pino 12, servoPin, como o pino de controle do servo motor

    motor.write(90);                                        // Inicia motor em 90 graus
    delay(1000);                                            // Aguarda 1000ms = 1s

} // end void setup

void loop() {

    movimentoSuave(100, 30, 120);

    delay(1000);

    movimentoSuave(100, 120, 30);

    delay(1000);
    
} // end void loop


void movimentoSuave(const int tempo, int inicio, int fim){
  
    bool control;

    if(inicio < fim)
      control = 0;
    else
      control = 1;

    if(!control){

      for(int i=inicio; i < fim; i++){

        int aux = fim - inicio;

        motor.write(i);

        delay(tempo/aux);
        
      } // end for
    } // end if

    if(control){

      for(int i=inicio; i > fim; i--){

        int aux = inicio - fim;

        motor.write(i);

        delay(tempo/aux);
        
      } // end for
    } // end if
    
  
} // end void movimentoSuave
