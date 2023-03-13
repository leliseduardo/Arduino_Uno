/* 

      O objetivo deste programa é fazer a varredura de botões através do timer2. Isto é, a partir do timer2 verificar se algum botão foi pressionado. 
   se for, o programa realiza alguma função que, no caso deste programa, será acender e apagar leds. Serão quatro botões, dois para acender e dois para
   apagar dois leds. 

   ***** TIMER 2 *****

   Ciclo de máquina = 1/16MHz = 62,5ns
    
   Overflow = (256 - TCNT2) * Prescaler * Ciclo de máquina
   Overflow = 156 * 1024 * 62,5ns
   Overflow = 9,98ms

   Logo, a interrupção do timer2 ocorrerá a cada 9,98ms ~= 10ms.

*/

//Mapeamento de hardware
#define bot1 5
#define bot2 6
#define bot3 7
#define bot4 8
#define led1 9
#define led2 10
#define out 11

// Variáveis auxiliares
int cont = 0x00;

// Função de interrupção
ISR(TIMER2_OVF_vect){
  
    TCNT2 = 100;
    cont++;

    digitalWrite(out, !digitalRead(out));

    if(cont == 0x0A){                 // overflow * cont = 10ms * 10 = 100ms 
      
        cont = 0x00;

        if(!digitalRead(bot1))  digitalWrite(led1, HIGH);
        if(!digitalRead(bot2))  digitalWrite(led1, LOW);
        if(!digitalRead(bot3))  digitalWrite(led2, HIGH);
        if(!digitalRead(bot4))  digitalWrite(led2, LOW);
    }
}

void setup() {

    pinMode(bot1, INPUT_PULLUP);
    pinMode(bot2, INPUT_PULLUP);
    pinMode(bot3, INPUT_PULLUP);
    pinMode(bot4, INPUT_PULLUP);
    pinMode(led1, OUTPUT);
    pinMode(led2, OUTPUT);
    pinMode(out, OUTPUT);
    

    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(out, LOW);
  
    TCCR2A = 0x00;                    // Configura o timer2 para operação normal
    TCCR2B = 0x07;                    // Configura o prescaler em 1:1024
    TCNT2 = 100;                      // Inicia a contagem do timer2 em 100, para contagem de 156
    TIMSK2 = 0x01;                    // Habilita a interrupção por overflow do timer2   
}

void loop() {

    // Apenas aguarda a interrupção...
}
