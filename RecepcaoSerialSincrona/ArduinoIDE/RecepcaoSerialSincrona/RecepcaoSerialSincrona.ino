/* ========================================================================================================
 
   Este código é copiado do professor e tem a função de configurar um receptor serial síncrono, com a comunicação que o professor criou e para receber os dados enviados pelo código da
   última aula.


   Recepção de Dados de forma síncrona com Arduino

    
   Autor: Eng. Wagner Rambo  Data: Outubro de 2018
   
   www.wrkits.com.br | facebook.com/wrkits | youtube.com/user/canalwrkits 


   Objetivo: Receber pacotes de 8 bits identificando a 
   borda de subida do clock do transmissor
   
   
======================================================================================================== */


// ========================================================================================================
// --- Bibliotecas Auxiliares ---
#include <LiquidCrystal.h>


// ========================================================================================================
// --- Mapeamento de Hardware ---
#define   rx_data   13


// ========================================================================================================
// --- Constantes e Objetos ---
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
#define  rx_rate   5 //bits por segundo


// ========================================================================================================
// --- Variáveis Globais ---
char message[16];
volatile byte rx_byte = 0;
volatile int bit_pos = 0;
volatile bool up_lcd = 1;


// ========================================================================================================
// --- Configurações Iniciais ---
void setup() 
{
 
  pinMode(rx_data, INPUT);

  strcpy(message, "");
  lcd.begin(16,2);

  attachInterrupt(0, risingClk, RISING);

 
} //end setup


// ========================================================================================================
// --- Loop Infinito ---
void loop() 
{

   if(up_lcd)
   {
     up_lcd = 0;
 
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

   } //end if up_lcd
   
} //end loop


void risingClk()
{
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
  
  
   up_lcd = 1;
  
} //end risingClk
