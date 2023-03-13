/* 

        O objetivo deste programa é controlar um servo motor a partir da interrupção do timer2. Para isso, o timer2 criará um PWM que irá controlar o
     Servo.

     ***** Timer 2 *****

     Ciclo de máquina = 62,5ns
      
     Overflow = (256 - TCNT2) * prescaler * ciclo de maquina
     Overflow = 256 * 1024 * 62,5ns
     Overflow = 16,384ms

     ********************
     
     ***** Servo Motor ****

     256 ----- 16ms(periodo)
       x ----- 1ms(0º)
          x = 16

     O duty mínimo para o motor tem que ser de 1ms, considerando que esse valor representa 0º. Logo, se 256 representa todo o período do PWM, 16 é a 
     contagem mínima para que o duty mínimo, de 1ms, esteja na saída. 
     O valor de duty máximo é 2ms, logo, a contagem máximo para o duty máximo deve ser de 32. Como será o potenciômetro que irá controlar o ângulo, 
     quando ele estiver com a tensão máxima, o adc deve valer 16.

     duty = adc + 16

     quando adc = 0, duty = 16 = 1ms = 0º
     quando adc = 16, duty = 32 = 2ms = 180º

     Logo:

     1024 ----- 16
      adc ----- 1
          adc = 1024 / 16
          adc = 64

     Entao:

     leitura adc = adc/64

     se adc = 1024, leitura adc = 16
     se adc = 0, leitura adc = 0
     
     Na simulação e na prática o circuito e o programa funcionaram como esperado.

*/

// Mapeamento de hardware
#define servo 4
#define pot A0

// Variaveis auxiliares
int duty, adc;

// Função de interrupção
ISR(TIMER2_OVF_vect){
  
    if(digitalRead(servo)){

        TCNT2 = duty;

        digitalWrite(servo, LOW);
    } // end if    
    else{

        TCNT2 = 256 - duty;

        digitalWrite(servo, HIGH);
    } // end else
}

void setup() {
  
    pinMode(servo, OUTPUT);
    pinMode(pot, INPUT);

    TCCR2A = 0x00;                // Configura o timer2 para funcionamento normal
    TCCR2B = 0x07;                // Configuta o prescaler em 1:1024
    TCNT2 = 0x00;                 // Inicia a contagem do timer2 em 0, para contagem de 256
    TIMSK2 = 0x01;                // Habilita a interrupção por overflow do timer2
    
    digitalWrite(servo, LOW);
    
    duty = 16; 
}

void loop() {

    adc = analogRead(pot);

    duty = (adc/64) + 16;
}
