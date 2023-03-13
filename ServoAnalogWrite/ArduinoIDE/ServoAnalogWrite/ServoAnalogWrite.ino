/* 

          O objetivo deste programa é controlar o posicionamento de um Servo motor a partir da função analogWrite. Para isso, serão configurados alguns
      registrador do ATMega328P para que a frquênci a do PWM de saída seja alterada para uns 60Hz aproximadamente.
         
          Na simulação e na prática o circuito e o programa funcionaram perfeitamente. 
        
*/

// Mapemento de hardware
#define servo 3
#define pot A0

// Funções auxiliares
void set_Frequencia(int opcao);

// Variáveis auxiliares
int adc = 0x00;

void setup() {

    pinMode(pot, INPUT);
    pinMode(servo, OUTPUT);

    TCCR2A = 0xA3;              // Configura o timer2 como fast PWM e desliga o modo de comparação
    set_frequencia(7);          // Seta a frequencia dos pwm's do Arduino em 60Hz
}

void loop() {
  
    adc = analogRead(pot);

    adc = map(adc, 0, 1023, 10, 35);

    OCR2B = adc;                // OCR2B é o registrador que controla o PWM do OC2B, que é o pino D3 do mcu e d3 do Arduíno
    //analogWrite(servo, adc);
}

/* 

        Como o servo funciona com duty entre 0,6ms e 2,4ms, e a frequência do PWM configurada foi de aproximadamente 60Hz, então o período do PWM é
    16,67ms aproximadamente. Como o PWM tem resolução de 8bits, ele varia entra 0 e 255. Para descobrir qual valor do PWM equivale ao intervalo
    de período entra 0,6ms e 2,4ms, deve-se fazer uma regra de três:

        256 ----- 16,67ms
          x ----- 0,6ms
            x = 9,21
          Colocando um pouco acima do limite inferior, x = 10

        256 ----- 16,67ms
          x ----- 2,4ms
            x = 36,86
          Colocando um pouco abaixo do limite superior, x = 35
            
*/

void set_frequencia(int opcao){
  
    /*
    
        De acordo com a equação:

        freqPWM = Clock / (prescaler*256)

        Sendo prescaler configurado por TCCR2B, podendo ser 1, 8, 32, 64, 128, 256, 1024

        Usando, a equação acima, temos a seguinte tabela de frequencias para o PWM, de acordo com as opções de prescaler:

        Tabela:
  
        option  frequency
        
        1      62.5  kHz
        2       7.81 kHz
        3       1.95 kHz
        4     976.56  Hz
        5     488.28  Hz
        6     244.14  Hz
        7      61.03  Hz          
    
    */
  
    TCCR2B = opcao;
    
}
