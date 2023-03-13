/* 

        Este programa tem a função de criar um transmissor de infravermelho que envie sinais PWM, com duty variável proporcional à leitura do conversor AD.

*/

// Mapeamento de hardware
#define infra 9
#define pot A0

// Variáveis auxiliares
unsigned char pwm = 128;

void setup() {
  
    pinMode(infra, OUTPUT);
    analogWrite(infra, pwm);
    
}

void loop() {
  
    pwm = map(analogRead(pot), 0, 1023, 50, 200);

    analogWrite(infra, pwm); 
}
