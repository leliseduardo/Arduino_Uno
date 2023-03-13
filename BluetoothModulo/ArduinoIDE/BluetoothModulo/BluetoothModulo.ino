/* ========================================================================================================
 
   Este código é copiado do professor e tem a função de iniciar o uso do módulo Bluetooth. Pelo código é possível notar o quanto é simples a comunicação com o módulo.


   Hello World Módulo Bluetooth!

    
   Autor: Eng. Wagner Rambo  Data: Janeiro de 2019
   
   www.wrkits.com.br | facebook.com/wrkits | youtube.com/user/canalwrkits | dailymotion.com/wrkits


   Hardware:

               HC-05
                RX
 Arduino   ____  |  ____
 D1 TX ---|____|-o-|____|--- GND
           1.5k     2.2k

 Arduino      HC-05
 D0 RX  -----  TX
    5V  -----  VCC
   GND  -----  GND 
           
======================================================================================================== */


// ========================================================================================================
// --- Bibliotecas Auxiliares ---



// ========================================================================================================
// --- Configurações Iniciais ---
void setup()
{
  Serial.begin(9600);

  
} //end setup


// ========================================================================================================
// --- Loop Infinito ---
void loop()
{
  Serial.println("Hello World WR Bluetooth");

  delay(741);
  

  
} //end loop














  
