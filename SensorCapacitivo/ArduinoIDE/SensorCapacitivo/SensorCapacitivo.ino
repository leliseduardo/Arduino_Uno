/* 

                O objetivo deste programa é demonstrar o uso do sensor capacitivo, que gera um pulso positivo quando o dedo toca no sensor. Ele funciona basicamente como um
         botão. Logo, o programa para usá-lo é bem simples.

                Na simulação o circuito e o programa funcionaram como esperado.

*/

// Mapeamento de hardware
#define sensor 4
#define led 13

void setup() {

    pinMode(sensor, INPUT);
    pinMode(led, OUTPUT);
} // end void setup

void loop() {

    if(digitalRead(sensor))
        digitalWrite(led, !digitalRead(led));

    delay(100);
} // end void loop
