/* ========================================================================================================
 
   Este código é copiado do professor e tem a função de comunicar o terminal Serial com o LCD, de forma que, quando se escreve algo no terminal Serial o conteúdo que foi escrito vá 
   para a o display. 
   
   Envio de caracteres para o LCD em tempo real
    
   Autor: Eng. Wagner Rambo  Data: Dezembro de 2018
   
   www.wrkits.com.br | facebook.com/wrkits | youtube.com/user/canalwrkits 

     
======================================================================================================== */


// ========================================================================================================
// --- Bibliotecas Auxiliares ---
#include <LiquidCrystal.h>               //biblioteca LCD


// ========================================================================================================
// --- Objetos ---
LiquidCrystal lcd(12, 11, 5, 4, 3, 7);   //ligações Arduino - LCD


// ========================================================================================================
// --- Variáveis Globais ---
void send_str(bool line_num);           //função que envia strings do terminal para o LCD


// ========================================================================================================
// --- Variáveis Globais ---
boolean line_n = 1;                     //armazena o número da linha do LCD


// ========================================================================================================
// --- Configurações Iniciais ---
void setup()
{
   
  lcd.begin(16, 2);                     //lcd 16 colunas, 2 linhas
 
  Serial.begin(115200);                 //inicia serial 115200 baud rate
  
  Serial.print("Aguardando entradas na serial...");  //imprime
   
} //end setup


// ========================================================================================================
// --- Loop Infinito ---
void loop()
{

   if(line_n) send_str(line_n);  //se line_n verdadeiro, envie string na linha 1
  
   else send_str(line_n);        //senão, é falso, envia string na linha 2

   
} //end loop


// ========================================================================================================
// --- Desenvolvimento das Funções ---
void send_str(bool line_num)
{
   
   //lê todos os caracteres disponíveis
   if (Serial.available()) 
   {
  
      //aguarda receber mensagem completa
      delay(100);

      //determina a linha do display
      if(line_num) { lcd.setCursor(0,0);  line_n = 0;  }
      else         { lcd.setCursor(0,1);  line_n = 1;  }
    
      //mostra os caracteres no LCD
      while (Serial.available() > 0)  lcd.write(Serial.read()); 

      //envia espaços para limpeza "manual" do LCD
      for(int i=0; i<15; i++) lcd.print(" ");
  
   } //end Serial available 
  
  
} //end send_str
