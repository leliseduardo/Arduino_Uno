/*

            Este código tem a função de controlar dois servos a partir de uma página Web, utilizando o ESP8266. Vale ressaltar que a biblioteca SoftwareSerial está 
     descontinuada e não é a melhor forma de utilizar o ESP8266.

            Na prática o circuito e o programa NÃO funcionaram. Porém, o uso do ESP8266 não é simples e não foi ensinado completamente, de forma que não dá para saber o que
     foi feito, tanto na biblioteca utilizada quanto no código feito. Principalmente pelo motivo de serem utilizadas conexões em rede e códigos HTML. Um estudo focado apenas
     em ESP's será feito assim que possível.
   
*/

// =============================================================================================================
// --- Bibliotecas ---
#include <SoftwareSerial.h>    //inclui biblioteca software serial
#include <Servo.h>             //inclui biblioteca para controle dos servos


// =============================================================================================================
// --- Objetos ---
SoftwareSerial esp8266(5, 4);  //pino TX do ESP8266 ligado no digital 5 e RX no digital 4  
Servo sv1;                     //servo motor 1
Servo sv2;                     //servo motor 2

 
// =============================================================================================================
// --- Constantes e Mapeamento de Hardware ---
#define DEBUG true             //DEBUG no serial monitor
#define serv1 9                //servo motor 1 
#define serv2 10               //servo motor 2  


// =============================================================================================================
// --- Protótipo das Funções ---
String sendData(String command, const int timeout, boolean debug);


// =============================================================================================================
// --- Variáveis Globais ---
int   pos1     = 175,          //armazena posição do servo 1
      pos2     = 175,          //armazena posição do servo 2
      vel      =  10,          //velocidade dos servos (100 -> 90º in 1 s)(1 -> 90º in 9 s)
      pos1min  =  15,          //posição mínima do servo 1
      pos2min  =  15,          //posição mínima do servo 2
      pos1max  = 160,          //posição máxima do servo 1
      pos2max  = 160;          //posição máxima do servo 2
 
 
// =============================================================================================================
// --- Configurações Iniciais ---
void setup()
{
 
  // -- Configura Servos e Posições Iniciais --
  sv1.attach(serv1);
  sv2.attach(serv2);
  sv1.write(pos1max);
  sv2.write(pos2max);
  sv1.detach();
  sv2.detach();
 
  // -- Inicia Comunicação Serial --
  Serial.begin(9600);
  esp8266.begin(115200);

  // -- Configura WiFi --
  // ============================
  sendData("AT+RST\r\n", 2000, DEBUG);                                   //reset no modulo
  sendData("AT+CWMODE=1\r\n", 1000, DEBUG);                              //modo station
  sendData("AT+CWJAP=\"Nome da Rede\",\"Senha da Rede\"\r\n", 2000, DEBUG);   //conecta com rede Wifi (nome e senha)
  while(!esp8266.find("OK"));                                            //aguarda até que haja conexão
  
  sendData("AT+CIFSR\r\n", 1000, DEBUG);                                 //mostra endereço IP
  sendData("AT+CIPMUX=1\r\n", 1000, DEBUG);                              //permite múltiplas conexões
  sendData("AT+CIPSERVER=1,80\r\n", 1000, DEBUG);                        //inicia web server na porta 80
  
} //end setup
 

// =============================================================================================================
// --- Loop Infinito ---
void loop()
{
  
  if (esp8266.available())  //verifica se existem dados disponíveis no ESP8266
  {
    if (esp8266.find("+IPD,")) //novo comando?
    {                          //Sim
      String msg;
      esp8266.find("?");                    //movimenta cursor até encontrar conteúdo da mensagem
      msg = esp8266.readStringUntil(' ');   //lê mensagem
      String command = msg.substring(0, 3); //"sr1" = comando para o servo #1 e "sr2" = comando para o servo #2
      String valueStr = msg.substring(4);   //os 3 caracteres seguintes informam o ângulo desejado
      int value = valueStr.toInt();
      if (DEBUG) {
        Serial.println(command);
        Serial.println(value);
      }
      delay(100);
 
  
      //-- controle do servo 1 --
      if(command == "sr1") 
      {
        //limita ângulo do servo
        if (value >= pos1max) value = pos1max;      
        
        if (value <= pos1min) value = pos1min;
          
    
        sv1.attach(serv1); //conecta servo1
        while(pos1 != value) 
        {
          if (pos1 > value) 
          {
            pos1 -= 1;
            sv1.write(pos1);
            delay(100/vel);
          }
          if (pos1 < value) 
          {
            pos1 += 1;
            sv1.write(pos1);
            delay(100/vel);
          }
        } //end while
        sv1.detach(); //desconecta servo1
      
      } //end controle servo1

 
      //-- controle do servo 2 --
      if(command == "sr2") 
      {
        //limita ângulo do servo
        if (value >= pos2max) value = pos2max;
  
        if (value <= pos2min) value = pos2min;

         
        sv2.attach(serv2); //conecta servo2
        while(pos2 != value) 
        {
          if (pos2 > value) 
          {
            pos2 -= 1;
            sv2.write(pos2);
            delay(100/vel);
          }
          if (pos2 < value) 
          {
            pos2 += 1;
            sv2.write(pos2);
            delay(100/vel);
          }
        } //end while   
        sv2.detach(); //desconecta servo 2 
            
      } //end controle servo 2 
    }
  }
  
} //end loop
 
 
// =============================================================================================================
// --- Função ---
String sendData(String command, const int timeout, boolean debug)
{
  String response = "";
  esp8266.print(command);
  long int time = millis();
  while ( (time + timeout) > millis())
  {
    while (esp8266.available())
    {
      char c = esp8266.read();
      response += c;
    }
  }
  if (debug)
  {
    Serial.print(response);
  }
  return response;

} //end sendData
