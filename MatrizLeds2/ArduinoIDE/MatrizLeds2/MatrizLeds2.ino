/*

        O objetivo deste programa é utilizar a matriz de leds e desenhar o PAC-MAN de boca afechada e aberta. Este código foi copiado do WRKITS pela alta complexidade e baixa
    importância do circuito. Porém, o conceito de multiplexação foi bem entendido, assim como todo o circuito e código.

        

*/

// --- Bibliotecas Auxiliares ---
#include <TimerOne.h>                    //Inclui biblioteca para trato de interrupção


// --- Hardware ---
#define latchPin 10                      //digital 10 ao pino 12 do 74HC595 (Latch)

int clockPin = 12;                       //digital 12 ao pino 11 do 74HC595 (Clock)                  **OBS
int dataPin  = 11;                       //digital 11 ao pino conectado ao pino 14 do 74HC595 (Data) **OBS

// **OBS.: (deve ser variável por que está associada com a biblioteca Timer1


// --- Funções Auxiliares ---
void shiftIt(byte dataOut);              //Controla Shift Registers
void atualizaMatriz();                   //Atualiza display para exibir imagem 1
void atualizaMatriz2();                  //Atualiza display para exibir imagem 2


// --- Variáveis Globais ---
byte imagem1[8]; //matriz unidimensional para armazenar imagem 1
byte imagem2[8]; //matriz unidimensional para armazenar imagem 2


// --- Configurações Iniciais ---
void setup()
{
  //Direção dos pinos
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
 
//CRIAÇÃO DAS IMAGENS BIT A BIT (1 INDICA LED ACESO NA MATRIZ, 0 INDICA LED APAGADO) 
 
 //PACMAN (BOCA FECHADA)
   imagem1[0] = B00111100;
   imagem1[1] = B01110110;
   imagem1[2] = B11111111;
   imagem1[3] = B11111111;
   imagem1[4] = B11111111;
   imagem1[5] = B01111110;
   imagem1[6] = B00111100;
   imagem1[7] = B00000000;
   
//PACMAN (BOCA ABERTA)  
   imagem2[0] = B00111100;
   imagem2[1] = B01110110;
   imagem2[2] = B11111111;
   imagem2[3] = B11111111;
   imagem2[4] = B11000000;
   imagem2[5] = B11111111;
   imagem2[6] = B01111110;
   imagem2[7] = B00111100;
   
 
 Timer1.initialize(10000);        //Gera uma interrupção a cada 10000 micro segundos (freq = 100Hz)

} //end setup


// --- Loop Infinito ---
void loop()
{
  
  Timer1.attachInterrupt(atualizaMatriz);      //Associa a matriz 1 ao timer1
  
  for(int i=0; i<8; i++)
  {
   imagem1[i];                                 //Envia imagem 1 para a matriz de leds
  }
  delay(600);
  
  Timer1.attachInterrupt(atualizaMatriz2);     //Associa a matriz 2 ao timer1
  
  for(int i=0; i<8; i++)
  {
   imagem2[i];                                 //Envia imagem 2 para a matriz de leds
  }
  delay(600);
  
} //end loop



void atualizaMatriz()                         //Atualiza matriz para exibir imagem 1
{
  byte linhaA = B10000000;                    //linha A
    
  
  for(byte k=0; k<9; k++)
  {
   digitalWrite(latchPin, LOW);               //deixa o shift register pronto para receber dados
  
   shiftIt(~imagem1[k]);                      //envia o vetor de LEDs negado para os 74HC595
   shiftIt(linhaA);                           //envia o número pertinente a linha para os 74HC595
  
   digitalWrite(latchPin, HIGH);              //Interrompe recepção de dados
   linhaA = linhaA >> 1;                      //Desloca a linha 1 bit para a direita shift right
  }
 
} //end atualizaMatriz


void atualizaMatriz2()                        //Atualiza matriz para exibir imagem 1
{
  byte linhaA = B10000000;                    //linha A
    
  
  for(byte k=0; k<9; k++)
  {
   digitalWrite(latchPin, LOW);               //deixa o shift register pronto para receber dados
  
   shiftIt(~imagem2[k]);                      //envia o vetor de LEDs negado para os 74HC595
   shiftIt(linhaA);                           //envia o número pertinente a linha para os 74HC595
  
   digitalWrite(latchPin, HIGH);              //Interrompe recepção de dados
   linhaA = linhaA >> 1;                      //Desloca a linha 1 bit para a direita shift right
  }
 
} //end atualizaMatriz2



void shiftIt(byte dataOut)                   //Atualiza registradores de deslocamento
{                                            //
  
  boolean pinState;
  digitalWrite(dataPin, LOW);                //libera o registrador de deslocamento, deixando-o pronto para
                                             //enviar dados
  
  for(int i=0; i<8; i++)                     //para cada bit em dataOut, envie um bit
  {
    digitalWrite(clockPin, LOW);             //define clockPin como LOW, antes de enviar o bit
    
    //se o valor de dataOut e (E lógico) uma máscara de bits
    //forem verdadeiros, defina pinState como 1 (HIGH)
    
    if(dataOut & (1<<i))
    {
      pinState = HIGH;
    }
    else
    {
     pinState = LOW; 
    }
    
                                              //define dataPin como HIGH ou LOW, dependendo de pinState
    digitalWrite(dataPin, pinState);
    digitalWrite(clockPin, HIGH);             //envia o bit durante o extremo ascendente de clock
    digitalWrite(dataPin, LOW);
  }
  
  digitalWrite(clockPin, LOW);               //interrompe o deslocamento
  
} //end shiftIt



/*

  
					{0,56,92,158,158,130,68,56},
                    {0,56,124,186,146,130,68,56},
                    {0,56,116,242,242,130,68,56},
                    {0,56,68,226,242,226,68,56},
                    {0,56,68,130,242,242,116,56},
                    {0,56,68,130,146,186,124,56},
                    {0,56,68,130,158,158,92,56},
                    {0,56,68,142,158,142,68,56}









*/
