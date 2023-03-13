/* 

      O objetivo deste programa é muito parecido com o projeto "MotorPasso", por isso, o código é o mesmo. O motor de passo gira em um sentido caso o potenciômetro
   esteja lendo um valor maior que 2,5V e gira no sentido contrário caso a tensão lida pelo potenciômetro seja menor que 2,5V.

      Na prática o programa e o circuito funcionaram perfeitamente.

*/


// Protótipo de funções auxiliares
void sentido_Motor();
void gira_Horario();
void gira_AntiHorario();

// Variáveis auxiliares
int adc;

void setup() {

    for(int i=8; i < 12; i++)
        pinMode(i, OUTPUT);

    pinMode(A0, INPUT);

} // end void setup

void loop() {

    sentido_Motor();  
} // end void loop

void sentido_Motor(){
  
    adc = analogRead(A0);

    if(adc >= 512)
        gira_Horario();
    else
        gira_AntiHorario();
       
} // end void sentido_Motor


void gira_Horario(){
  
    PORTB = 0x03;
    delay(2);
    PORTB = 0x06;
    delay(2);
    PORTB = 0x0C;
    delay(2);
    PORTB = 0x09;
    delay(2);
} // end void gira_AntiHorario


void gira_AntiHorario(){
  
    PORTB = 0x09;
    delay(2);
    PORTB = 0x0C;
    delay(2);
    PORTB = 0x06;
    delay(2);
    PORTB = 0x03;
    delay(2);
} // end void gira_Horario
