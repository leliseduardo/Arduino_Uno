/* 

            Este código exemplifica o uso da biblioteca Ultrassonico_Lib.

            Escolha dois pinos digitais para trigger e echo e especifique tais pinos na criação do objeto.

*/

// Inclusão da biblioteca
#include <Ultrassonico_Lib.h>

// Criação do objeto
Ultrassonico_Lib ultra(11, 12);             // define trigger em d11, e echo em d12

// Variáveis globais auxiliares
float dist;

void setup() {
 
    Serial.begin(9600);
}

void loop() {
  
    // Para distancias em cm
    dist = ultra.distancia_cm();

    Serial.print("Distancia em cm: ");
    Serial.print(dist);
    Serial.print(" cm");

    Serial.print(" || ");

    // Para distancias em polegadas
    dist = ultra.distancia_pol();

    Serial.print("Distancia em pol: ");
    Serial.print(dist);
    Serial.println(" Pol");

    delay(741);
}
