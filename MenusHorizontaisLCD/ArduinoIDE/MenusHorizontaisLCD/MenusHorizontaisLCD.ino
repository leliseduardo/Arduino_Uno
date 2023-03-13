/* 
  
          O objetivo deste código é criar menus no display LCD de forma horizontal. A técnica de criação de menus e alteração de menus é a mesma, porrém, com a impressão de
    que os menus estão se movendo horizontalmente. 

         Na simulação e na prática o circuito e o programa funcionaram perfeitamente.

*/


// Inclusão de bibliotecas
#include <LiquidCrystal.h>

// Mapeamento de hardware
#define botaoEsquerda 11
#define botaoDireita  10
#define botaoEnter    9
#define botaoVolta    8

LiquidCrystal disp( 2,    // RS
                    3,    // E
                    4,    // d4
                    5,    // d5
                    6,    // d6
                    7);   // d7

// Protótipo de funções auxiliares
void leitura_Botoes();
void menu1();
void sub_Menu1();
void menu2();
void sub_Menu2();
void menu3();
void sub_Menu3();
void menu4();
void sub_Menu4();

// Variáveis auxiliares
boolean flagBE = 0;
boolean flagBD = 0;
boolean flagBEnt = 0;
boolean flagBV = 0;

const int numeroMenus = 4;
const int numeroSubMenus = 2;
int menu = 1;
int entraMenu = 1;



void setup() {
  
    for(int i = 8; i < 12; i++)
        pinMode(i, INPUT_PULLUP);

    disp.begin(16, 2);
    disp.clear();
    delay(555);
} // end void setup

void loop() {
  
    leitura_Botoes();

    switch(menu){

        case 1: 
            menu1();
            break;
        case 2:
            menu2();
            break;
        case 3: 
            menu3();
            break;
        case 4:
            menu4();
            break;
    } // end switch menu
} // end void loop



// Funções auxiliares



void leitura_Botoes(){
  
    if(!digitalRead(botaoEsquerda))   flagBE   = 1;
    if(!digitalRead(botaoDireita))    flagBD   = 1;
    if(!digitalRead(botaoEnter))      flagBEnt = 1;
    if(!digitalRead(botaoVolta))      flagBV   = 1;

    if(entraMenu == 1){
      
        if(digitalRead(botaoEsquerda) && flagBE){

            flagBE = 0;
            
            if(menu > 1)
                menu--;

            disp.clear();
        } // end if botaoEsquerda

        if(digitalRead(botaoDireita) && flagBD){

            flagBD = 0;

            if(menu < numeroMenus)
                menu++;

            disp.clear();
        } // end if botaoEsquerda
    } // end if entraMenu == 1

    if(digitalRead(botaoEnter) && flagBEnt){

            flagBEnt = 0;
            
            if(entraMenu < numeroSubMenus)
                entraMenu++;

            disp.clear();
     } // end if botaoEsquerda

     if(digitalRead(botaoVolta) && flagBV){

            flagBV = 0;
            
            if(entraMenu > 1)
                entraMenu--;

            disp.clear();
     } // end if botaoEsquerda
    
} // end void leitura_Botoes



void menu1(){
  
    switch(entraMenu){

        case 1: 
            disp.setCursor(0, 0);
            disp.print("     Sala     >");
            break;
         case 2:
            subMenu1();
            break;
    } // end switch entraMenu
} // end void menu1


void subMenu1(){

    disp.setCursor(1, 0);
    disp.print("Luzes sala");
    disp.setCursor(1, 1);
    disp.print("1: ON    2: OFF");
} // end void subMenu1




void menu2(){
  
    switch(entraMenu){

        case 1: 
            disp.setCursor(0, 0);
            disp.print("<   Cozinha   >");
            break;
         case 2:
            subMenu2();
            break;
    } // end switch entraMenu
} // end void menu2


void subMenu2(){

    disp.setCursor(1, 0);
    disp.print("Luzes cozinha");
    disp.setCursor(1, 1);
    disp.print("1: ON    2: OFF");
} // end void subMenu2



void menu3(){
  
    switch(entraMenu){

        case 1: 
            disp.setCursor(0, 0);
            disp.print("<   Garagem   >");
            break;
         case 2:
            subMenu3();
            break;
    } // end switch entraMenu
} // end void menu3


void subMenu3(){

    disp.setCursor(1, 0);
    disp.print("Luzes garagem");
    disp.setCursor(1, 1);
    disp.print("1: ON    2: OFF");
} // end void subMenu3




void menu4(){
  
    switch(entraMenu){

        case 1: 
            disp.setCursor(0, 0);
            disp.print("<   Quintal   ");
            break;
         case 2:
            subMenu4();
            break;
    } // end switch entraMenu
} // end void menu4


void subMenu4(){

    disp.setCursor(1, 0);
    disp.print("Luzes quintal");
    disp.setCursor(1, 1);
    disp.print("1: ON    2: OFF");
} // end void subMenu4
