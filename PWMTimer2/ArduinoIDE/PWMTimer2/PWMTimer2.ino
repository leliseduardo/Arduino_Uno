/* 
  
            Este programa tem a função de criar uma saída PWM a partir do estouro do timer2. Alterando a variável PWM, altera-se o Duty Cicle do PWM, alterando o prescaler
     do timer2, altera-se a frequência do PWM.

            Na simulação o programa funcionou perfeitamente.
            
*/

boolean pwmControl = 0;
unsigned char pwm = 128;


ISR(TIMER2_OVF_vect){

    if(pwmControl){

        TCNT2 = pwm;
        PORTD &= ~(1 << PORTD4);
        pwmControl = 0;
    } // end if
    else{

        TCNT2 = 256 - pwm;
        PORTD |= (1 << PORTD4);
        pwmControl = 1;
    } // end else
}


void setup() {
  
    DDRD |= (1 << DDD4);
    PORTD &= ~(1 << PORTD4);

    TCCR2A = 0x00;              // Configura o timer2 em modo normal

//  TCCR2B = 0x04;              // Configura o prescaler em 1:64
    TCCR2B = 0x05;              // Configura o prescaler em 1:128
//  TCCR2B = 0x06;              // Configura o prescaler em 1:256  
    
    TIMSK2 = 0x01;              // Habilita a interrupção do timer2
}

void loop() {
  
    pwm += 10;
    delay(700);
}
