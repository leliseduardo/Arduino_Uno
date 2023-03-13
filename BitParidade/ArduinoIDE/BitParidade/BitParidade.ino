/* ========================================================================================================
 
   Este código é copiado do professor e tem a intenção de demonstra e explicar o bit de paridade.


   Bit de Paridade


   Transmissão de Dados com Arduino comunicação Síncrona

    
   Autor: Eng. Wagner Rambo  Data: Outubro de 2018
   
   www.wrkits.com.br | facebook.com/wrkits | youtube.com/user/canalwrkits 


  Exemplo de transmissão síncrona

        _   _   _   _   _   _   _   _   _   _   _   _   _
Clock _| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_ ...
              ___         _______     ___     _______
Dado  _______|   |_______|       |___|   |___|       |_____ ...
       0   0   1   0   0   1   1   0   1   0   1   1   0

Paridade: Análise do número de 1's presente na mensagem
É uma forma de detecção de erro em um sistema de comunicação.
Pouca eficiência, no entanto simples de implementar.

Par  (Even) -> bit de paridade é 0
Ímpar (Odd) -> bit de paridade é 1


Bit de Paridade Exemplo H (ASCII Table):

byte 01001000

Comumente utiliza-se o bit menos significativo para representar a paridade

byte H com bit de paridade 1001000 0  <- se 0, não há erro
                           1101000 1  <- se 1, há erro na transmissão


Problema: 

byte H com bit de paridade 1001011 0 <- está em 0, porém há DOIS bits errados!


     
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
const char *message = "Hgllo World!";

/*
      H        g        l        l        o      space
   01001000 01100111 01101100 01101100 01101111 00100000

      W        o        r        l        d        !
   01010111 01101111 01110010 01101100 01100100 00100001


*/


int p_count = 0;


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
          if(tx_bit) p_count += 1;
          lcd.setCursor(i,0);
          lcd.cursor();


          digitalWrite(sig_clk,  HIGH);
          delay((1000/tx_rate) / 2);
          digitalWrite(sig_clk,   LOW);

          
      } //end for aninhado

  } //end for


  digitalWrite(tx_data, LOW);

  lcd.setCursor(11,1);
  lcd.print(p_count);
   

} //end setup




void loop() 
{
 

}
