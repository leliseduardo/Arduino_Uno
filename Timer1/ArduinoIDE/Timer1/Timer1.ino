/* 

            Este código tem o objetivo de mostrar a configuração da interrupção por comparação do timer1. Esta interrupção irá comparar o contador do timer1 com o contador do
       comparador. No PDF que está na pasta do projeto está um visão geral do timer1.

            Na prática o programa funcionou como esperado.

*/

// Mapeamento de hardware
#define led PB5

// Constantes 
const uint16_t T1_inicio = 0;
const uint16_t T1_comp = 31250;


// Função de interrupção
ISR(TIMER1_COMPA_vect){

    TCNT1 = T1_inicio;              // Reinicializa os registradores
    PORTB ^= (1 << led);            // Inverte nível lógico de led
} // end void ISR

void setup(){

    DDRB |= (1 << led);             // Configura led como saída

    TCCR1A = 0x00;                  // Configura o timer1 para funcionamento normal, que é a contagem de seu contador
    
    TCCR1B |= (1 << CS12);          // As três flags de TCCR1B configuram o prescaler em 1:256
    TCCR1B &= ~(1 << CS11);
    TCCR1B &= ~(1 << CS10);

    TCNT1 = T1_inicio;              // Inicializa os registradores
    OCR1A = T1_comp;

    TIMSK1 = (1 << OCIE1A);         // Habilita a interrupção por comparação do timer1
    
}

void loop() {
  // put your main code here, to run repeatedly:

}
