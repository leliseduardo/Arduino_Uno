/*

        O objetivo deste código é criar uma animação de 8 frames na matriz de leds. Este código foi copiado da aula do WRKits, por seu um circuio mais complexo e com baixa impor-
    tância de aplicação. Caso e necessite entendê-lo para utilizar em algum projeto, é válido revisar todo o código.

        Não tenho matriz de leds para testar na prática e também não funciona na simulação.
          
*/

#include <TimerOne.h>                  //Inclui biblioteca para trato de interrupção

#define latchPin 10                    //Pino conectado ao pino 12 do registrador de deslocamento

int clockPin = 12;                     //Pino conectado ao pino 11 do registrador de deslocamento
int dataPin = 11;                      //Pino conectado ao pino 14 do registrador de deslocamento

byte frame = 0;                        //Armazenará o frame atual


// --- Funções Auxiliares ---
void shiftIt(byte dataOut);              //Controla Shift Registers
void screenUpdate();                     //Atualiza display


//Vetor multidimensional
byte led[8][8] = {
                    { //Frame 01
                     B00000000,
                     B00000000,
                     B10000111,
                     B10011111,
                     B10000111,
                     B00000000,
                     B00000000,
                     B00000000,
                    }, //end frame 01
                    
                    { //Frame 02
                     B00000000,
                     B00000000,
                     B01001110,
                     B01111110,
                     B01001110,
                     B00000000,
                     B00000000,
                     B00000000,
                    }, //end frame 02
                    
                    { //Frame 03
                     B00000000,
                     B00000000,
                     B01101110,
                     B01111110,
                     B01101110,
                     B00000000,
                     B00000000,
                     B00000000,
                    }, //end frame 03
                    
                    { //Frame 04
                     B00000000,
                     B00100000,
                     B01111100,
                     B01111000,
                     B01111100,
                     B00100000,
                     B00000000,
                     B00000000,
                    }, //end frame 04
                    
                    { //Frame 05
                     B00010000,
                     B00000000,
                     B01101100,
                     B01111000,
                     B01101100,
                     B00000000,
                     B00010000,
                     B00000000,
                    }, //end frame 05
                    
                    { //Frame 06
                     B00000100,
                     B00000000,
                     B01101000,
                     B01111000,
                     B01101000,
                     B00000000,
                     B00000000,
                     B00001000,
                    }, //end frame 06
                    
                    { //Frame 07
                     B00000001,
                     B00001000,
                     B01111000,
                     B01110000,
                     B01111000,
                     B00000000,
                     B00100000,
                     B00001010,
                    }, //end frame 07
                    
                    { //Frame 08
                     B00000000,
                     B00000000,
                     B01110000,
                     B01100000,
                     B01110000,
                     B00000000,
                     B00000000,
                     B00000000,
                    }, //end frame 08
                    
                    
                 }; //end led 8x8
                 
                 
                 
                
void setup()
{
  pinMode(latchPin,OUTPUT);
  pinMode(clockPin,OUTPUT);
  pinMode(dataPin,OUTPUT);
  
  
  Timer1.initialize(10000);                        //Gera uma interrupção a cada 10000 micro segundos (freq = 100Hz)
  Timer1.attachInterrupt(screenUpdate);            //Associa a função screenUpdate ao timer1


} //end setup


void loop()
{
   for(int i=0; i<8; i++)                              //Percorre os 8 frames
   {
      for(int j=0; j<8; j++)                           //Percorre as 8 linhas
      {
         led[i][j] = led[i][j] << 1 | led[i][j] >> 7;  //rotação bit a bit
      
      } //end for aninhado
   
   
   }
    frame++;                                           //Incrementa frame
    if(frame > 7) frame = 0;                           //Se maior que 7, volta a ser zero
    
    delay(500);                                        //taxa de atualização

} //end loop

//Atualiza display
void screenUpdate()
{
   byte row = B10000000; //linha 1
   
   
   for(byte k=0; k<9; k++)
  {
   digitalWrite(latchPin, LOW);                       //deixa o shift register pronto para receber dados
  
   shiftIt(~led[frame][k]);                           //envia o vetor de LEDs negado para os 74HC595
   shiftIt(row);                                      //envia o número pertinente a linha para os 74HC595
  
   digitalWrite(latchPin, HIGH);                      //Interrompe recepção de dados
   row = row >> 1;                                    //Desloca a linha 1 bit para a direita shift right
  }

} //end screenUpdate


void shiftIt(byte dataOut)
{
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


}
