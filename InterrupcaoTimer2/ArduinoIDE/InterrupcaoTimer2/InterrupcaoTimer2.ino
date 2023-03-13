/* 

      Este programa tem a função de demonstrar como configurar a interrupção por Overflow do timer2 utilizando os registradores do ATMega328P. Vale 
   ressaltar que, diferentemente de utilizar a interrupção pelas funções reservadas do Arduíno, quando se configura o estouro por Overflow de algum timer,
   deve-se utilizar o nome da função como "ISR", que é a função reservada do MCU para realizar a interrupção.


   ***** TIMER 2 *****

   Ciclo de máquina = 1/16MHz = 62,5ns
    
   Overflow = (256 - TCNT2) * Prescaler * Ciclo de máquina
   Overflow = 156 * 1024 * 62,5ns
   Overflow = 9,98ms

   Logo, a interrupção do timer2 ocorrerá a cada 9,98ms ~= 10ms.

      Na simulação o programa funcionou perfeitamente. 

*/

ISR(TIMER2_OVF_vect){     // Função de interrupção utilizando os registradore do ATMega328P
  
    TCNT2 = 100;          // Reinicia a contagem do timer2 em 100, para contagem de 156

    digitalWrite(10, !digitalRead(10));
}

void setup() {
  
    pinMode(10, OUTPUT);

    TCCR2A = 0x00;        // Configura a operação normal do timer2
    TCCR2B = 0x07;        // Configura os prescaler em 1:1024
    TCNT2 = 100;          // Inicia contagem do timer2 em 100, para contagem de 156
    TIMSK2 = 0x01;        // Habilita a interrupção por overflow do timer2
}

void loop() {

    // Apenas aguarda a interrupção...
}
