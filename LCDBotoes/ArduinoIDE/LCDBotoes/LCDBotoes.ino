/* 

          Este programa tem o objetivo de utilizar o LCD para demonstrar qual botao foi pressionado por último. Para isso, serão conectados dois botões no Arduíno, assim como 
     O LCD 16x2

           Na prática o circuito funcionou como esperado. 

*/

#include <LiquidCrystal.h>                          // Inclui biblioteca do display LCD
  
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);                  // Mapea as portas do LCD no Arduíno

#define botao1 6                                    // Cria mnemônico para botao1 no pino 6
#define botao2 7                                    // Cria mnemônico para botao2 no pino 7

int b1 = 0, b2 = 0;

void setup() {

     pinMode(botao1, INPUT);                        // Configura botao1 como entrada digital
     pinMode(botao2, INPUT);                        // Configura botao2 como entrada digital
  
     lcd.begin(16,2);                               // Inicia o LCD  
     lcd.print("Pressione");                        // Escreve "Pressione" na coluna 0, linha 0           
     
}

void loop() {

    b1 = digitalRead(botao1);
    b2 = digitalRead(botao2);

    if(!b1){

        lcd.setCursor(2, 1);                          // Seta o cursor na coluna 3, linha 2
        lcd.print("Opcao 1");                         // Escreve opcao1, pois botao1 foi pressionado
    
    }

    if(!b2){
      
        lcd.setCursor(2, 1);                          // Seta cursor para coluna 3, linha 2
        lcd.print("Opcao 2");                         // Escreve opcao2, pois botao2 foi pressionado
      
    }

} // end void loop
