/* 

        Este programa tem a função de ler um sensor de movimento do tipo PIR e acionar uma saída e mudar a posição de um servo motor. O sensor PIR tem como saída um pulso de 
    nível alto ou baixo, numa duração que pode ser configurada. Na aula, o pulso foi configurado para ser de nível alto e durar aproximadamentes 1,2s. Assim, o Arduído terá a 
    função de identificar este pulso e acionar uma saída e o servo motor. 
        Para usar o servo motor, será incluída a biblioteca "Servo", para este tipo de motor.

        Na simulação o código funcionou como esperado. Já na prática, ele se demonstrou bem lento.

*/

// Inclusão de bibliotecas
#include <Servo.h>

// Mapeamento de hardware
#define saida 13                                  // Saída no pino digital 13
#define motor 12                                  // Servo motor no pino digital 12
#define pir    2                                  // Leitura do PIR no pino digital 2

// Funções auxiliares
void leitura_Sensor();
Servo m;

//Variáveis auxiliares
unsigned long leituraSensor = 0;

void setup() {

    pinMode(saida, OUTPUT);
    pinMode(motor, OUTPUT);
    pinMode(pir, INPUT);

    m.attach(motor);
    m.write(0);

    //Serial.begin(9600);

} // end void setup

void loop() {

    leitura_Sensor();

    if((leituraSensor > 1E6) && (leituraSensor <= 3E6)){
      
        digitalWrite(saida, HIGH);
        
        m.write(180);
        
    } // end if
    else{

        digitalWrite(saida, LOW);

        m.write(0);
      
    } // end else
  
} // end void loop



void leitura_Sensor(){
  
    leituraSensor = pulseIn(pir, HIGH, 3E6); // Faz a contagem do tempo em que o pulso do sensor se mantém em nível máximo, em us. Ainda, limita a contagem em 3s.
   
    //Serial.println(leituraSensor);           // Imprime na porta Serial o tempo em que o pulso do sensor se manteve em nível alto

} // end void leitura_Sensor
