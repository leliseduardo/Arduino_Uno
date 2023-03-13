/* 

                Este código é copiado do professor e tem a função de utilizar um sensor de Lux, ou luminosidade. Este sensor nada mais é do que o um sensor de luz num módulo
        I2C. 

*/


// ========================================================================================================
// --- Bibliotecas Auxiliares ---
#include <Wire.h>
#include <BH1750.h>


// ========================================================================================================
// --- Mapeamento de Hardware ---
#define   led   13


// ========================================================================================================
// --- Definição de Objetos ---
BH1750 lightMeter;


// ========================================================================================================
// --- Configurações Iniciais ---
void setup()
{
  Serial.begin(115200);

  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);

  lightMeter.begin();
  
} //end setup


// ========================================================================================================
// --- Loop Infinito ---
void loop()
{
 
  unsigned lux = lightMeter.readLightLevel();
  
 
  Serial.print("Luminosidade: ");
  Serial.print(lux);
  Serial.println(" lux");

  if(lux < 400) digitalWrite(led, HIGH);
  else          digitalWrite(led,  LOW);
  
  delay(741);
  

} //end loop
