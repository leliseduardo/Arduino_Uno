/* 

        O objetivo deste programa é utilizar um encoder rotativo para controlar o PWM e simplesmente para contar um número de 8bits. A função utilizada
    neste aula foi criada pelo professor e é um pouco dificil de entender, por usar um tipo de programação que utilizar operações lógicas, além de ter
    um vetor que decodifica os sinais gerados pelo encoder. Porém, tentarei explicar seu funcionamento. Vale ter em mente que esta não é a única maneira
    de se programar a leitura de um encoder roativo, existem outras maneiras que podem ser mais bem compreendidas, como foi feito no curso de Pic. Para
    aprofundar mais, vale ver o código que utiliza "if's" para realizar a leitura do encoder. 
        Para implementar este programa, foi pego como base o código do projeto "LCDMenus3", e adicionado mais um menu.

        Na prática o circuito e o programa funcionaram perfeitamente, como esperado.
               
*/

// Inclusão de bibliotecas
#include <LiquidCrystal.h>

// Mapeamento de hardware
#define bot_Up 8
#define bot_Down 9
#define bot1 12
#define bot2 13
#define led1 A1
#define led2 A0
#define motorPWM 10
#define motor 11

// Mapeamento do hardware do LCD
LiquidCrystal disp( 2, // RS
                    3, // EN
                    4, // d4
                    5, // d5
                    6, // d6
                    7); // d7

// Protótipo de funções auxiliares
void troca_Menu();
void mostra_Menu();
void data_Hora();
void temperatura();
void leds();
void menu4();
void menu5();
void aciona_Motor(unsigned int tempo);
void displayEncoder();
char read_encoder();


// Variáveis auxiliares
char menu = 0x01;
char cont1 = 0x01;
char cont2 = 0x01;
int pwm = 0x00;
unsigned int tempoMotor = 0x00;
bool flagBU,
     flagBD, 
     flagB1,
     flagB2;

// Função de configuração
void setup() {
  
    for(int i=2; i < 8; i++)
        pinMode(i, OUTPUT);
    
    pinMode(bot_Up, INPUT_PULLUP);
    pinMode(bot_Down, INPUT_PULLUP);
    pinMode(bot1, INPUT_PULLUP);
    pinMode(bot2, INPUT_PULLUP);
    pinMode(led1, OUTPUT);
    pinMode(led2, OUTPUT);
    pinMode(motorPWM, OUTPUT);
    pinMode(motor, OUTPUT);

    flagBU = 0x00;
    flagBD = 0x00;
    flagB1 = 0x00;
    flagB2 = 0x00;

    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);

    disp.begin(16,2);
     
} // end void setup

// Função de loop
void loop() {
  
    troca_Menu();
    mostra_Menu();
} // end void loop


// Funções auxiliares

void troca_Menu(){

    if(!digitalRead(bot_Up)) flagBU = 0x01;
    if(!digitalRead(bot_Down)) flagBD = 0x01;

    if(digitalRead(bot_Up) && flagBU){
      
      flagBU = 0x00;

      disp.clear();
      menu++;

      if(menu > 0x06) menu = 0x01;
    } // end if

    if(digitalRead(bot_Down) && flagBD){
      
      flagBD = 0x00;

      disp.clear();
      menu--;

      if(menu < 0x01) menu = 0x06;
    } // end if
  
} // end void troca_Menu


void mostra_Menu(){
  
    switch(menu){

        case 0x01: 
            data_Hora();

            break;
        case 0x02:
            temperatura();

            break;
        case 0x03: 
            leds();

            break;
        case 0x04:
            menu4();

            break;
        case 0x05:
            menu5();

            break;
        case 0x06:
            displayEncoder();

            break;
    } // end switch
} // end void mostra_Menu


void data_Hora(){
  
    disp.setCursor(0,0);
    disp.print("Data e Hora");
    disp.setCursor(0,1);
    disp.print("03/10/20 20:56");
} // end void data_Hora

void temperatura(){
  
    disp.setCursor(0,0);
    disp.print("Temperatura");
    disp.setCursor(0,1);
    disp.print("489 Celsius");
    
} // end void temperatura

void leds(){
  
    if(!digitalRead(bot1)) flagB1 = 0x01;
    if(!digitalRead(bot2)) flagB2 = 0x02;

    disp.setCursor(0,0);
    disp.print("Aciona Leds");

    if(digitalRead(bot1) && flagB1){
      
        flagB1 = 0x00;
        
        cont1++;

        if(cont1 > 0x02) cont1 = 0x01;
           
    } // end if

    if(digitalRead(bot2) && flagB2){
      
        flagB2 = 0x00;

        cont2++;

        if(cont2 > 0x02) cont2 = 0x01;
           
    } // end if

    switch(cont1){

        case 0x01: 
            digitalWrite(led1, LOW);
            disp.setCursor(0,1);
            disp.print("Led1: D");
            break;
        case 0x02: 
            digitalWrite(led1, HIGH);
            disp.setCursor(0,1);
            disp.print("Led1: L");
            break;            
    } // end switch 

    switch(cont2){

        case 0x01: 
            digitalWrite(led2, LOW);
            disp.setCursor(8,1);
            disp.print("Led2: D");
            break;
        case 0x02: 
            digitalWrite(led2, HIGH);
            disp.setCursor(8,1);
            disp.print("Led2: L");
            break;            
    } // end switch 
    
} // end void leds 


