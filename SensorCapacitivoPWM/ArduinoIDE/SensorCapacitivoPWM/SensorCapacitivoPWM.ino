/* 

                Neste programa, dois sensores capacitivos serão usados para incrementar e decrementar um PWM de saída, no pino 6. A leitura dos sensores será feita através
        das interrrupções externas. Assim, consegue-se utilizar os sensores como se fossem botões. 

                Na simulação o circuito e o programa funcionaram.

*/

// Mapeamento de hardware
#define sensor1 2
#define sensor2 3
#define pwmOut 6

// Variáveis auxiliares
byte pwm = 128;

void leitura_Sensor1(){                                    // Função que a interrupção externa INT0 chama
  
    pwm += 10;
} // end void leitura_Sensor

void leitura_Sensor2(){                                    // Função que a interrupção externa INT1 chama
  
    pwm -= 10;
} // end void leitura_Sensor

void setup() {

    pinMode(sensor1, INPUT);
    pinMode(sensor2, INPUT);
    pinMode(pwmOut, OUTPUT);

    attachInterrupt(0, leitura_Sensor1, RISING);           // Função que faz a interrupção externa INT0 executar a função leitura_Sensor quando houver borda de subida
    attachInterrupt(1, leitura_Sensor2, RISING);           // Função que faz a interrupção externa INT0 executar a função leitura_Sensor quando houver borda de subida
  
} // end void setup

void loop() {

    analogWrite(pwmOut, pwm);   
} // end void loop
