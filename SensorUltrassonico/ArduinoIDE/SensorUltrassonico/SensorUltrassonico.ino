/* 

        Este programa tem o objetivo de demonstrar o pulso de Trigger que é enviadoao sensor ultrasônico. A partir do Proteus será possível enxergar este pulso, utilizando o 
    osciloscòpio. O pulso de Trigger serve para acionar o sensor ultrassonico e começar um leitura de distância. Este pulso deve ser de 10us.
        Vale ressaltar que a pinagem do módulo Arduíno não é a mesma pinagem do microcontrolador ATMega328p. Portanto, na simulação do proteus, em que utilizo o microcontrolador
    para testar o código feito aqui, tenho que  descobrir qual é o pino do microcontolador que condiz com o pino aqui programado, que diz respeito à pinagem do módulo Arduíno Uno
        Ainda, o proteus parece não simular com leveza os cóigos, não fazendo as temportizações certas.

        Na simulação o dódigo cunfionou como esperado.      

*/

#define trigger 12

void setup() {
  
     pinMode(trigger, OUTPUT);                  // Configura o trigger, logo, pino 12, como saída digital 
     digitalWrite(trigger, LOW);                // Inicia trigger em Low

}

void loop() {

     digitalWrite(trigger, HIGH);               // Liga trigger
     delayMicroseconds(10);                     // Função de delay em microsegundos, logo, aguarda 100ms
     digitalWrite(trigger, LOW);                // Desliga trigger
     delay(100);                                // A função delay simples conta em milisegundos, logo, neste caso aguarda 100ms

}
