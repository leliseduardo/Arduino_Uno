/* 

        O objetivo deste programa é criar um código simples para um robo autonômo simples, que controla dois motores e lê dois sensores. O objetivo do rôbo é andar pra frente e
    quando o sensor da esquerda for setado, ele para, anda para trás e faz um desvio à direita. Dai volta a andar parar frente. Se o sensor da direita é setado, o processo é o
    mesmo.

        Na simulação o circuito e o programa funcionaram perfeitamente.

*/

// Mapeamento de hardware
#define sensorE 6
#define sensorD 7
#define m1a 8
#define m1b 9
#define m2a 10
#define m2b 11

// Protótipo de funções auxiliares
void frente();
void tras();
void direita();
void esquerda();
void para();
void desvia_direita();
void desvia_esquerda();

void setup() {

    pinMode(sensorE, INPUT_PULLUP);
    pinMode(sensorD, INPUT_PULLUP);
    pinMode(m1a, OUTPUT);
    pinMode(m1b, OUTPUT);
    pinMode(m2a, OUTPUT);
    pinMode(m2b, OUTPUT);
    
} // end void setup

void loop() {
  
   frente();

   if(!digitalRead(sensorE))
      desvia_direita();
   else if(!digitalRead(sensorD))
      desvia_esquerda();

   delay(100);

} // end void loop


void frente(){
  
    digitalWrite(m1a, HIGH);
    digitalWrite(m1b, LOW);
    digitalWrite(m2a, LOW);
    digitalWrite(m2b, HIGH);
    
} // end void frente


void tras(){
  
    digitalWrite(m1a, LOW);
    digitalWrite(m1b, HIGH);
    digitalWrite(m2a, HIGH);
    digitalWrite(m2b, LOW);
    
} // end void tras


void direita(){
  
    digitalWrite(m1a, HIGH);
    digitalWrite(m1b, LOW);
    digitalWrite(m2a, HIGH);
    digitalWrite(m2b, LOW);
    
} // end void direita


void esquerda(){
  
    digitalWrite(m1a, LOW);
    digitalWrite(m1b, HIGH);
    digitalWrite(m2a, LOW);
    digitalWrite(m2b, HIGH);
    
} // end void esquerda


void para(){
  
    digitalWrite(m1a, LOW);
    digitalWrite(m1b, LOW);
    digitalWrite(m2a, LOW);
    digitalWrite(m2b, LOW);
    
} // end void para

void desvia_direita(){
  
    para();
    delay(1000);
    tras();
    delay(1000);
    direita();
    delay(1000);
    frente();
    
} // end desvia direita


void desvia_esquerda(){
  
    para();
    delay(1000);
    tras();
    delay(1000);
    esquerda();
    delay(1000);
    frente();
    
} // end desvia esquerda
