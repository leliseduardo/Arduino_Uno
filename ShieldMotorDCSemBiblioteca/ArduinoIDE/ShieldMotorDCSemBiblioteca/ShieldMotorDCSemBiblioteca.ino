/*
   
            Este código é copiado do professor. Ele demonstrou como controlar o shield de motor DC, que utiliza um registrador de deslocamento SN74HC595.
     Este registrador controla dois CI's de ponte H L293D para, assim, controlar os motores DC.
            Este código ficará salvo para possíveis consultas futuras.
   
*/

// --- Mapeamento de Hardware ---
#define   dir_clk      4     //clock do registrador no digital  4
#define   dir_ser      8     //dados do registrador no digital  8
#define   dir_latch   12     //latch do registrador no digital 12
#define   dir_en       7     //enable do registrador no digital 7
#define   pwm2a       11     //pwm motor1
#define   pwm2b        3     //pwm motor2
#define   pwm0a        6     //pwm motor3
#define   pwm0b        5     //pwm motor4


// --- Protótipo das Funções Auxiliares ---
void sendCommand(unsigned char value);   //Função para enviar o byte para saída do registrador


// --- Configurações Iniciais ---
void setup() 
{
  pinMode(dir_clk,   OUTPUT);    //saída para clock
  pinMode(dir_ser,   OUTPUT);    //saída para dados
  pinMode(dir_latch, OUTPUT);    //saída para latch
  pinMode(dir_en,    OUTPUT);    //saída para enable
  pinMode(pwm2a,     OUTPUT);    //saída para pwm motor1
  pinMode(pwm2b,     OUTPUT);    //saída para pwm motor2
  pinMode(pwm0a,     OUTPUT);    //saída para pwm motor3
  pinMode(pwm0b,     OUTPUT);    //saída para pwm motor4
  
  digitalWrite(dir_en, LOW);
  analogWrite(pwm2a, 0xFF);
  analogWrite(pwm2b, 0xFF);
  analogWrite(pwm0a, 0xFF);
  analogWrite(pwm0b, 0xFF);
  


} //end setup


// --- Loop Infinito ---
void loop() 
{
  
  sendCommand(0b10101100);
  delay(2000);
  sendCommand(0b01010011);
  delay(2000);


} //end loop


// --- Desenvolvimento das Funções Auxiliares ---
void sendCommand(unsigned char value)
{
  
    boolean verify;                  //bit de controle

    digitalWrite(dir_latch, LOW);    //desliga latch
    digitalWrite(dir_clk,   LOW);    //desabilita o clock
    
    for(unsigned char i=0x0; i<0x08; i++)    //loop finito para enviar os 8 bits
    {
       digitalWrite(dir_clk, LOW);   //clock em low
       
       if(value & (1<<i)) verify = HIGH;
       else verify = LOW;
       
       digitalWrite(dir_ser, verify); //Habilita saída de dados conforme condição acima
       digitalWrite(dir_clk, HIGH);
    
    } //end for
    
    
    digitalWrite(dir_clk, LOW);
    
    digitalWrite(dir_latch, HIGH);


} //end sendCommand
