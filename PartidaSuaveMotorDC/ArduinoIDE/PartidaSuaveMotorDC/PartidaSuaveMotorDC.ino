/* 

          O objetivo deste programa é criar uma função que realize a partida suave de um motor DC.

          Na simulação e na prática o circuito e o programa funcionaram perfeitamente.

*/

// Mapeamento de hardware
#define motor 11

// Protótipo de funções auxiliares
void partida_Motor(int tempo);

// Variáveis auxiliares
int pwm = 0x00;

void setup() {

    pinMode(motor, OUTPUT);

    partida_Motor(5000);
}

void loop() {
  
    // Pode-se criar a aplicação que se quiser, inclusive alguma que desliga o motor e, para ligar novamente, chama a função partida_Motor.
}

void partida_Motor(int tempo){

    while(pwm < 0xFF){

        analogWrite(motor, pwm);

        pwm++;

        delayMicroseconds(tempo);
    } 

    pwm = 0x00;

    digitalWrite(motor, HIGH);
}
