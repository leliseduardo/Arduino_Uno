/* 

                  Este programa tem a função de demonstrar como se utiliza um comando do Assembly aqui no Arduino IDE. De quebra, o código demonstra como utilizar um delay
      mínimo, que corresponde a um ciclo de máquina, utilizando o comando NOP do Assembly, que segura o programa 1 ciclo de máquina.
    


   ***** TIMER 2 *****

   Ciclo de máquina = 1/16MHz = 62,5ns
    
   Overflow = (256 - TCNT2) * Prescaler * Ciclo de máquina
   Overflow = 156 * 1024 * 62,5ns
   Overflow = 9,98ms

   Logo, a interrupção do timer2 ocorrerá a cada 9,98ms ~= 10ms. 

*/

// Mapeamento de hardware
#define saida1 15
#define saida2 16

// Constantes auxiliares
#define NOP __asm__("nop\n\t");

ISR(TIMER2_OVF_vect){     // Função de interrupção utilizando os registradore do ATMega328P
  
    TCNT2 = 100;          // Reinicia a contagem do timer2 em 100, para contagem de 156

    digitalWrite(saida1, !digitalRead(saida1));
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    digitalWrite(saida2, !digitalRead(saida2));
}

void setup() {
  
    pinMode(saida1, OUTPUT);
    pinMode(saida2, OUTPUT);
    digitalWrite(saida1, LOW);
    digitalWrite(saida2, LOW);

    TCCR2A = 0x00;        // Configura a operação normal do timer2
    TCCR2B = 0x07;        // Configura os prescaler em 1:1024
    TCNT2 = 100;          // Inicia contagem do timer2 em 100, para contagem de 156
    TIMSK2 = 0x01;        // Habilita a interrupção por overflow do timer2
}

void loop() {

    // Apenas aguarda a interrupção...
}
