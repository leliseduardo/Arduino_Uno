/* 

        O objetivo deste programa é implementar um temporizador a partir de um botão e dois display de 7 segmentos multiplexados. Para isso, será utili-
    zado o código do projeto "MultiplexacaoDisp", que contém dois botões para ajustar o valor do display. A partir deste valor configurado, o display
    ira contar até 0 e acionar uma carga.
        Novamente não irei fazer a prática deste circuito, pois já fiz circuitos e programas parecidos no curso de Pic, tanto em C quanto em Assembly.
    Assim, a montagem do circuito não é novidade. O código foi feito pois sempre existe alguma diferença de lógica, principalemten pela mudança de mcu.
    Portanto, a simples simulação do proteus já resolve e garante o total entendimento no circuito e programa. 
        
        Na simulação o programa e o circuito funcionaram perfeitamente.

*/

// Mapeamento de hardware
#define bot1 11
#define bot2 10
#define disp1 9
#define disp2 8
#define botStart 12
#define saida 13

// Protótipo de funções auxiliares
void multiplex(char n);
char disp(char num);
void leitura_Botoes();

// Variáveis auxiliares
char cont = 0;
boolean flagB1, flagB2, flagBStart, flagTemp;
char dez = 0x00, uni = 0x00;
unsigned long tempo1 = 0x00, tempo2 = 0x00, um_segundo = 1000;

void setup() {

  for(int i=0; i < 7; i++) pinMode(i, OUTPUT);
  pinMode(disp1, OUTPUT);
  pinMode(disp2, OUTPUT);
  pinMode(bot1, INPUT_PULLUP);
  pinMode(bot2, INPUT_PULLUP);
  pinMode(botStart, INPUT_PULLUP);
  pinMode(saida, OUTPUT);

  flagB1 = 0x00;
  flagB2 = 0x00;
  flagBStart = 0x00;
  flagTemp = 0x00;

  digitalWrite(disp1, LOW);
  digitalWrite(disp2, LOW);
  digitalWrite(saida, LOW);

} // end void setup

void loop() {

    tempo2 = millis();                     // tempo2 = millis(), função que conta, em milisegundos, o tempo em que o programa está em execução
  
    leitura_Botoes();

    multiplex(cont);

    if(flagTemp){
      
        if(tempo2 - tempo1 > um_segundo){   // Neste "if", o tempo2, igual ao tempo de funcionamento do programa, em milisegundos, menos o tempo1, 
                                            // tem que ser maior que 1000, que representa 1s. Como tempo1 inicia em 0x00, o primeiro teste, após 1s 
            tempo1 = tempo2;                // de funcionamento do programa, irá ser verdadeiro. Após o primeiro teste, tempo1 recebe o tempo de 
                                            // funcionamento do programa quando o teste foi verdadeiro. Assim, o teste só poderá ser verdadeiro nova-
            cont--;                         // mente quando o tempo2 tiver contado 1000 depois do primeiro teste, ou seja, quando tiver passado mais
                                            // 1s. Assim, o tempo mínimo de entrada neste "if" será de 1s. Logo, cont irá decrementar a cada 1s.
            if(cont == 0x00){               // Esta é uma alternativa para não travar o programa com delays, o que atrapalharia a multiplexação, e 
                                            // também uma alternativa caso não se use os timers do mcu.
                flagTemp = 0x00;
                tempo1 = 0x00;

                digitalWrite(saida, HIGH);
            } // end if
        } // end if        
    } // end if
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
  
    if(!digitalRead(bot1)) flagB1 = 0x01;
    if(!digitalRead(bot2)) flagB2 = 0x01;
    if(!digitalRead(botStart)) flagBStart = 0x01;

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

    if(digitalRead(botStart) && flagBStart){


        flagBStart = 0x00;
        flagTemp = 0x01;

        if(cont == 0x00){
            
            flagTemp = 0x00;
          
            digitalWrite(saida, LOW);
        } // end if
    } // end if
} // end void leitura_Botoes
