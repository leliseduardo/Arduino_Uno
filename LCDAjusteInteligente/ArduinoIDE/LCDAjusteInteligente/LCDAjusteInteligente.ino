/* 

            Este programa tem a funçãode utilizar o código já feito na aula "LCD_MenuLista" para, agora, fazer um ajuste inteligente do menu e de um pwm no menu1. Enquanto
     houver o ajuste, o parâmetro a ser ajustado irá piscar. Para isso serão adicionados dois botões.

            NA simulação e na prática o circuito e o programa funcionaram perfeitamente.

*/

//Inclusão de bibliotecas
#include <LiquidCrystal.h>

// Mapeamento de hardware
LiquidCrystal disp(2,   // RS
                   3,   // E
                   4,   // D4
                   5,   // D5
                   6,   // D6
                   7);  // D7
                   
#define   enter       8
#define   seleciona   9 
#define   ajuste      10
#define   parametro   12
#define   led         11

// Protótipo de funções auxiliares
void leitura_Botoes();
void leitura_Botoes2();
void imprime_Display();
void entra_Menus();
void menu1();
void menu2();
void menu3();
void menu4();
void menu5();
void pisca_Ajuste();

// Variáveis auxiliares
boolean flagBE = 0,
        flagBS = 0,
        flagBA = 0,
        flagBP = 0,
        entraMenu = 0,
        entraAjuste = 0;

int menu = 0x01,
    pwm = 0x00;


// Função de inicialização
void setup() {

    pinMode(enter, INPUT_PULLUP);
    pinMode(seleciona, INPUT_PULLUP);
    pinMode(ajuste, INPUT_PULLUP);
    pinMode(parametro, INPUT_PULLUP);
    pinMode(led, OUTPUT);

    digitalWrite(led, LOW);

    disp.begin(16,2); 
    disp.clear();
} // end void setup


// Função de execução
void loop() {

    leitura_Botoes();
    if(entraMenu)
        entra_Menus();   
    else
       imprime_Display(); 
} // end void loop




// Funções auxiliares


void leitura_Botoes(){

    if(!digitalRead(enter))   flagBE = 1;
    if(!digitalRead(seleciona))   flagBS = 1;


    if(digitalRead(seleciona) && flagBS){

        flagBS = 0;

        menu++;     
        
        entraAjuste = 0;                      // Desliga ajuste de parâmetros
        
        if(menu > 0x05) menu = 0x01;

        disp.clear();
    } // end if digitalRead(seleciona) && flagBS

    if(digitalRead(enter) && flagBE){

        flagBE = 0;

        entraMenu = !entraMenu;

        entraAjuste = 0;                      // Desliga ajuste de parâmetros

        disp.clear();
    } // end if digitalRead(enter) && flagBE
} // end void leitura_Botoes

void leitura_Botoes2(){

    if(!digitalRead(ajuste))      flagBA = 1;

    if(entraAjuste)
        if(!digitalRead(parametro))   
            flagBP = 1;

        if(digitalRead(ajuste) && flagBA){

            flagBA = 0;

            entraAjuste = !entraAjuste;
        } // end if ajuste
        
        if(digitalRead(parametro) && flagBP){
          
            flagBP = 0;

            pwm += 10;

            if(pwm > 255)   pwm = 0x00;
        } // end if parametro
} // end void leitura_Botoes2

void imprime_Display(){

    switch(menu){

        case 0x01:
            disp.setCursor(0, 0);
            disp.print("> ");
            disp.setCursor(2, 0);
            disp.print("Menu ");
            disp.print(menu);
            disp.setCursor(2, 1);
            disp.print("Menu ");
            disp.print(menu + 1);
            break;
        case 0x02: 
            disp.setCursor(0, 0);
            disp.print("> ");
            disp.setCursor(2, 0);
            disp.print("Menu ");
            disp.print(menu);
            disp.setCursor(2, 1);
            disp.print("Menu ");
            disp.print(menu + 1);
            break;
         case 0x03: 
            disp.setCursor(0, 0);
            disp.print("> ");
            disp.setCursor(2, 0);
            disp.print("Menu ");
            disp.print(menu);
            disp.setCursor(2, 1);
            disp.print("Menu ");
            disp.print(menu + 1);
            break;
          case 0x04: 
            disp.setCursor(0, 0);
            disp.print("> ");
            disp.setCursor(2, 0);
            disp.print("Menu ");
            disp.print(menu);
            disp.setCursor(2, 1);
            disp.print("Menu ");
            disp.print(menu + 1);
            break;
          case 0x05: 
            disp.setCursor(0, 0);
            disp.print("> ");
            disp.setCursor(2, 0);
            disp.print("Menu ");
            disp.print(menu);
            disp.setCursor(2, 1);
            disp.print("Menu ");
            disp.print(1);
            break;
           
    } // end switch menu
} // end void imprime_Display



void entra_Menus(){

    switch(menu){

        case 0x01: 
            menu1();
            break;
        case 0x02: 
            menu2();
            break;
        case 0x03: 
            menu3();
            break;
        case 0x04: 
            menu4();
            break;
        case 0x05: 
            menu5();
            break;
    } // end switch menu
} // end void entra_Menus



void menu1(){

    leitura_Botoes2();

    disp.setCursor(0, 0);
    disp.print("Dentro menu 1");
    disp.setCursor(0, 1);
    disp.print("PWM Led: ");
    disp.setCursor(10, 1);
    disp.print(pwm);

    if(entraAjuste){

        pisca_Ajuste();
        disp.setCursor(10, 1);
        disp.print("      ");
        pisca_Ajuste();
    } // end if ajuste
         

    analogWrite(led, pwm);
} // end void menu1


void menu2(){

    disp.setCursor(0, 0);
    disp.print("Dentro menu 2");
    disp.setCursor(2, 1);
    disp.print("Aciona led 2");
} // end void menu2


void menu3(){

    disp.setCursor(0, 0);
    disp.print("Dentro menu 3");
    disp.setCursor(2, 1);
    disp.print("Aciona led 3");
} // end void menu3


void menu4(){

    disp.setCursor(0, 0);
    disp.print("Dentro menu 4");
    disp.setCursor(2, 1);
    disp.print("Aciona led 4");
} // end void menu4


void menu5(){

    disp.setCursor(0, 0);
    disp.print("Dentro menu 5");
    disp.setCursor(2, 1);
    disp.print("Aciona led 5");
} // end void menu5



void pisca_Ajuste(){

    for(int i=0; i < 25; i++){

        leitura_Botoes();
        leitura_Botoes2();

        delay(10);
    }
} // end void pisca_Ajuste
