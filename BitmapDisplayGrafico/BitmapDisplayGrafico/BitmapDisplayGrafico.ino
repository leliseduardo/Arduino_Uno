/* ======================================================================================================
   
   Curso de Arduino WR Kits Channel
   
   Display Gráfico 128x64

   Imagem Bitmap
   
    
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
// --- Imagem Bitmap ---
const uint8_t img_bitmap[] U8G_PROGMEM = {
  
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x70, 0x30, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0xfa,
   0xff, 0xff, 0x05, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x44, 0x7f, 0x7c, 0xf8, 0x5f, 0x60, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x03, 0x7c, 0x00, 0xfe, 0x02,
   0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x00,
   0xfc, 0x00, 0xe4, 0x0f, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x1f, 0x00, 0xfc, 0x00, 0xa4, 0x0f, 0x40, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x0f, 0x00, 0xfe, 0x00, 0xe4, 0x1f,
   0x00, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x1f, 0x00,
   0x7e, 0xe0, 0xff, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x19, 0xb7, 0xff, 0xff, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0xfe, 0x01, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x03, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x20, 0x00,
   0x00, 0xc0, 0x01, 0x00, 0x00, 0x40, 0x30, 0x00, 0x00, 0x00, 0x00, 0x90,
   0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x80, 0x11, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00,
   0x00, 0xa0, 0x0d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0xfc, 0x00, 0x00, 0x00, 0x00,
   0x04, 0x00, 0x00, 0xf0, 0x03, 0x00, 0x08, 0x00, 0x00, 0x50, 0x00, 0xff,
   0x03, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0xfc, 0x0f, 0xc0, 0x0f, 0x00,
   0x00, 0x00, 0x80, 0xff, 0x0f, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0xfe,
   0x3f, 0xf8, 0x0f, 0x00, 0x00, 0x00, 0xc0, 0xff, 0x1f, 0x00, 0x00, 0x00,
   0x04, 0x00, 0x00, 0xff, 0x3f, 0xf8, 0x0f, 0x00, 0x00, 0x88, 0xf1, 0x5f,
   0x1f, 0x01, 0x3f, 0x00, 0x00, 0x00, 0x90, 0xaf, 0x7d, 0xfc, 0x0f, 0x00,
   0x00, 0xfc, 0xef, 0x53, 0x3f, 0x01, 0xff, 0xff, 0xff, 0xff, 0x83, 0xaf,
   0xfd, 0xff, 0x0b, 0x00, 0x00, 0xfc, 0xff, 0xde, 0x3d, 0x51, 0xfe, 0xff,
   0xff, 0xff, 0xc7, 0xdb, 0xf7, 0x0f, 0x0c, 0x00, 0x00, 0xfc, 0xff, 0xe9,
   0x7a, 0xff, 0xf8, 0xff, 0xff, 0xff, 0xff, 0x37, 0xe9, 0xff, 0x0f, 0x00,
   0x00, 0xb4, 0x7f, 0xff, 0xfb, 0xfe, 0x01, 0x00, 0x00, 0x00, 0xe2, 0xfd,
   0xef, 0xff, 0x07, 0x00, 0x00, 0xc0, 0x7f, 0x50, 0xfe, 0xff, 0x07, 0x00,
   0xc0, 0xff, 0xff, 0x21, 0xf9, 0xff, 0x00, 0x00, 0x00, 0xf0, 0x7f, 0x73,
   0xfe, 0xff, 0xff, 0xff, 0x7f, 0xf0, 0xff, 0xcd, 0xec, 0x3f, 0x00, 0x00,
   0x00, 0xc0, 0xff, 0x04, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x1b,
   0x66, 0x00, 0x00, 0x00, 0x00, 0x00, 0xcf, 0xa8, 0xba, 0x07, 0x00, 0x00,
   0x00, 0x00, 0x80, 0x2b, 0x75, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xa9,
   0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf3, 0x7a, 0x00, 0x00, 0x00,
   0x00, 0x00, 0xf8, 0x23, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xcf,
   0xfc, 0x07, 0x00, 0x00, 0x00, 0x00, 0xfc, 0xdf, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0x3f, 0xff, 0x0f, 0x00, 0x00, 0x00, 0x00, 0xf8, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x03, 0x00, 0x00,
   0x00, 0x00, 0x00, 0xfe, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8,
   0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00

    };       

  
// ======================================================================================================
// --- Protótipo das Funções ---
void bitmap();                      //função para gerar o bitmap


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
     bitmap();
  } while( u8g.nextPage() );

   
} //end loop


// ======================================================================================================
// --- Desenvolvimento das Funções ---


// ======================================================================================================
// --- Função bitmap ---
void bitmap() 
{
  
  u8g.drawXBMP( 0, 0, 128, 64, img_bitmap);

  
} //end bitmap


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
