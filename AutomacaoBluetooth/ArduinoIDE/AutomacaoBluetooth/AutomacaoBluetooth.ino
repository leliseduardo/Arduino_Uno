/* ========================================================================================================
 
   Este código é copiado do professor e tem a função de acionar dois relés através do celular. Para isso, utiliza-se o módulo Bluetooth.

   Automação Residencial com Bluetooth
   Controle de Relés

    
   Autor: Eng. Wagner Rambo  Data: Fevereiro de 2019
   
   www.wrkits.com.br | facebook.com/wrkits | youtube.com/user/canalwrkits


   Hardware módulo Bluetooth:

               HC-05
                RX
 Arduino   ____  |  ____
 D1 TX ---|____|-o-|____|--- GND
           1.5k     2.2k

 Arduino      HC-05
 D0 RX  -----  TX
    5V  -----  VCC
   GND  -----  GND 


   Hardware Relés:

   *Pesquise por WR Kits controle de relés no YouTube
   *Ou utilize um Relé Shield
           
======================================================================================================== */

 
// ========================================================================================================
// --- Mapeamento de Hardware ---
#define   relay1    6
#define   relay2    7


// ========================================================================================================
// --- Variáveis Globais ---
String  rel_control;   //string para controle dos relés


// ========================================================================================================
// --- Configurações Iniciais ---
void setup() 
{
  Serial.begin(9600);      //inicializa serial em 9600bps
  pinMode(relay1, OUTPUT);    //configura saída para o relé 1
  pinMode(relay2, OUTPUT);    //configura saída para o relé 2

  digitalWrite(relay1, LOW);  //inicializa relé 1 desligado
  digitalWrite(relay2, LOW);  //inicializa relé 2 desligado
  

} //end setup


// ========================================================================================================
// --- Loop Infinito ---
void loop() 
{
  while(Serial.available())   //aguarda dados
  {
    delay(5);                 //atrasa 5 ms

    char let = Serial.read(); //armazena bytes
    rel_control += let;       //na string de controle
    
  } //end while

  if(rel_control.length() > 0x00) //maior que zero?
  {                               //sim
    Serial.println(rel_control);  //imprime na Serial monitor


    if(rel_control == "re1")
    {
      digitalWrite(relay1, !digitalRead(relay1)); //inverte estado de relé 1
      
      if(digitalRead(relay1)) Serial.println("Lampada da sala ligada");  
      else                    Serial.println("Lampada da sala desligada");
      
    } //end if re1

    else if(rel_control == "re2")
    {
      digitalWrite(relay2, !digitalRead(relay2)); //inverte estado de relé 2
      
      if(digitalRead(relay2)) Serial.println("Lampada do quarto ligada");  
      else                    Serial.println("Lampada do quarto desligada");
      
    } //end if re2

    
    rel_control = ""; //limpa string
    
  } //end readString
  

} //end loop
