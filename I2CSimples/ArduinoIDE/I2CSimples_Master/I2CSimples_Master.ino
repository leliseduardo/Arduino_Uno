/* 

        O objetivo deste programa é configurar um Master para comunicação I2C. Este código irá enviar uma String e um byte numérico ao Slave.

        Na simulação o programa funcionou como esperado.

*/

#include <Wire.h>

void setup() {
  Wire.begin();
}

byte x = 0;

void loop() {
  Wire.beginTransmission(15); 
  Wire.write("x is ");        
  Wire.write(x);              
  Wire.endTransmission(); 

  x++;
  delay(500);
}
