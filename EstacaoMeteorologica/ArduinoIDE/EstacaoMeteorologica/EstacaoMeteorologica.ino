/* 

                Este programa tem a função de imprimir no display LCD os valores de temperatura e umidade do ar, captados pelo sensor DHT11.

                Na prática o circuito e o programa funcionaram perfeitamente.

*/

// Inclusãode bibliotecas
#include <LiquidCrystal.h>
#include <dht.h>

// Mapeamento de hardware
#define dht_sinal 8

LiquidCrystal disp( 2,    // RS
                    3,    // E
                    4,    // d4
                    5,    // d5
                    6,    // d6
                    7);   // d7

// Variáveis auxiliares
int temperatura = 0x00;
int umidade = 0x00;
dht sensor;

void setup() {
  
    disp.begin(16,2);
    disp.clear();
} // end void setup

void loop() {

    sensor.read11(dht_sinal);

    temperatura = sensor.temperature;
    umidade = sensor.humidity;
    
    disp.setCursor(0,0);
    disp.print("Temperatura: ");
    disp.print(temperatura);
    disp.setCursor(0, 1);
    disp.print("Umidade: ");
    disp.print(umidade);
        
} // end void loop
