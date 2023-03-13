/* 

            Este programa tem a função de ler dois sensores de temperatura LM35, que podem, numa aplicação prática, estar interno e externo a um 
     ambiente. As temperaturas lidas serão impressas em um display LCD e, através de um botão, muda-se o menu e a impressão da leitura de casa 
     sensor.

            Na simulação e na prática o circuito e o programa funcionaram como esperado.

*/

// Inclusão de bibliotecas
#include <LiquidCrystal.h>

// Mapeamento de hardware
LiquidCrystal disp(2,    // RS
                   3,    // EN
                   4,    // D4 
                   5,    // D5
                   6,    // D6
                   7);   // D7
#define botao 10
#define sensor1 A0
#define sensor2 A1

// Protótipos de funções auxiliares
void leitura_Botao();
void celsius();
int media_Temperatura();

// Variáveis auxiliares
float temperatura = 0.0;
float ultimaTemperatura = 0.0;
int tensao = 0.0;
boolean flagB;
boolean controlSensor;
int menu = 0x01;

void setup() {

    disp.begin(16, 2);

    pinMode(botao, INPUT_PULLUP);
    pinMode(sensor1, INPUT);
    pinMode(sensor2, INPUT);

    flagB = 0x00;
    controlSensor = 0x00;

    disp.setCursor(0, 0);
    disp.print("Temperatura");
} // end void setup

void loop() {
  
    leitura_Botao();

    switch(menu){

        case 0x01: disp.setCursor(0, 1); disp.print("Int: "); controlSensor = 0x00; break;
        case 0x02: disp.setCursor(0, 1); disp.print("Ext: "); controlSensor = 0x01; break;
    } // end switch menu

    celsius();

    delay(100);
} // end void loop



// Funções auxiliares

void leitura_Botao(){
  
    if(!digitalRead(botao)) flagB = 0x01;

    if(digitalRead(botao) && flagB){
      
        flagB = 0x00;

        menu++;
    } // end if

    if(menu > 0x02)
        menu = 0x01;
} // end void leitura_Botao

void celsius(){

    tensao = media_Temperatura();

    temperatura = (tensao*5.0)/1024.0;

    temperatura = temperatura * 100.0;

    if((temperatura > ultimaTemperatura + 0.5) || (temperatura < ultimaTemperatura - 0.5)){
      
        ultimaTemperatura = temperatura;

        disp.setCursor(5, 1);
        disp.print(ultimaTemperatura);
        
    } // end if temperatura
} // end void celsius


int media_Temperatura(){

    int adc = 0x00;                         // Essa variável tem que ser inicializada com 0, senão gera erro na hora da contagem.

    for(int i=0; i < 0x64; i++){
        
        if(!controlSensor)
            adc += analogRead(sensor1);
        else
            adc += analogRead(sensor2);
    }

    return (adc/0x64);
} // end void media_Temperatura
