/*
   
              Este código é copiado do professor e tem a função de utilizar o módulo RTC DS3231 para data e hora. Neste código, essas informações serão
        mostradas no serial monitor, com baud rate de 115200.

   Mapeamento de Hardware
            DS3231    -> Arduino Mega 2560
            -----------------------------------------
            VCC pin   -> Arduino 5V
            GND pin   -> Arduino GND
            SDA pin   -> Arduino Digital 20 (SDA)  
            SCL pin   -> Arduino Digital 21 (SCL)  
            -----------------------------------------
    
   Autor: Eng. Wagner Rambo  Data: Novembro de 2016
   
   www.wrkits.com.br | facebook.com/wrkits | youtube.com/user/canalwrkits
   
*/


// --- Bibliotecas ---
#include <DS3231.h>          //Inclui a biblioteca do DS3231 Shield


// --- Comunicação I2C ---
DS3231  rtc(SDA, SCL);


// --- Configurações Iniciais ---
void setup()
{
 
  Serial.begin(115200);          //Inicia comunicações Serial em 115200 baud rate
 
  rtc.begin();                   //Inicializa RTC
  
  //Descomente as linhas a seguir para configurar o horário, após comente e faça o upload novamente para o Arduino
  //rtc.setDOW(WEDNESDAY);     // Set Day-of-Week to SUNDAY
  //rtc.setTime(12,42, 0);     // Set the time to 12:00:00 (24hr format)

} //end setup


// --- Loop Infinito ---
void loop()
{
  //Imprime o dia da semana
  Serial.print(rtc.getDOWStr());
  Serial.print(" ");
  Serial.print(" -- ");
  Serial.print(" ");

  //Imprime o horário
  Serial.println(rtc.getTimeStr());
  
  //Atualiza monitor a cada segundo
  delay (1000);
  
} //end loop
