/*

        O objetivo deste programa é desenvolver o código para o robo autonomo projetado pelo professor, que utiliza servo motor, sensor ultrassônico,
    um drive para motores de e dois motores dc. Ainda, utiliza um trimpot para leitura ADC e controle de velocidade dos motores, através do PWM. 

        A fórmula de conversão de tempo em distância segue a seguinte regra de três:

        1s = 1000000us e velocidade do som de ida e volta do ultrassom = 340/2 = 170m/s = 17000cm/s


        1000000us ---------- 17000cm
            t     ---------- 1cm
                  t = 58,82us

        Logo, a cada 58,82us do tempo do pulso de echo, existe 1cm de distância do sensor a um obstáculo.

        Não tenho como testar o código, por não ter os motores nem o CI L293D, além das baterias, suporte e chassi do robô. Porém, o código está pronto,
    entendido e feito por mim mesmo, assim como o circuito. Quando eu puder, posso montar e testar este robô.

*/

// Inclusão de bibliotecas
#include <Servo.h>

// Mapeamento de hardware
#define in1 10
#define in2 11
#define en1 5
#define in4 8
#define in3 9
#define en2 6
#define pot A0
#define trig 13
#define echo 12
#define servoOut 7

// Protótipo de funções auxiliares
void move_Frente();
float leitura_Distancia();
void trigger();
void velocidade();
void tras();
void direita();
void esquerda();
void decisao();

// Variáveis auxiliares
Servo servo1;
float distancia = 0.0;
float dist_direita = 0.0;
float dist_esquerda = 0.0;

void setup() {

    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    pinMode(en1, OUTPUT);
    pinMode(in4, OUTPUT);
    pinMode(in3, OUTPUT);
    pinMode(en2, OUTPUT);
    pinMode(trig, OUTPUT);
    pinMode(pot, INPUT);
    pinMode (echo, INPUT);

    servo1.attach(servoOut);

    digitalWrite(trig, LOW);

    servo1.write(80);

    delay(500);
} // end void setup

void loop() {

    velocidade();

    move_Frente();

    distancia = leitura_Distancia();

    if(distancia < 20)
        decisao();
    
    delay(100);
} // end void loop


void move_Frente(){

    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
} // end void move_Frente


float leitura_Distancia(){

    float pulso = 0.0;
  
    trigger();

    pulso = pulseIn(echo, HIGH);

    pulso = pulso / 58.82;

    return pulso;
} // end float leitura_Distancia


void trigger(){
  
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);
} // end void trigger


void velocidade(){

    int leituraADC = 0x00;
  
    leituraADC = analogRead(pot);

    leituraADC = map(leituraADC, 0, 1023, 0, 255);

    analogWrite(en1, leituraADC);
    analogWrite(en2, leituraADC);
} // end void velocidade



void tras(){

    digitalWrite(en1, HIGH);
    digitalWrite(en2, HIGH);
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    
} // end void tras


void direita(){

    digitalWrite(en1, HIGH);
    digitalWrite(en2, HIGH);
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    
} // end void direita


void esquerda(){

    digitalWrite(en1, HIGH);
    digitalWrite(en2, HIGH);
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    
} // end void esquerda


void para(){

    digitalWrite(en1, LOW);
    digitalWrite(en2, LOW);
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    
} // end void para


void decisao(){
  
    para();
    delay(500);
    servo1.write(0);
    delay(500);
    dist_direita = leitura_Distancia();
    delay(2000);
    servo1.write(175);
    delay(500);
    dist_esquerda = leitura_Distancia();
    delay(2000);
    servo1.write(80);
    delay(500);

    if(dist_direita > dist_esquerda){
      
        tras();
        delay(600);
        direita();
        delay(2000);
        move_Frente();    
    } // end if
    else{

        tras();
        delay(600);
        esquerda();
        delay(2000);
        move_Frente();
    } // end else
} // end void decisao
