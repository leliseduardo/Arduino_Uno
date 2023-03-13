/*

            O objetivo deste programa é ajustar o brilho de um led atrabés de um potenciômetro. Para isso, uma entrada ADC irá ler o potenciômetro e,
       a partir do valor lido, o um PWM de saída irá ajustar o brilho do Led.

            Na simulação e na prática o circuito e o programa funcionaram como esperado.

*/

// Mapeamento de hardware
#define led 3
#define pot A0

// Variáveis auxiliares
int adc = 0x00;
int pwm = 0x00;

void setup() {

    pinMode(pot, INPUT);
    pinMode(led, OUTPUT);

    digitalWrite(led, LOW);
}

void loop() {

    adc = analogRead(pot);

    pwm = map(adc, 0, 1023, 0, 255);

    analogWrite(led, pwm);
}
