/* 

        O objetivo deste programa é receber um dado pelo I2C, enviado pelo master. Portanto, este código configura um Slave para comunicação I2C.

       Na simulação o programa funcionou como esperado. 

*/


#include <Wire.h>

void setup() {
  Wire.begin(15);                
  Wire.onReceive(receiveEvent); 
  Serial.begin(9600); 
}         

void loop() {
  delay(100);
}

void receiveEvent(int howMany) {
  while (1 < Wire.available()) { 
    char c = Wire.read();
    Serial.print(c);      
  }
  int x = Wire.read();    
  Serial.println(x);         
}
