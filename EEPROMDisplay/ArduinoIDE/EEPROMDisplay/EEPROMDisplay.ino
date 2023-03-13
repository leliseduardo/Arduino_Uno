/* 

        O objetivo deste programa é incrementar um display de 7 segmentos e gravar o número atual na memória EEPROM. Se o Arduíno for reiniciado ou desligado, quando for ligado
    novamente, o último número salvo aparecerá no display. O número que estava quando o display foi desligado.


        Na simulação e na prática o circuito e o programa funcionaram perfeitamente.

*/

// Inclusão de bibliotecas
#include <EEPROM.h>

// Protótipo de funções auxiliares
int display(int num);

// Variáveis auxiliares
int adress = 0;
int disp = 0;
bool flag = 0;

void setup() {

  for(int i=0; i < 7; i++)
    pinMode(i, OUTPUT);
    
  pinMode(8, INPUT_PULLUP);

  PORTD = display(0);
  disp = EEPROM.read(adress);

}

void loop() {
  
    if(!digitalRead(8))
      flag = 1;

    if(digitalRead(8) && flag){

      flag = 0;

      disp++;
      
    } // end if

    if(disp >= 10)
      disp = 0;


    PORTD = display(disp);

    EEPROM.write(adress, disp);

    delay(100);

}

int display(int num){
  
    int aux = 0;

    int imprime[10] = {
    
          0x3F,
          0x06,
          0x5B,
          0x4F,
          0x66,
          0x6D,
          0x7D,
          0x07,
          0x7F,
          0x67
    };

    aux = imprime[num];

    return aux;
  
} // end int display
