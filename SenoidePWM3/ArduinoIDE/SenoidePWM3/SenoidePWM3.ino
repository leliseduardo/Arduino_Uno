/* 

          O objetivo deste programa é utilizar o código da aula passada, denominada "SenoidePWM2" e modifica-la para que a frequência da senoide seja alterada de acordo com a
    leitura de um potenciômetro na entrada analalógica A0.

         Na simulação e na prática o circuito e o programa funcionaram perfeitamente.

*/

// Mapeamento de hardware
#define senoOut 10


// Variáveis auxiliares
float seno;
int senoDigital;

void setup() {
  
    pinMode(senoOut, OUTPUT);

    Serial.begin(9600);
} // end void setup

void loop() {

    for(int i = -180; i < 180; i++){

        seno = sin(i*(3.1415/180.0)*(map(analogRead(A0), 0, 1023, 1, 33)));
        senoDigital = 127+int(seno*255/2.0);

        analogWrite(senoOut, senoDigital);
        Serial.println(senoDigital);

        delay(5);
    } // end for
} // end void loop
