/* ========================================================================================================
 
   Este código é copiado do professor e tem a função de criar um recpetor para o transmissor serial criado na última aula. O protocolo utilizado é serial e a forma como ocorrerá a comu-
   nicação foi criada pelo professor, definindo o tempo e as configurações necessárias para o transmisso e receptor conversarem.


   Recepção de Dados com Arduino

    
   Autor: Eng. Wagner Rambo  Data: Outubro de 2018
   
   www.wrkits.com.br | facebook.com/wrkits | youtube.com/user/canalwrkits 


   Objetivo: Receber pacotes de 8 bits por NRZ
   
   NRZ none return to zero encoding
       ___         _____
   ___|   |_______|     |_____ . . .
    0   1   0 0 0   1 1   0 0

 
   
======================================================================================================== */


// ========================================================================================================
// --- Bibliotecas Auxiliares ---
#include <LiquidCrystal.h>


// ========================================================================================================
// --- Mapeamento de Hardware ---
#define   rx_data   13


// ========================================================================================================
// --- Constantes e Objetos ---
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


// ========================================================================================================
// --- Variáveis Globais ---
char message[16];
byte rx_byte = 0;
int bit_pos = 0;


// ========================================================================================================
// --- Configurações Iniciais ---
void setup() 
{
 
  pinMode(rx_data, INPUT);

  strcpy(message, "");
  lcd.begin(16,2);

 
} //end setup


// ========================================================================================================
// --- Loop Infinito ---
void loop() 
{
   delay(200);
   bool rx_bit = digitalRead(rx_data);

   if(bit_pos == 8)
   {
     rx_byte = 0x00;
     bit_pos = 0x00;
    
   } //end if bit_pos
   
   if(rx_bit)
   {
     rx_byte |= (0x80 >> bit_pos);
    
   } //end rx_bit

   bit_pos += 0x01;

   if(bit_pos == 8)
   {
     strncat(message, &rx_byte, 1);
    
   } //end if bit_pos


   lcd.setCursor(0,0);
   lcd.print(message);
   lcd.setCursor(0,1);

   for(int i=0; i<8; i+=1)
   {
     if(i < bit_pos)
     {
       lcd.print(rx_byte & (0x80 >> i) ? "1" : "0");
     
     } //end if aninhado
     else
     {
       lcd.print(" ");
      
     } //end else aninhado
     
   } //end for

   lcd.setCursor(strlen(message), 0);
   lcd.cursor();

  
} //end loop
