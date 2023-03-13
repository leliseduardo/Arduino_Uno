/* 

        O objetivo deste programa é configurar o Arduíno como Slave de uma comunicação I2C. Este Slave irá receber uma leitura feita pelo ADC do Master e utiliza-la para 
    controlar uma saída PWM, que estará ligada a um led. Logo, a leitura de um potenciômetro pelo ADC do Master irá controlar o brilho de um led no Slave, através do PWM.
        No Arduíno, a comunicação I2C funciona tando nos pinos SDA e SCL quanto nos pinos A4 e A5, respectivamente.

        Na prática o circuito funcionou perfeitamente.

*/

// Inclusão de bibliotecas
#include <Wire.h>

// Mapeamento de hardware
#define led 3                     // Cria mnemônico para led, no pino 3

void setup() {

  pinMode(led, OUTPUT);
  
  Wire.begin(15);                
  Wire.onReceive(receiveEvent); 
}         

void loop() {
  delay(100);
}

void receiveEvent(int howMany) {
  
  int x = Wire.read();    
  analogWrite(led, x);            // Usa PWM em led, com duty = x     
}
