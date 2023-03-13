/* 

        Este programa tem a função de criar um receptor de infravermelho que receba sinais PWM provenientes de outro Arduíno, o transmissor.

*/

// Mapeamento de hardware
#define infra 8

// Variáveis auxiliares
int pwm = 0;

void setup() {
  
    pinMode(infra, INPUT);

    Serial.begin(9600);
    
}

void loop() {
  
    pwm = pulseIn(infra, HIGH);
    pwm = map(pwm, 500, 1750, 0, 1023);

    Serial.println(pwm);

    delay(100);
}
