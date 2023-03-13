/* 

      Este programa tem a função de comparar o delay com a interrupção do timer2, mostrando que, enquanto o delay trava o programa, atrapalhando sua
   execução, a interrupção ocorre no meio da execução, interrompendo-a, mas não trava a mesma por um tempo considerável para aplicações não críticas.


   ***** TIMER 2 *****

   Ciclo de máquina = 1/16MHz = 62,5ns
    
   Overflow = (256 - TCNT2) * Prescaler * Ciclo de máquina
   Overflow = 156 * 1024 * 62,5ns
   Overflow = 9,98ms

   Logo, a interrupção do timer2 ocorrerá a cada 9,98ms ~= 10ms.

      Na simulação e na prática o circuito e o programa funcionaram como esperado. 

*/

// Variáveis auxiliares
int cont = 0x00;

ISR(TIMER2_OVF_vect){     // Função de interrupção utilizando os registradore do ATMega328P
  
    TCNT2 = 100;          // Reinicia a contagem do timer2 em 100, para contagem de 156
    cont++;

    if(cont == 0x32){     // 0x32h = 50d * 9,98ms = 499ms é o tempo em que a saída d10 irá alternar

        cont = 0x00;
        
        digitalWrite(10, !digitalRead(10));
    }
}

void setup() {
  
    pinMode(10, OUTPUT);
    pinMode(9, OUTPUT);

    TCCR2A = 0x00;        // Configura a operação normal do timer2
    TCCR2B = 0x07;        // Configura os prescaler em 1:1024
    TCNT2 = 100;          // Inicia contagem do timer2 em 100, para contagem de 156
    TIMSK2 = 0x01;        // Habilita a interrupção por overflow do timer2
}

void loop() {

    digitalWrite(9, HIGH);
    delay(499);
    digitalWrite(9, LOW);
    delay(499);
}