void menu4(){
  
    char encoder;

    encoder = read_encoder();

    disp.setCursor(0,0);
    disp.print("Motor PWM");

    if(encoder){

        disp.clear();
        pwm += encoder;
    }

    analogWrite(motorPWM, pwm);
    disp.setCursor(5,1);
    disp.print(pwm);
    
} // end void menu4

void menu5(){
  
    if(!digitalRead(bot1)) flagB1 = 0x01;
    if(!digitalRead(bot2)) flagB2 = 0x02;

    disp.setCursor(0,0);
    disp.print("Aciona Motor");

    if(digitalRead(bot1) && flagB1){
      
        flagB1 = 0x00;
        
        tempoMotor++;

        if(tempoMotor > 120) tempoMotor == 0x00;

        disp.clear();
           
    } // end if

    if(digitalRead(bot2) && flagB2){
      
        flagB2 = 0x00;

        aciona_Motor(tempoMotor);
        
        disp.clear();
           
    } // end if

    digitalWrite(motor, LOW);
    disp.setCursor(5,1);
    disp.print("Motor: D");
    disp.setCursor(0,1);
    disp.print(tempoMotor);
    
} // end void menu5


void aciona_Motor(unsigned int tempo){

    digitalWrite(motor, HIGH);
    disp.setCursor(5,1);
    disp.print("Motor: L");

    for(int i=0; i < tempo; i++)
        delay(1000);
      
} // end void aciona_Motor

void displayEncoder(){
  
    static unsigned char cont = 0;
    char encoder;

    encoder = read_encoder();

    disp.setCursor(0, 0);
    disp.print("Encoder Rot");

    disp.setCursor(6, 1);
    disp.print(cont);

    if(encoder){

        disp.clear();
        cont += encoder;
    }
}

// Esta função está explicada abaixo. Suas linhas foram numeradas para facilitar a explicação
char read_encoder(){
  
      static char enc_states[] = {0,-1,1,0,1,0,0,-1,-1,0,0,1,0,1,-1,0}; // 1
      static unsigned old_AB = 0x00;

      old_AB <<= 2; // 2
      old_AB |= (PIND & 0x03); // 3
      return (enc_states[(old_AB & 0x0F)]); // 4
}

/* 

    Na função read_encoder, algumas operações são feitas de forma um pouco complexas. Para clarear, vou tentar dar uma explicação clara de seu funciona-
    mento.

    O vetor enc_states nada mais é do que um vetor com valores que correspondem aos sinais gerados quando o encoder rotativo gira sem um sentido ou
    no outro. Este vetor sempre retornará um número que corresponde ao sentido de giro, de acordo com os sinais gerados pelo encoder. 

    Ao invés de explicar as operações vou, pegar um exemplo de um giro do encoder, com o sinal de incremento.

    De acordo com o datasheet, se o encoder gira no sentido CW, e A está em D0 e B em D1, temos:

    Inicio do giro:

    B = D0 = 1 e A = D1 = 1

    old_AB = old_AB << 2 <=> 0000 0000 << 2 = 0000 0000
    old_AB = old_AB | (PIND & 0x03) <=> 0000 0000 | (0000 0011 & 0000 0011) <=> 0000 0000 | 0000 0011 = 0000 0011
    return (enc_states[ols_AB & 0x0F) <=> return enc_states[0000 0011 & 0000 1111] <=> return enc_states[0000 0011] <=> return enc_states[3]
    enc_states[3] = 0

    Continuando o giro:

    B = D0 = 1
    A = D1 = 0

    old_AB = old_AB << 2 <=> 0000 0011 << 2 = 0000 1100
    old_AB = old_AB | (PIND & 0x03) <=> 0000 1100 | (0000 0001  & 0000 0011) <=> 0000 1100 | 0000 0001 = 0000 1101
    return (enc_states[ols_AB & 0x0F) <=> return enc_states[0000 1101 & 0000 1111] <=> return enc_states[0000 1101] <=> return enc_states[11]
    enc_states[11] = 1

    A partir daí, girando nesse sentido, a função começa a retornar apenas 1. 

    Não é tão simples de enxergar o funcionamento, mas com essa análise ajuda. Seguindo os mesmos passos para o outro sentido, percebe-se que a 
    função começa a retornar apenas -1. 
    

*/
