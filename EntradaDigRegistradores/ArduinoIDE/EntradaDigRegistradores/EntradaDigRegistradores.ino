/* 

            Este código tem a função de realizar a leitura de um botão, configurando uma entrada e uma saída digital através do registradores internos do ATMega328P.

            Na simulação e na prática o circuito e o programa funcionaram perfeitamente.

*/

// Mapeamento de hardware
#define bot1 (1 << 4)
#define led (1 << 5)

// Variáveis auxiliares
boolean flagB1 = 0x00;

void setup() {

    DDRB &= ~bot1;            // Configura o bit 4 de DDRB como entrada digital
    PORTB |= bot1;            // Habilita o pull-up interno do bit 4 do PORTB

    DDRB |= led;              // Configura o bit 5 de DDRB como saída digital

    while(1){
      
        if(!(PINB&bot1))   flagB1 = 0x01;             // PINB é o registrador que guarda o estado de cada entrada do PORTB

        if((PINB&bot1) && flagB1){
          
            flagB1 = 0x00;

            PORTB ^= led;
        } // end if 
    } // end while

}
