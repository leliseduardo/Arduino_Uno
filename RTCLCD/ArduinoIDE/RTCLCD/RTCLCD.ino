/*
   
            Este código é copiado do professor. Ele novamente tem o intuito de utilizar o módulo RTC, mas agora para imprimir data e hora no display
   LCD, possibilitando muitas aplicações que necessitam de temporizações ou de data e hora.

   Mapeamento de Hardware
            DS3231    -> Arduino Duemilanove/UNO
            -----------------------------------------
            VCC pin   -> Arduino 5V
            GND pin   -> Arduino GND
            SDA pin   -> Arduino Analog 4 (SDA)  
            SCL pin   -> Arduino Analog 5 (SCL)  
            -----------------------------------------
    
   Autor: Eng. Wagner Rambo  Data: Novembro de 2016
   
   www.wrkits.com.br | facebook.com/wrkits | youtube.com/user/canalwrkits
   
*/


// --- Bibliotecas ---
#include <DS3231.h>             //Inclui a biblioteca do DS3231 Shield
#include <LiquidCrystal.h>      //Biblioteca para o display LCD


// --- Comunicação I2C ---
DS3231  rtc(SDA, SCL);


// --- Hardware do LCD ---
LiquidCrystal disp(8,  //RS no digital 8
                   7,  //EN no digital 7
                   5,  //D4 no digital 5
                   4,  //D5 no digital 4
                   3,  //D6 no digital 3
                   2); //D7 no digital 2


// --- Configurações Iniciais ---
void setup()
{
 
  Serial.begin(115200);          //Inicia comunicações Serial em 115200 baud rate
 
  rtc.begin();                   //Inicializa RTC
  disp.begin(16,2);              //Inicializa LCD 16 x 2
  disp.clear();                  //Limpa LCD
  
  
  //Descomente as linhas a seguir para configurar o horário, após comente e faça o upload novamente para o Arduino
  //rtc.setDOW(MONDAY);     // Set Day-of-Week to SUNDAY
  //rtc.setTime(16,30, 0);     // Set the time to 12:00:00 (24hr format)
  //rtc.setDate(28,11,2016);
} //end setup


// --- Loop Infinito ---
void loop()
{
  //Imprime o dia da semana
  Serial.print(rtc.getDOWStr());
  Serial.print(" ");
  Serial.print(" -- ");
  Serial.print(" ");

   disp.setCursor(0,0);                                 //Posiciona cursor na coluna 1, linha 1
   disp.print(rtc.getTimeStr());                        //Imprime horário
   disp.setCursor(0,1);                                 //Posiociona cursor na coluna 1, linha 2
   disp.print(rtc.getDateStr());                        //Imprime a data

  //Imprime o horário
  Serial.println(rtc.getTimeStr());
  
  
  delay (100); //taxa de atualização
  
} //end loop
