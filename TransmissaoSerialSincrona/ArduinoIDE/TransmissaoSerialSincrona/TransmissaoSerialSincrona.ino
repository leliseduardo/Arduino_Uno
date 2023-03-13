/* ========================================================================================================
 
   Este código foi copiado do professor e tem a função de demonstrar a comunicação serial síncrona. Ele criou a comunicação e ela é muito parecida com as últimas duas aulas, porém,
   agora a comunicação utiliza um clock e, portanto, é síncrona.


   Transmissão de Dados com Arduino comunicação Síncrona

    
   Autor: Eng. Wagner Rambo  Data: Outubro de 2018
   
   www.wrkits.com.br | facebook.com/wrkits | youtube.com/user/canalwrkits 


  Exemplo de transmissão síncrona

        _   _   _   _   _   _   _   _   _   _   _   _   _
Clock _| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_ ...
              ___         _______     ___     _______
Dado  _______|   |_______|       |___|   |___|       |_____ ...
       0   0   1   0   0   1   1   0   1   0   1   1   0
 
     
======================================================================================================== */


// ========================================================================================================
// --- Bibliotecas Auxiliares ---
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

 
// ========================================================================================================
// --- Mapeamento de Hardware ---
#define  tx_data   13
#define  sig_clk   12


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
  pinMode(sig_clk, OUTPUT);


  lcd.begin(16,2);
  lcd.setBacklight(LOW);
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
          delay((1000/tx_rate) / 2);
          
          lcd.noCursor();
          lcd.setCursor(j, 1);
          lcd.print(tx_bit ? "1" : "0");
          lcd.setCursor(i,0);
          lcd.cursor();


          digitalWrite(sig_clk,  HIGH);
          delay((1000/tx_rate) / 2);
          digitalWrite(sig_clk,   LOW);

          
      } //end for aninhado

  } //end for


  digitalWrite(tx_data, LOW);
   

} //end setup




void loop() 
{
 

}
