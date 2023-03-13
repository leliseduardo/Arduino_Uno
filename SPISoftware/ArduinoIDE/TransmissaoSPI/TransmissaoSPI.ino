/* =====================================================================================================

   Curso de Arduino e AVR 198
   
   WR Kits Channel

   Autor: Eng. Wagner Rambo  Data: Novembro de 2018
   
   www.wrkits.com.br | facebook.com/wrkits | youtube.com/user/canalwrkits 

   
  Serial Peripheral Interface (SPI)
  
  O protocolo SPI foi desenvolvido originalmente pela Motorola
  e adotado por diversos fabricante ao longo do tempo.
  Linhas:

  -> CS ou SS (Chip Select): a seleção de dispositivo é utilizada
  para selecionar ou habilitar o disposito com o qual se deseja
  comunicar e também para encerrar a execução dos comandos 
  transmitidos pelo dispositivo mestre.;
  -> Clock ou SCLK: utilizada para sincronização entre o dispositivo
  mestre e o dispositivo escravo. O sinal deve ser simétrico
  (duty de 50%) e a informação de saída estar disponível no
  mínimo por 30ns antes da borda de subida de clock e lida até
  30ns antes da borda de descida de clock;
  -> SI ou MOSI: Entrada Serial, linha de recepção de dados;
  -> SO ou MISO: Saída Serial, linha de transmissão de dados.



  Exemplo de transmissão de dispositivo Mestre para Escravo

              ___         _______     ___     _______
MOSI  _______|   |_______|       |___|   |___|       |_____ ...
           0   1   0   0   1   1   0   1   0   1   
        _   _   _   _   _   _   _   _   _   _   _   _   _
SCLK  _| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_ ...

      ___                                         _________ ...
CS       |_______________________________________|


===================================================================================================== */


// ========================================================================================================
// --- Bibliotecas Auxiliares ---
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

 
// ========================================================================================================
// --- Mapeamento de Hardware ---
#define  tx_data   11   //MOSI
#define  sig_clk   10   //SCLK
#define  cs_pin     9   //Chip Select


// ========================================================================================================
// --- Constantes e Objetos ---
#define  tx_rate   25 //bits por segundo

LiquidCrystal_I2C lcd(0x3F,2,1,0,4,5,6,7,3, POSITIVE);


// ========================================================================================================
// --- Protótipo das Funções ---
void send_data(char *message);


// ========================================================================================================
// --- Variáveis Globais ---
const char *message = "WR";


// =====================================================================================================
// --- Configurações Iniciais ---
void setup() 
{

  pinMode(tx_data, OUTPUT);
  pinMode(sig_clk, OUTPUT);
  pinMode(cs_pin,  OUTPUT);
  digitalWrite(cs_pin, HIGH);

  lcd.begin(16,2);
  lcd.setBacklight(LOW);
  lcd.setCursor(0,0);
  lcd.print(message);


  

} //end setup


// =====================================================================================================
// --- Loop Infinito ---
void loop() 
{
   send_data(message);

   delay(741);

} //end loop


// =====================================================================================================
// --- Desenvolvimento das Funções ---
void send_data(char *message)
{
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

          digitalWrite(cs_pin, LOW);
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
  digitalWrite(cs_pin, HIGH);
  
  
} //end send_data
