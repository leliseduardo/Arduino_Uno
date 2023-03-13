/* 

        O objetivo deste programa é criar uma aplicação para o projeto exemplo do Arduíno Standalone. O Arduíno Standalone é um projeto que utiliza um ATMega328p com seu 
    circuito mínimo numa protoboard ou em uma PCB prórpia. Assim, pode-se profissionalizar circuios e projetos com o Arduíno. O projeto exemplo será a leitura ADC de um 
    circuito divisor de tensão que possui um LDR, que varia sua resistência de acordo com a luminosidade ambiente. Assim, de acordo com a leitura, será controlado o brilho
    de um led, através de um PWM.

        Na prática o circuito funcionou como esperado. 

*/

// Mapeamento de hardware
#define ldr A0
#define led 9

// Variáveis auxiliares
int leitura = 0;

void setup() {

    pinMode(ldr, INPUT);
    pinMode(led, OUTPUT);
} // end void setup

void loop() {

    leitura = analogRead(ldr);

    leitura = map(leitura, 0, 1023, 0, 255);

    analogWrite(led, leitura);

    delay(100);
} // end void loop
