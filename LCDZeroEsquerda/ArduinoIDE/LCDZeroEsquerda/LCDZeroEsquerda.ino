/* 

            Este programa tem a função de corrigir um erro recorrente que acontece no display. Geralmente, o display não imprime o zero a esquerda, isto
     é, quando um número decremente, por exemplo, e passa a ser menor do que 10, ele não mostra o zero a esquerda, e sim, somente o número menor do que
     10. Isso pode gerar uma impressão errada e uma passagem incorreta da informação na qual o display tem a função de passar.
            Com um temporizador simples, este código demonstra uma forma de corrigir este erro recorrente.

            Na simulação e na prática o circuito e o programa funcionaram perfeitamente.

*/

// Inclusão de bibliotecas
#include <LiquidCrystal.h>

// Mapeamento de hardware
LiquidCrystal disp( 2,      // RS
                    3,      // EN
                    4,      // D4
                    5,      // D5
                    6,      // D6
                    7 );    // D7

// Protótipos de funções auxiliares
void temporizador();
void imprime_Display(int minutos, int segundos);

// Variáveis auxiliares
int minutos, segundos;
          
void setup() {

    disp.begin(16, 2);

    minutos = 1;
    segundos = 30;
}

void loop() {
  
    disp.setCursor(2, 0);
    disp.print("Temporizador");
    temporizador();
    delay(1000);
}


// Funções auxiliares

void temporizador(){
  
    segundos--;

    if(segundos <= 0x00){

        segundos = 59;

        minutos--;

        if(minutos <= 0x00)
            minutos = 59;
    } // end if segundos

    imprime_Display(minutos, segundos);
} // end void temporizador


void imprime_Display(int minutos, int segundos){
  
    if(minutos < 10){

        disp.setCursor(8, 1);
        disp.print("0"); 
        disp.setCursor(9, 1);
        disp.print(minutos);    
    } // end if minutos < 10
    else{

        disp.setCursor(8, 1);
        disp.print(minutos); 
    } // end else minutos < 10

    disp.setCursor(10, 1);
        disp.print(":"); 

    if(segundos < 10){

        disp.setCursor(11, 1);
        disp.print("0");
        disp.setCursor(12, 1);
        disp.print(segundos); 
    } // end if segundos < 10
    else{

        disp.setCursor(11, 1);
        disp.print(segundos); 
    } // end else segundos < 10
} // end void imprime_Display
