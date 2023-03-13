/*
  
              Este código é copiado do professor e demonstra o uso de um sensor de alicate amperímetro e o uso de sua biblioteca.
   
*/

// =============================================================================================================
// --- Bibliotecas ---
#include <LiquidCrystal.h>      //Biblioteca para o display LCD
#include "EmonLib.h"            //Biblioteca para o sensor de corrente
#include <SPI.h>                //Biblioteca SPI
 
EnergyMonitor emon1;            //cria objeto para sensor de corrente
 
 
// =============================================================================================================
// --- Mapeamento de Hardware ---
#define     botao       10     //botão para mudar entre um menu e outro
#define     pin_sct     A0     //sensor de corrente


// =============================================================================================================
// --- Constantes do Projeto ---
#define     rede       220     //tensão da rede local 220V


// =============================================================================================================
// --- Protótipo das Funções ---
void read_but();                               //função para leitura do botão


// =============================================================================================================
// --- Variáveis Globais ---
short          screens   = 0x01;               //variável para seleção de menus
 

boolean        but_flag  = 0x00,               //flag auxiliar para o botão
               amp_unity = 0x00;               //flag de modificação de múltiplo de unidade de corrente


// =============================================================================================================
// --- Hardware do LCD ---
LiquidCrystal disp(8,  //RS no digital 8
                   7,  //EN no digital 7
                   5,  //D4 no digital 5
                   4,  //D5 no digital 4
                   3,  //D6 no digital 3
                   2); //D7 no digital 2


// =============================================================================================================
// --- Configurações Iniciais ---
void setup()
{

  pinMode(botao  , INPUT_PULLUP);      //entrada para o botão com pull-up interno
  pinMode(pin_sct, INPUT);             //entrada para sensor de corrente

  Serial.begin(9600);                  //inicia serial com 9600 baud rate
  
  //Pino, calibracao - Cur Const= Ratio/BurdenR. 2000/33 = 60
  emon1.current(pin_sct, 60);
 
  
  disp.begin(16,2);                    //Inicializa LCD 16 x 2
  disp.clear();                        //Limpa LCD

  disp.setCursor(2,0);                 //posiciona curso na coluna 3 linha 1
  disp.print("Amperimetro");           //imprime
  
   
} //end setup


// =============================================================================================================
// --- Loop Infinito ---
void loop()
{

  read_but();   //chama função para ler botão

 
  switch(screens)
  {
      case 0x01: disp.setCursor(14,1); disp.print(" A"); amp_unity = 0x00; break;
      case 0x02: disp.setCursor(14,1); disp.print("mA"); amp_unity = 0x01; break;
    
  } //end switch screens
 
  
  //Calcula a corrente
  double Irms = emon1.calcIrms(1480);
  
  //Mostra o valor da corrente no serial monitor e display
  Serial.print("Corrente : ");
  Serial.print(Irms); // Irms
  Serial.println(" A");
  disp.setCursor(2,1);                 //posiciona curso na coluna 3 linha 2
  
  if(!amp_unity) disp.print(Irms);
  else           disp.print(Irms*1000);
  
  
  delay(10);  
  
} //end loop



// =============================================================================================================
// --- Desenvolvimento das Funções ---

// =============================================================================================================
void read_but()                                //função para leitura do botão
{
     if(!digitalRead(botao)) but_flag = 0x01;  //botão pressionado? Seta flag

     if(digitalRead(botao) && but_flag)        //botão solto e flag setada?
     {                                         //sim...
         but_flag = 0x00;                      //limpa flag

         screens++;                            //incrementa screens

      
     } //end if

     if(screens > 0x02) screens = 0x01;
  
  
} //end read_but
