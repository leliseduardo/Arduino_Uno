/* 

            Este código tem o objetivo de utilizar o timer1 para mudar o tempo de atualizaçao do display LCD.

            Na simulação e na prática o circuito e o programa funcionaram como esperado.

*/

// Inclusão de bibliotecas
#include <LiquidCrystal.h>

// Mapeamento de hardware
#define led PB5
#define pot A0
LiquidCrystal disp( 2,  // RS
                    3,  // E
                    4,  // D4
                    5,  // D5
                    6,  // D6
                    7); // D7    

// Constantes 
const uint16_t T1_inicio = 0;
const uint16_t T1_comp = 31250;

// Variáveis auxiliares
int cont = 0x00;
boolean control = 0;
int adc;

// Função de interrupção
ISR(TIMER1_COMPA_vect){

    TCNT1 = T1_inicio;              // Reinicializa os registradores
    PORTB ^= (1 << led);            // Inverte nível lógico de led

    cont++;

    if(cont == 0x08){

        cont = 0x00;
      
        control = 1;     
    }
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

    disp.begin(16, 2);
    Serial.begin(9600);
    
}

void loop() {
  
    adc = analogRead(pot);

    adc = map(adc, 0, 1023, 0, 255);

    if(control){

        Serial.print("Valor: ");
        Serial.println(adc);

        disp.clear();
        disp.setCursor(3, 0);
        disp.print("Valor: ");
        disp.setCursor(3, 1);
        disp.print(adc);

        control = 0;
    }
}
