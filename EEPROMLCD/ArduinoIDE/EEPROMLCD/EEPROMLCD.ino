/* 

            O objetivo deste programa é criar um contator que seja impresso no display, a cada incremento desse contador, o programa salva o conteúdo na memória EEPROM. Sempre
     que o circuito for reiniciado, o programa irá perguntar se o usuário que retomar a contagem de onde parou ou se quer recomeçar do zero. Se o usuário quiser retomar a 
     contagem, o programa le o último valor salvo na EEPROM.

            Na simulação e na prática o circuito e o programa funcionaram perfeitamente.

*/

// Inclusão de bibliotecas
#include <LiquidCrystal.h>
#include <EEPROM.h>

// Mapeamento de hardware
#define botao1 10
#define botao2 9
LiquidCrystal disp(2,   // RS
                   3,   // EN
                   4,   // D4
                   5,   // D5
                   6,   // D6
                   7);  // D7

// Protótipo de funções auxiliares
void leitura_Botoes();

// Variáveis auxiliares
int cont = 0x00;
int address = 0x00;
short option = 0x00;
boolean flagB1 = 0x00;
boolean flagB2 = 0x00; 

void setup() {

    pinMode(botao1, INPUT_PULLUP);
    pinMode(botao2, INPUT_PULLUP);

    disp.begin(16,2);
    disp.clear();

    leitura_Botoes();
    disp.clear();

    disp.setCursor(0, 0);
    disp.print("Contador: ");
} // end void setup

void loop() {
 
    cont++;
    delay(500);

    disp.setCursor(1, 5);
    disp.print(cont);

    EEPROM.write(address, cont);
} // end void loop


// Funções auxiliares

void leitura_Botoes(){

    disp.setCursor(0, 0);
    disp.print("Retomar cont ?");
    disp.setCursor(2, 1);
    disp.print("Nao");
    disp.setCursor(8, 1);
    disp.print("Sim");

    do{

        if(!digitalRead(botao1)) flagB1 = 0x01;
        if(!digitalRead(botao2)) flagB2 = 0x01;

        if(digitalRead(botao1) && flagB1){
          
            flagB1 = 0x00;

            option = 0x01;
        } // end if botao1

        if(digitalRead(botao2) && flagB2){

            flagB2 = 0x00;

            option = 0x02;
        } // end if botao2

        if(option == 0x01)
            cont = EEPROM.read(address);
       

        if(option == 0x02){

            EEPROM.write(address, 0xFF);
            cont = 0x00;
        } // end if option == 0x02
      
    }while(option == 0x00);   // end do-while
} // end void leitura_Botoes
