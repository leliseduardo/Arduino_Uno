/* 
  
            Este código tem a função de, a partir da utilização do código da aula passada, denominada "PWMTimer2", fazer com que o PWM do pino d4 altere de acordo com a 
     leitura de um LDR pelo ADC. Assim, quanto maior a luminosidade no LDR, menor será o PWM e menor será o brilho de um led conectado ao d4. Da mesma forma, quanto mais 
     escuro estiver o ambiente, maior seráo duty e maior será o brilho do led. 

            Na simulação e na prática o circuito e o programa funcionaram perfeitamente.
            
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
  
    pwm = map(analogRead(A0), 0, 1023, 255, 0);
}
