/* ======================================================================================================
   
   Curso de Arduino WR Kits Channel
   
   Display Gráfico 128x64 e sensor de umidade/temperatura

   
    
   Autor: Eng. Wagner Rambo  Data: Agosto de 2018
    
   
   www.wrkits.com.br | facebook.com/wrkits | youtube.com/canalwrkits

 


====================================================================================================== */


// ======================================================================================================
// --- Bibliotecas ---
#include <U8glib.h>
#include <dht.h>


// ======================================================================================================
// --- Declaração de Objetos ---

//display gráfico 128x64
U8GLIB_ST7920_128X64_1X u8g( 6,  //E
                             5,  //R/W
                             4,  //RS
                             7); //RST
//DHT11
dht     myDHT;
#define DHT_pin   8


// ======================================================================================================
// --- Variáveis Globais ---
char *temp_str = "00.0";        //armazena a string de temperatura
char *hum_str  = "00.0";        //armazena a string de umidade
float hum_perc, temp_C;         //variáveis para umidade e temperatura


// ======================================================================================================
// --- Configurações Iniciais ---
void setup() 
{  

               
   u8g.setFont(u8g_font_courB10);   //seleciona fonte para display

   u8g.setColorIndex(1);            //desenhar com pixels on


} //end setup


// ======================================================================================================
// --- Loop Infinito ---
void loop() 
{
    
  u8g.firstPage();
  do {   
    draw();
  } while( u8g.nextPage() );

 
} //end loop


// ======================================================================================================
// --- Desenvolvimento das Funções ---
void draw()
{

   u8g.drawFrame(4,0,120,31);            //desenha retângulo superior
   u8g.drawFrame(4,33,120,31);           //desenha retângulo inferior
   

   //coleta dados do DHT11
   myDHT.read11(DHT_pin);
   hum_perc  = myDHT.humidity;
   temp_C    = myDHT.temperature;
  
  
   // converte float para strings char u8g
   u8g.drawStr( 15, 13, "Temperatura");       //mostra temperatura
   dtostrf(temp_C, 3, 1, temp_str);
   u8g.drawStr(33,27, temp_str);
   u8g.drawStr(70,27, " C"); 

   u8g.drawStr(26,45, "Umidade");             //mostra umidade
   dtostrf(hum_perc, 3, 1, hum_str);
   u8g.drawStr(40,60, hum_str);
   u8g.drawStr(75,60, "%"); 

  
} //end draw
