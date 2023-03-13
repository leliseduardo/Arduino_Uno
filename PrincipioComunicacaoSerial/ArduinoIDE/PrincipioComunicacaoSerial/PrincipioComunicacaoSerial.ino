/* ========================================================================================================
 
   Este código é copiado do professor e tem a função de demonstrar a transmissão serial simples, através da porta 13, escolhida pelo professor. Esta aula demonstra a criação de um pro-
   tocolo de transmissão serial criado pelo professor, e faz entender como este tipo de comunicação funciona.

   Transmissão de Dados com Arduino

    
   Autor: Eng. Wagner Rambo  Data: Setembro de 2018
   
   www.wrkits.com.br | facebook.com/wrkits | youtube.com/user/canalwrkits 


  Exemplos de transmissão
   
   NRZ none return to zero encoding
       ___         _____
   ___|   |_______|     |_____ . . .
    0   1   0 0 0   1 1   0 0

   RZ return to zero
             ___
   __     __|   |__     ___
     |___|         |___|   |___ . . .
       0      1      0       0
     
   
======================================================================================================== */


// ========================================================================================================
// --- Bibliotecas Auxiliares ---
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

 
// ========================================================================================================
// --- Mapeamento de Hardware ---
#define  tx_data   13


// ========================================================================================================
// --- Constantes e Objetos ---
#define  tx_rate   5 //bits por segundo

LiquidCrystal_I2C lcd(0x3F,2,1,0,4,5,6,7,3, POSITIVE);


// ========================================================================================================
// --- Variáveis Globais ---
const char *message = "Hello World!";


// ========================================================================================================
// --- Configurações Iniciais ---
void setup() 
{
  pinMode(tx_data, OUTPUT);

  lcd.begin(16,2);
  lcd.setBacklight(HIGH);
  lcd.setCursor(0,0);
  lcd.print(message);

  for(int i=0; i<strlen(message); i++)
  {
      char tx_byte = message[i];

      //limpa a segunda linha do LCD
      lcd.noCursor();
      lcd.setCursor(0,1);
      lcd.print("        ");
      lcd.setCursor(i,0);
      lcd.cursor();

      for(int j=0; j<8; j++)
      {
          bool tx_bit = tx_byte & (0x80 >> j);
    
          digitalWrite(tx_data,tx_bit);

          lcd.noCursor();
          lcd.setCursor(j, 1);
          lcd.print(tx_bit ? "1" : "0");
          lcd.setCursor(i,0);
          lcd.cursor();

          
          delay(1000/tx_rate);
          
      } //end for aninhado

  } //end for


  digitalWrite(tx_data, LOW);
   

} //end setup




void loop() 
{
 

}
