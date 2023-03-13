/* 

        O objetivo deste código é implementar a multiplexação de dois displays de 7 segmentos. Ainda, com o uso de dois botões, será incrementado e
    decrementado o valor exibido no display. 
        Não realizarei a prárica deste circuito e código pois já fiz a multiplexação de displays várias vezes, tanto em C com o Pic, quanto em Assembly,
    também com o Pic. A única diferença aqui é o mcu, a lógica é a mesma.
    
        Na simulação o circuito e o programa funcionaram como esperado.
  
*/

// Mapeamento de hardware
#define bot1 11
#define bot2 10
#define disp1 9
#define disp2 8

// Protótipo de funções auxiliares
void multiplex(char n);
char disp(char num);
void leitura_Botoes();

// Variáveis auxiliares
char cont = 0;
boolean flagB1, flagB2;
char dez = 0x00, uni = 0x00;

void setup() {

  for(int i=0; i < 7; i++) pinMode(i, OUTPUT);
  pinMode(disp1, OUTPUT);
  pinMode(disp2, OUTPUT);
  pinMode(bot1, INPUT_PULLUP);
  pinMode(bot2, INPUT_PULLUP);

  flagB1 = 0x00;
  flagB2 = 0x00;

  digitalWrite(disp1, LOW);
  digitalWrite(disp2, LOW);

} // end void setup

void loop() {
  
    leitura_Botoes();

    multiplex(cont);
} // end void loop


void multiplex(char n){
  
    dez = n/10;
    PORTD = disp(dez);
    digitalWrite(disp2, HIGH);
    delay(1);
    digitalWrite(disp2, LOW);

    uni = n%10;
    PORTD = disp(uni);
    digitalWrite(disp1, HIGH);
    delay(1);
    digitalWrite(disp1, LOW);
} // end void multiplex


char disp(char num){

    char aux = 0;

    char imprime[10] = {
    
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
} // end void disp


void leitura_Botoes(){
  
    if(!digitalRead(bot1)) flagB1 = 1;
    if(!digitalRead(bot2)) flagB2 = 1;

    if(digitalRead(bot1) && flagB1){
      
        flagB1 = 0;

        cont++;

        if(cont > 99)
          cont = 0x00;
    } // end if

    if(digitalRead(bot2) && flagB2){
      
        flagB2 = 0;

        cont--;

        if(cont < 0x00)
            cont = 99;
    } // end if
} // end void leitura_Botoes
