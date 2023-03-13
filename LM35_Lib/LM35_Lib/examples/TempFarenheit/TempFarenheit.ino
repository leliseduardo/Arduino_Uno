/* 

        Exemplo de uso da biblioteca LM35_Lib

        Conecte o LM35 em uma das entradas analógicas e especifique a entrada na criação do objeto, assim como o exemplo.

*/

// Inclusão da biblioteca
#include <LM35_Lib.h>

// Criação do objeto
LM35_Lib  t(A0);

// Variáveis globais auxiliares
float temp;

void setup() {

    Serial.begin(9600);
}

void loop() {
  
    temp = t.farenheit();

    Serial.print("Temperatura: ");
    Serial.print(temp);
    Serial.println("F");

    delay(741);
}
