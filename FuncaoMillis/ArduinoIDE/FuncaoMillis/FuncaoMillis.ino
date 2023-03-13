/* 

            Este código tem a função de demonstrar uma aplicação para a função millis. Através da interrupção externa, será descoberto o tempo que um pulso leva para acionar
      a interrupção externa. Aqui, será usado um pulso no pino 13, mas poderia ser um pulso de uma fonte externa. Com este programa, será possível descobrir o tempo de meio
      período do sinal que causa a interrupção.
            Como dito, o programa imprime no terminal serial o tempo de meio período.

            Na prática o circuito e o programa funcionaram perfeitamente.
           
*/


// Mapeamento de hardware
#define Out 13

// Variáveis auxiliares
int control = 0x00;
unsigned long tempoAux = 0, tempo = 0, aux = 0;

ISR(INT0_vect){

    control = 0x01;

    aux = millis();

    tempo = aux - tempoAux;
    
} // end ISR

void setup() {
  
    pinMode(Out, OUTPUT);
    digitalWrite(Out, LOW);

    EICRA |= (1 << ISC01) | (1 << ISC00);     // Configura a interrupção externa como borda de subida
    EIMSK |= (1 << INT0);                     // Habilita a interrupção externa 0

    sei();                                    // Liga interrupções    

    Serial.begin(9600);
    Serial.println("Iniciando...");
}

void loop() {

    

    if(control){

        control = 0x00;
        
        tempoAux = millis();
    } // end if

    Serial.print("Tempo = ");
    Serial.println(tempo);

    digitalWrite(Out, !digitalRead(Out));
    delay(1000);
}
