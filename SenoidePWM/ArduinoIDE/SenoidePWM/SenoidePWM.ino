/* 

          O objetivo deste programa é, a partir da função seno, do Arduíno, gerar uma variação do duty do PWM que varie de acordo com a função seno. Isto é, o duty do PWM irá
    de 0 a 255 com variação senoidal. Assim, a tensão na saída d10 irá variar de 0 a 5V de forma senoidal. Porém, o seno irá variar apenas de 0 a 180º, de forma que a função
    irá variar apenas de 0 a 1. Logo, não haverá ciclo negativo no sinal.
          Aplicando um filtro passa baixa na saída na qual o PWM, consegue-se criar um sinal analaógico na saída do Arduíno, de modo que a variação de tensão ocorra de forma
    analógica no pino d10.

          Na simulação e na prática o circuito e o programa funcionaram perfeitamente. 

*/

// Mapeamento de hardware
#define senoOut 10


// Variáveis auxiliares
float seno;
int senoDigital;

void setup() {
  
    pinMode(senoOut, OUTPUT);

    Serial.begin(9600);
} // end void setup

void loop() {

    for(int i = 0; i <= 180; i++){

        seno = sin(i*(3.1415/180.0));
        senoDigital = int(seno*255);

        analogWrite(senoOut, senoDigital);
        Serial.println(senoDigital);

        delay(5);
    } // end for
} // end void loop
