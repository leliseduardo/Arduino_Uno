/* 

        Este código é copiado do professor e serve para demonstrar o uso do display LCD com I2C. Para descobrir o endereço I2C do display é necessário utilizar o programa
    I2C_Scanner, presente na pasta deste projeto.

*/


// ========================================================================================================
// --- Bibliotecas Auxiliares ---
#include <Wire.h>
#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd(0x3F,2,1,0,4,5,6,7,3, POSITIVE);


// ========================================================================================================
// --- Configurações Iniciais ---
void setup()
{
 lcd.begin (16,2);

 
} //end setup


// ========================================================================================================
// --- Loop Infinito ---
void loop()
{
  lcd.setBacklight(HIGH);
  lcd.setCursor(0,0);
  lcd.print("Hello World");
  lcd.setCursor(0,1);
  lcd.print("Display I2C!!!");
  delay(1000);
  lcd.setBacklight(LOW);
  delay(1000);
  
} //end loop
