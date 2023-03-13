/* 

            O objetivo deste programa é utilizar o sensor de umidade e temperatura DHT11, a partir da biblioteca para este sensor. A umidade e temperatura serão impressos 
       pelo serial do Arduíno. 

            Na prática o programa funcionou perfeitamente, tanto na leitura Serial quando no Serial Plotter.

*/

// Inclusão de bibliotecas
#include <dht.h>


// Mapeamento de hardware
#define dht_sinal 5

// Variáveis auxiliares
int umidade = 0x00;
int temperatura = 0x00;

dht sensor;

void setup() {

    Serial.begin(9600);
}

void loop() {

    sensor.read11(dht_sinal);

    umidade = sensor.humidity;
    temperatura = sensor.temperature;

    Serial.print(temperatura);
    Serial.print(" ");
    Serial.println(umidade);

//    Serial.print(temperatura);
//    Serial.print(" C");
//    Serial.print(" \t");
//    Serial.print(umidade);
//    Serial.println("%");

    delay(10);
}
