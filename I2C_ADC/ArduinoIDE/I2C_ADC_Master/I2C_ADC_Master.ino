/* 

        O objetivo deste programa é configurar um Master para comunicação I2C. Este master irá enviar a informação lida pelo conversor AD, que estará conectado a um 
    potenciômetro. Logo, a leitura do potenciômetro feita pelo master, será usada no Slave.
        No Arduíno, a comunicação I2C funciona tando nos pinos SDA e SCL quanto nos pinos A4 e A5, respectivamente.

        Na prática o circuito funcionou perfeitamente.

*/

// Inclusão de bibliotecas
#include <Wire.h>

// Variáveis auxiliares
int x;

void setup() {
  
  Wire.begin();
}

void loop() {

  x = analogRead(A0);

  x = map(x, 0, 1023, 0, 255);
  
  Wire.beginTransmission(15);       
  Wire.write(x);              
  Wire.endTransmission(); 

  x++;
  delay(100);
}
