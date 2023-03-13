/* ========================================================================================================
 
   Este código é copiado do professor e tem a função de criar caracteres gigantes no display LCD.

   Caracteres Gigantes em Display LCD 16x2
    
   Autor: Eng. Wagner Rambo  Data: Dezembro de 2018
   
   www.wrkits.com.br | facebook.com/wrkits | youtube.com/user/canalwrkits 

     
======================================================================================================== */


// ========================================================================================================
// --- Bibliotecas Auxiliares ---
#include <LiquidCrystal.h>                //biblioteca LCD
 

// ========================================================================================================
// --- Constantes ---
LiquidCrystal lcd(12, 11, 5, 4, 3, 7);


// ========================================================================================================
// --- Protótipo das Funções ---
void disp_num(int num);
void char0();
void char1();
void char2();
void char3();


// ========================================================================================================
// --- Variáveis Globais ---
int cnt_num = 0;

// Segmentos personalizados
byte segF[8] = 
{
  B00111,  
  B01111,  
  B11111,  
  B11111,  
  B11111,  
  B11111,  
  B11111,  
  B11111
};

byte segA[8] =
{
  B11111,  
  B11111,  
  B11111,  
  B00000,  
  B00000,  
  B00000,  
  B00000,  
  B00000
};

byte segB[8] =
{
  B11100,  
  B11110,  
  B11111,  
  B11111,  
  B11111,  
  B11111,  
  B11111,  
  B11111
};

byte segC[8] =
{
  B11111,  
  B11111,  
  B11111,  
  B11111,  
  B11111,  
  B11111,  
  B11110,  
  B11100
};


byte segD[8] =
{
  B00000,  
  B00000,  
  B00000,  
  B00000,  
  B00000,  
  B11111,  
  B11111,  
  B11111
};


byte segE[8] =
{
  B11111,  
  B11111,  
  B11111,  
  B11111,  
  B11111,  
  B11111,  
  B01111,  
  B00111
};


byte segG[8] =
{
  B11111,  
  B11111,  
  B11111,  
  B00000,  
  B00000,  
  B00000,  
  B11111,  
  B11111
};


// ========================================================================================================
// --- Configurações Iniciais ---
void setup()
{
  
  lcd.createChar(0,segF);
  lcd.createChar(1,segA);
  lcd.createChar(2,segB);
  lcd.createChar(3,segE);
  lcd.createChar(4,segD);
  lcd.createChar(5,segC);
  lcd.createChar(6,segG);
 
  lcd.begin(16, 2);  

 
} //end setup


// ========================================================================================================
// --- Loop Infinito ---
void loop()
{
  
  disp_num(cnt_num);
  delay(741);

  cnt_num += 1;
  if(cnt_num > 3) cnt_num = 0;
  lcd.clear();
 

} //end loop


// ========================================================================================================
// --- Desenvolvimento das Funções ---


void disp_num(int num)  
{
  
   switch(num)
   {
      case 0: char0(); break;
      case 1: char1(); break;
      case 2: char2(); break;
      case 3: char3(); break;
  
   } //end switch
   
} // end disp_num




// ========================================================================================================
// --- Gera os "segmentos" para o caractere 0 ---
void char0()
{ 
  lcd.setCursor(5, 0);   //linha 1
  lcd.write((byte)0);    //segmento F
  lcd.write((byte)1);    //segmento A
  lcd.write((byte)2);    //segmento B
  lcd.setCursor(5, 1);   //linha 2
  lcd.write((byte)3);    //segmento E
  lcd.write((byte)4);    //segmento D
  lcd.write((byte)5);    //segmento C
  
} //end char0


// ========================================================================================================
// --- Gera os "segmentos" para o caractere 1 ---
void char1()
{ 
  lcd.setCursor(5+2, 0);   //linha 1
  lcd.write((byte)2);    //segmento B
  lcd.setCursor(5+2, 1);   //linha 2
  lcd.write((byte)5);    //segmento C
  
} //end char1


// ========================================================================================================
// --- Gera os "segmentos" para o caractere 2 ---
void char2()
{ 
  lcd.setCursor(5+1, 0);   //linha 1
  lcd.write((byte)6);    //segmento G
  lcd.write((byte)2);    //segmento B
  lcd.setCursor(5, 1);   //linha 2
  lcd.write((byte)3);    //segmento E
  lcd.write((byte)4);    //segmento D
  
} //end char2


// ========================================================================================================
// --- Gera os "segmentos" para o caractere 3 ---
void char3()
{ 
  lcd.setCursor(5+1, 0);   //linha 1
  lcd.write((byte)6);    //segmento G
  lcd.write((byte)2);    //segmento B
  lcd.setCursor(5+1, 1);   //linha 2
  lcd.write((byte)4);    //segmento D
  lcd.write((byte)5);    //segmento C
  
} //end char3
