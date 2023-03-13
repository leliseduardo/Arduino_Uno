/* 

          O objetivo deste programa é utilizar o código da aula passada, denominada "SenoidePWM" e modifica-la para que a saída seja uma senoide completa, e não apenas os
    semi-ciclos positivos.

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

        seno = sin(i*(3.1415/180.0));
        senoDigital = 127+int(seno*255/2.0);

        analogWrite(senoOut, senoDigital);
        Serial.println(senoDigital);

        delay(5);
    } // end for
} // end void loop
