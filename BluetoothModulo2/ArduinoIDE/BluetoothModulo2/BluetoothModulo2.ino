/* ========================================================================================================
 
   Este código é copiado do professor e tem a função de utilizar o módulo Bluetooth. Nesse código o celular enviará um comando para o Arduino atrabés do Bluetooth, fazendo um led acender.


   Controle de LED por BlueTooth

    
   Autor: Eng. Wagner Rambo  Data: Janeiro de 2019
   
   www.wrkits.com.br | facebook.com/wrkits | youtube.com/user/canalwrkits


   Hardware:

               HC-05
                RX
 Arduino   ____  |  ____
 D1 TX ---|____|-o-|____|--- GND
           1.5k     2.2k

 Arduino      HC-05
 D0 RX  -----  TX
    5V  -----  VCC
   GND  -----  GND 
           
======================================================================================================== */

 
// ========================================================================================================
// --- Mapeamento de Hardware ---
#define   LED   13     //led onboard digital 13


// ========================================================================================================
// --- Variáveis Globais ---
String  LED_control;   //string para controle do LED


// ========================================================================================================
// --- Configurações Iniciais ---
void setup() 
{
  Serial.begin(9600);      //inicializa serial em 9600bps
  pinMode(LED, OUTPUT);    //configura saída para o led
  digitalWrite(LED, LOW);  //inicializa led desligado
  

} //end setup


// ========================================================================================================
// --- Loop Infinito ---
void loop() 
{
  while(Serial.available())   //aguarda dados
  {
    delay(5);                 //atrasa 5 ms

    char let = Serial.read(); //armazena bytes
    LED_control += let;       //na string de controle
    
  } //end while

  if(LED_control.length() > 0x00) //maior que zero?
  {                               //sim
    Serial.println(LED_control);  //imprime na Serial monitor

    //comando para ligar LED
    if(LED_control == "ledon") digitalWrite(LED, HIGH);

    //comando para desligar LED
    else if(LED_control == "ledoff") digitalWrite(LED, LOW);

    //comando para piscar led uma vez
    else if(LED_control == "led")
    {
       digitalWrite(LED, HIGH);
       delay(2000);
       digitalWrite(LED,  LOW);
       
    } //end led

    

    LED_control = ""; //limpa string
    
  } //end readString
  

} //end loop
