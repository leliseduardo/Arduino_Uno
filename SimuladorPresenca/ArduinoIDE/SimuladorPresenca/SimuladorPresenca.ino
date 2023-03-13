/* 

            Este programa tem o objetivo de criar um simulador de presença. Isto é, um programa que alterna o acionamento de 4 saídas aleatóriamente.
       Estas saídas podem ser ligadas em um relé shield, que irá acionar as lampâdas de 4 cômodos diferentes a cada tempo que será definido aleatória-
       mente, simulando, assim, que existe pessoas dentro da casa, por exemplo.          

            Na simulação o circuito funcionou perfeitamente.
          
*/

// Mapeamento de hardware
#define lamp1 4
#define lamp2 5
#define lamp3 6
#define lamp4 7

void setup() {

    for(int i=4; i < 8; i++)
        pinMode(i, OUTPUT);

    for(int i=4; i < 8; i++)
        digitalWrite(i, LOW);

    randomSeed(analogRead(A0));
}

void loop() {
  
    digitalWrite(lamp1, HIGH);
    digitalWrite(lamp2, LOW);
    digitalWrite(lamp3, LOW);
    digitalWrite(lamp4, LOW);

    delay(random(2000, 8000));

    digitalWrite(lamp1, LOW);
    digitalWrite(lamp2, HIGH);
    digitalWrite(lamp3, LOW);
    digitalWrite(lamp4, LOW);

    delay(random(2000, 8000));

    digitalWrite(lamp1, LOW);
    digitalWrite(lamp2, LOW);
    digitalWrite(lamp3, HIGH);
    digitalWrite(lamp4, LOW);

    delay(random(2000, 8000));

    digitalWrite(lamp1, LOW);
    digitalWrite(lamp2, LOW);
    digitalWrite(lamp3, LOW);
    digitalWrite(lamp4, HIGH);

    delay(random(2000, 8000));
    
}
