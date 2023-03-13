/* 

          Este programa tem a função de ler um sensor de nível de água. Quando o sensor detectar que o nível de água passou do nível desejado, ele irá acionar com nível lógico
    zero, e a partir disso, aciona um buzzer e uma possível bomba d'água é desligada. 

          Na simulação o circuito e o programa funcionaram como esperado.
          
*/

// Mapeamento de hardware
#define sensor 5
#define buzzer 6
#define bomba 7

// Protótipos de funções auxiliares
void leitura_Sensor();

// Variáveis auxiliares
int cont = 0x00;


// Função de interrupção
ISR(TIMER2_OVF_vect){

    TCNT2 = 0x64;
    cont++;

    if(cont == 0x64){
      
        cont = 0x00;

        digitalWrite(buzzer, !digitalRead(buzzer));
    }
}

void setup() {

    pinMode(sensor, INPUT_PULLUP);
    pinMode(buzzer, OUTPUT);
    pinMode(bomba, OUTPUT);

    digitalWrite(buzzer, LOW);
    digitalWrite(bomba, LOW);

    TCCR2A = 0x00;              // Timer2 operando no modo normal
    TCCR2B = 0x07;              // Prescaler 1:1024
    TCNT2 = 0x64;               // Inicia a contagem em 100d, para overflow = 10ms
    TIMSK2 = 0x00;              // Desabilita a interrupção por overflow do timer2, inicialmente
}

void loop() {

    leitura_Sensor();
}


// Funções auxiliares

void leitura_Sensor(){
  
    if(digitalRead(sensor)){
      
        digitalWrite(bomba, LOW);
        TIMSK2 = 0x01;                // Habilita a interrupção por overflow do timer2
    }  
    else{

        digitalWrite(buzzer, LOW);
        digitalWrite(bomba, HIGH);
        TIMSK2 = 0x00;                // Desabilita a interrupção por overflow do timer2
    }
}
