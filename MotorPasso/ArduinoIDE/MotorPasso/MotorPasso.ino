/* 

      O objetivo deste programa é fazer rodar um motor de passo. O sentido de roatação do motor dependerá do valor lido pelo ADC, que estará conectador a um potenciômetro. A 
   tabela que mostra os pulsos que o motor deve receber estão na pasta pinout. 
      O delay entre os pulsos mínimo que faz o motor girar é 2ms. Menos que isso o motor não gira. Poranto, com 2ms de delay é a velocidade que o motor gira com este tipo de
   acionamento.

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
