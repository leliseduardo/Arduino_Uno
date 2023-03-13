/* ======================================================================================================
   
   Curso de Arduino WR Kits Channel
   
   Display Gráfico 128x64
   
    
   Autor: Eng. Wagner Rambo  Data: Julho de 2018
    
   
   www.wrkits.com.br | facebook.com/wrkits | youtube.com/canalwrkits

 


====================================================================================================== */


// ======================================================================================================
// --- Bibliotecas ---
#include <U8glib.h>


// ======================================================================================================
// --- Objetos ---
U8GLIB_ST7920_128X64_1X u8g( 6,  //E
                             5,  //R/W
                             4,  //RS
                             7); //RST

// ======================================================================================================
// --- Protótipo das Funções ---
void draw();                        //função para desenho de string
void disp_graph_init();             //função de inicialização do display


// ======================================================================================================
// --- Configurações Iniciais ---
void setup() 
{

   disp_graph_init();
  
} //end setup


// ======================================================================================================
// --- Loop Infinito ---
void loop() 
{

  u8g.firstPage();  
  do {
    draw();
  } while( u8g.nextPage() );
  
  delay(100);
  
} //end loop


// ======================================================================================================
// --- Desenvolvimento das Funções ---


// ======================================================================================================
// --- Função para desenho de strings ---
void draw() 
{
  
  u8g.setFont(u8g_font_unifont);
 
  u8g.drawStr( 30, 25, "Hello World!");
  
} //end draw


// ======================================================================================================
// --- Função de inicialização do Display ---
void disp_graph_init()
{
  if ( u8g.getMode() == U8G_MODE_R3G3B2 ) {
    u8g.setColorIndex(255);     //branco
  }
  else if ( u8g.getMode() == U8G_MODE_GRAY2BIT ) {
    u8g.setColorIndex(3);         //máxima intensidade
  }
  else if ( u8g.getMode() == U8G_MODE_BW ) {
    u8g.setColorIndex(1);         // pixel on
  }
  else if ( u8g.getMode() == U8G_MODE_HICOLOR ) {
    u8g.setHiColorByRGB(255,255,255);
  }

} //end disp_graph_init
