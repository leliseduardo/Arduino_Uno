/*

              Este código é copiado do professor e tem a função de demonstrar a leitura de um potenciômetro no display OLED. Pode-se dizer que o circuito funciona como um
       voltímetro, uma vez que imprime a tensão no pino central do potenciômetro.
              Assim que comprar um display OLED irei realizar estas práticas.

*/


// ========================================================================================================
// --- Bibliotecas Auxiliares ---
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


// ========================================================================================================
// --- Definições ---
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);
 
#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif


// ========================================================================================================
// --- Variáveis Globais ---
float   volt = 3.91;


// ========================================================================================================
// --- Configurações Iniciais ---
void setup()   
{                
 
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  //Inicializa OLED com endereço I2C 0x3C (para 128x64)
  display.clearDisplay();
  display.display();
  
} //end setup


// ========================================================================================================
// --- Loop Infinito ---
void loop() 
{
  display.setTextSize(4);
  display.setTextColor(WHITE);
  display.setCursor(0,20);
  display.clearDisplay();
  display.print(volt);
  display.print("V");
  display.display();

  volt = (analogRead(A0)*5.0)/1024.0;
  
  
} //end loop


 
 
