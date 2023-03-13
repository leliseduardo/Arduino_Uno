/* 

        O objetivo deste programa é utilizar o programa da aula passada, denominado "LCDMenus", e acrescentar uma rotina no menu4. O menu4 terá a função
     de alterar o brilho de um terceiro led, adicionado no circuito. Este controle de brilho será feito através do controle do PWM de saída pelos botões
     1 e 2. Para utilizar o led numa saída PWM, foi trocado o botao2 de saída, que era a saída 11, e agora é a saída 12. Na saída 11 foi conectado o led
     no qual será controlado o brilho.

        Na simulação e na prática o programa e o circuito funcionaram como esperado.

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
#define ledPWM 10

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

// Variáveis auxiliares
char menu = 0x01;
char cont1 = 0x01;
char cont2 = 0x01;
int pwm = 0x00;
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
    pinMode(ledPWM, OUTPUT);

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

      if(menu > 0x04) menu = 0x01;
    } // end if

    if(digitalRead(bot_Down) && flagBD){
      
      flagBD = 0x00;

      disp.clear();
      menu--;

      if(menu < 0x01) menu = 0x04;
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
  
    if(!digitalRead(bot1)) flagB1 = 0x01;
    if(!digitalRead(bot2)) flagB2 = 0x02;

    disp.setCursor(0,0);
    disp.print("Led PWM");

    if(digitalRead(bot1) && flagB1){
      
        flagB1 = 0x00;
        
        pwm += 10;

        if(pwm > 255) pwm = 0x00;

        disp.clear();
        analogWrite(ledPWM, pwm);
           
    } // end if

    if(digitalRead(bot2) && flagB2){
      
        flagB2 = 0x00;

        pwm -= 10;

        if(pwm < 0x00) pwm = 255;

        disp.clear();
        analogWrite(ledPWM, pwm);
           
    } // end if

    analogWrite(ledPWM, pwm);
    disp.setCursor(5,1);
    disp.print(pwm);
    
} // end void menu5
