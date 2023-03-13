/* 

        O objetivo deste programa é configurar alguns registradores do ATMega328P para que seja possível alterar a frequência de um ou mais PWM's de
    saída. É possível configurar 7 frequências de PWM.

        Na simulação o programa funcionou como esperado.

*/

// Mapeamento de hardware
#define pwm1 3
#define pwm2 11

// Protótipos de funções auxiliares
void freq_pwm1(float val);
void freq_pwm2(float val);
void set_fequency(char opcao);

// Variáveis auxiliares
int adc = 0x00;

void setup() {
  
    pinMode(pwm1, OUTPUT);
    pinMode(pwm2, OUTPUT);

    TCCR2A = 0xA3;                      // Configura Fast PWM do ATMega328P e deslipa modo de comparação

    freq_pwm1(80);
    freq_pwm2(20);
    set_fequency(2);
    
} // end void setup

void loop() {

    adc = analogRead(A0);

    adc = map(adc, 0, 1023, 0, 100);

    freq_pwm1(adc);
} // end void loop

// Funções auxiliares

void freq_pwm1(float val){
  
    int duty;

    val = val/100;

    duty = (val * 256) - 1;

    OCR2B = duty;
} // end void freq_pwm1


void freq_pwm2(float val){
  
    int duty;

    val = val/100;

    duty = (val * 256) - 1;

    OCR2B = duty;
} // end void freq_pwm2


void set_fequency(char opcao){

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
} // end void set_frequency
