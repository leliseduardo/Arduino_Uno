/* 

            Este código tem a função de criar um relógio, com o display LCD, a partir do código do último projeto, denominado "RelogioTimer2".

     ***** TIMER 2 *****
      
     Ciclo de máquina = 62,5ns

     Overflow = (256 - TCNT2) * Prescaler * Ciclo de maquina
     Overflow = (256 - 56) * 1:32 * 62,5ns
     Overflow = 250 * 32 * 62,5ns
     Overflow = 400us 

     Se o tempo que se quer é 1s:

     1s / 400us = 2500

     Logo, 2500 * 400us = 1s

              Testando o tempo, na simulação, do RTC feito com as funções do Arduíno, obteve-se um tempo de 1,01s. Usando os registradores do mcu, obteve-se um tempo de 1,00s.
    Porém, sabe-se que ainda existe a latência de interrupção e o tempo não é exatamente 1s na vida real, mas bem próximo disso.

              Na simulação o programa funcionou perfeitamente.

*/

// Inclusão de bibliotecas
#include <LiquidCrystal.h>

// Mapeamento de hawdware
#define out 7
LiquidCrystal lcd ( 2,   // RS
                     3,   // E
                     4,   // d4
                     5,   // d5
                     6,   // d6
                     7);  // d7

// Protótipo de funções auxiliares
void imprime_Display();
void relogio();

// Variáveis auxiliares
int cont = 0x00;
//int mascara = B10000000;                      // Máscara que se utiliza para alternar o valor de um bit com a lógica XOR
short   numDias;
short   segundos = 57,
        minutos  = 59,
        horas    = 23,
        dia      = 31,
        mes      = 12;
int     ano      = 2021;


// Função de interrupção
ISR(TIMER2_OVF_vect){
  
    TCNT2 = 56;

    cont++;

    if(cont == 2500){

        cont = 0x00;
      
        //digitalWrite(out, !digitalRead(out));
        //PORTD ^= mascara;                    // Através da lógica XOR e da máscara, alterna o estado de D7

        imprime_Display();
        relogio();
    }
} // end funçao interrupão


void setup() {
  
    //pinMode(out, OUTPUT);
    //digitalWrite(out, LOW);
    //DDRD = 0x80;                              // Configura apenas D7 como saída digital
    //PORTD = 0x00;                             // Inicia todas as saídas do portd em Low

    TCCR2A = 0x00;                            // Configura o timer2 em funcionamento normal
    TCNT2 = 56;                               // Inicia o contador em 56 para contagem de 200
    TCCR2B = 0x03;                            // Configura o prescaler para 1:32
    TIMSK2 = 0x01;                            // Habilita a interrupção por overflow do timer2

    lcd.begin(16, 2);
} // end void setup



void loop() {

    // Apenas aguarda a interrupção
} // end void loop




// Funções auxiliares




void relogio(){

    switch(mes){
      
        case 2:
            if((ano%4 == 0 && ano%100 != 0) || ano%400 == 0)
                numDias = 29;
            else
                numDias = 28;
            break;
        case 4:
        case 6:
        case 9:
        case 11:
            numDias = 30;
            break;
        default:
            numDias = 31;
    }

    segundos++;

    if(segundos > 59){
      
        segundos = 0;
        minutos++;

        if(minutos > 59){

            minutos = 0;
            horas++;

            if(horas > 23){

                horas = 0;
                dia++;

                if(dia > numDias){

                    dia = 1;
                    mes++;

                    if(mes > 12){

                        mes = 1;
                        ano++;
                    } // end if mes > 12
                } // end if dia > numDias
            } // end if horas > 23
        } // end if minutos > 59 
    } // end if segundos > 59
} // end void relogio




void imprime_Display(){

    lcd.setCursor(4, 0);
    if(horas < 10) lcd.print(" ");
    lcd.print(horas);
    lcd.print(":");
    if(minutos < 10) lcd.print(" ");
    lcd.print(minutos);
    lcd.print(":");
    if(segundos < 10) lcd.print(" ");
    lcd.print(segundos);
    lcd.setCursor(3, 1);
    if(dia < 10) lcd.print(" ");
    lcd.print(dia);
    lcd.print("/");
    if(mes < 10) lcd.print(" ");
    lcd.print(mes);
    lcd.print("/");
    if(ano < 10) lcd.print(" ");
    lcd.print(ano);
    
    
}
