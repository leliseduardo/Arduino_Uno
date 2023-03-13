/* 

        O objetivo deste programa é criar submenus para o display LCD, para isso, será utilizado o código do programa "LCDMenus", e adicionar submenus
    no menu4.

        Na simulação e na prática o circuito e o programa funcionaram perfeitamente.
      
*/

// Inclusão de bibliotecas
#include <LiquidCrystal.h>

// Mapeamento de hardware
#define bot_Up 8
#define bot_Down 9
#define bot1 10
#define bot2 11
#define led1 A1
#define led2 A0
#define BotS 12

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

void troca_SubMenu4();
void subMenu4a();
void subMenu4b();
void subMenu4c();

// Variáveis auxiliares
char menu = 0x01;
char cont1 = 0x01;
char cont2 = 0x01;
bool flagBU,
     flagBD, 
     flagB1,
     flagB2,
     controle1,
     controle2,
     controle3;

char subMenu4 = 0x01;
bool flagBS;

// Função de configuração
void setup() {
  
    for(int i=2; i < 8; i++)
        pinMode(i, OUTPUT);
    for(int i=8; i < 13; i++)
        pinMode(i, INPUT_PULLUP);

    pinMode(led1, OUTPUT);
    pinMode(led2, OUTPUT);

    flagBU = 0x00;
    flagBD = 0x00;
    flagB1 = 0x00;
    flagB2 = 0x00;
    flagBS = 0x00;
    controle1 = 0x00;
    controle2 = 0x00;
    controle3 = 0x00;

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
  
    troca_SubMenu4();
} // end void menu4

void troca_SubMenu4(){
  
    if(!digitalRead(bot1))  flagB1 = 0x01;
    if(!digitalRead(bot2))  flagB2 = 0x01;

    if(digitalRead(bot1) && flagB1){

        flagB1 = 0x00;

        subMenu4++;

        disp.clear();

        if(subMenu4 > 0x03) subMenu4 = 0x01;
    } // end if bot1

    if(digitalRead(bot2) && flagB2){

        flagB2 = 0x00;

        subMenu4--;

        disp.clear();

        if(subMenu4 < 0x01) subMenu4 = 0x03;
    } // end if bot2

    disp.setCursor(0, 0);
    disp.print("Sub Menu ");

    switch(subMenu4){

        case 0x01:
            subMenu4a();
            break;
        case 0x02:
            subMenu4b();
            break;
        case 0x03:
            subMenu4c();
            break;
    } // end switch subMenu4
} // end void troca_SubMenu4



void subMenu4a(){

    if(!digitalRead(BotS))  flagBS = 0x01;

    if(digitalRead(BotS) && flagBS){
      
        flagBS = 0x00;

        controle1 = !controle1;
    } // end if botS

    if(!controle1){

        disp.print("1");
        disp.setCursor(0, 1);
        disp.print("Aguardando...   "); 
    } // end if controle1
    else{

        disp.print("1");
        disp.setCursor(0, 1);
        disp.print("Em funcionamento");
    } // end else controle1
} // end void subMenu4a

void subMenu4b(){

    if(!digitalRead(BotS))  flagBS = 0x01;

    if(digitalRead(BotS) && flagBS){
      
        flagBS = 0x00;

        controle2 = !controle2;      
    } // end if botS

    if(!controle2){

        disp.print("2");
        disp.setCursor(0, 1);
        disp.print("Aguardando...   "); 
    } // end if controle2
    else{

        disp.print("2");
        disp.setCursor(0, 1);
        disp.print("Em funcionamento");
    } // end else controle2
} // end void subMenu4b

void subMenu4c(){

    if(!digitalRead(BotS))  flagBS = 0x01;

    if(digitalRead(BotS) && flagBS){
      
        flagBS = 0x00;

        controle3 = !controle3;        
    } // end if botS

    if(!controle3){

        disp.print("3");
        disp.setCursor(0, 1);
        disp.print("Aguardando...   "); 
    } // end if controle3
    else{

        disp.print("3");
        disp.setCursor(0, 1);
        disp.print("Em funcionamento");
    } // end else controle3
} // end void subMenu4c
