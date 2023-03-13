/* 

      Este programa tem a função de ler um teclado matricial e escrever o número pressionado do display lcd. Ainda, a cada tecla pressionada um buzzer
   irá gerar um barulho de clique.


   ***** TIMER 2 *****

   Ciclo de máquina = 1/16MHz = 62,5ns
    
   Overflow = (256 - TCNT2) * Prescaler * Ciclo de máquina
   Overflow = 156 * 1024 * 62,5ns
   Overflow = 9,98ms

   Logo, a interrupção do timer2 ocorrerá a cada 9,98ms ~= 10ms.

      Na simulação o programa funcionou perfeitamente. 

*/

// Inclusão de bibliotecas
#include <LiquidCrystal.h>

// Mapeamento de hardware
#define col1 A0
#define col2 A1
#define col3 A2
#define lin1 8
#define lin2 9
#define lin3 10
#define lin4 11
#define buzzer 1

// Protótipos de funções auxiliares
void imprime_Display();
void pressiona_Teclado(int num);

// Variáveis auxiliares
LiquidCrystal disp( 2,    // RS
                    3,    // EN
                    4,    // D4
                    5,    // D5
                    6,    // D6
                    7 );  // D7                   
int cont = 0x00;
int numero = 0x00;
char control = 0x01;

// Função de interrupção
ISR(TIMER2_OVF_vect){     // Função de interrupção utilizando os registradore do ATMega328P
  
    TCNT2 = 100;          // Reinicia a contagem do timer2 em 100, para contagem de 156
    cont++;

    if(cont == 0x05){
      
        cont = 0x00;

        if(digitalRead(col1) && control == 0x01){

            control = 0x02;
            digitalWrite(col1, LOW);
            digitalWrite(col2, HIGH);
            digitalWrite(col3, HIGH);

            if(!digitalRead(lin1)) pressiona_Teclado(1);
            if(!digitalRead(lin2)) pressiona_Teclado(4);
            if(!digitalRead(lin3)) pressiona_Teclado(7);
            if(!digitalRead(lin4)) pressiona_Teclado(11);
        } // end if col1
        if(digitalRead(col2) && control == 0x02){

            control = 0x03;
            digitalWrite(col1, HIGH);
            digitalWrite(col2, LOW);
            digitalWrite(col3, HIGH);

            if(!digitalRead(lin1)) pressiona_Teclado(2);
            if(!digitalRead(lin2)) pressiona_Teclado(5);
            if(!digitalRead(lin3)) pressiona_Teclado(8);
            if(!digitalRead(lin4)) pressiona_Teclado(0);
        } // end if col2
        if(digitalRead(col3) && control == 0x03){

            control = 0x01;
            digitalWrite(col1, HIGH);
            digitalWrite(col2, HIGH);
            digitalWrite(col3, LOW);

            if(!digitalRead(lin1)) pressiona_Teclado(3);
            if(!digitalRead(lin2)) pressiona_Teclado(6);
            if(!digitalRead(lin3)) pressiona_Teclado(9);
            if(!digitalRead(lin4)) pressiona_Teclado(12);
        } // end if col3
    } // end if cont == 0x05
} // end ISR

void setup() {

    disp.begin(16,2);

    for(int i=8; i < 12; i++)
        pinMode(i, INPUT);
         
    pinMode(col1, OUTPUT);
    pinMode(col2, OUTPUT);
    pinMode(col3, OUTPUT);
    pinMode(buzzer, OUTPUT);

    digitalWrite(col1, HIGH);
    digitalWrite(col2, HIGH);
    digitalWrite(col3, HIGH);
    digitalWrite(buzzer, LOW);

    TCCR2A = 0x00;        // Configura a operação normal do timer2
    TCCR2B = 0x07;        // Configura os prescaler em 1:1024
    TCNT2 = 100;          // Inicia contagem do timer2 em 100, para contagem de 156
    TIMSK2 = 0x01;        // Habilita a interrupção por overflow do timer2
} // end void setup

void loop() {

    imprime_Display();
} // end void main



// Funções auxiliares

void pressiona_Teclado(int num){
  
    numero = num;

    TIMSK2 = 0x00;        // Desabilita a interrupção por overflow do timer2

    digitalWrite(buzzer, HIGH);
    delay(500);
    digitalWrite(buzzer, LOW);

    TIMSK2 = 0x01;        // Habilita a interrupção por overflow do timer2
    
} // end void pressiona_Teclado



void imprime_Display(){

    disp.setCursor(0,0);
    disp.print("Teclado: ");

    disp.setCursor(5, 1);
    if(numero == 11)
        disp.print("*");
    else if(numero == 12)
        disp.print("#");
    else
        disp.print(numero);
} // end void imprime_Display
