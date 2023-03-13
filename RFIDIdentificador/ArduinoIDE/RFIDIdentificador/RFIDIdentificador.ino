/*

            Este cógido é copiado do professor e tem a função de demonstrar no display o usuário no qual a tag RFID foi identificada. 
   
*/

// --- Bibliotecas Auxiliares ---
#include <SPI.h>                                        //Biblioteca SPI
#include <MFRC522.h>                                    //Biblioteca para RFID
#include <LiquidCrystal.h>                              //Biblioteca para o display LCD


// --- Mapeamento de Hardware ---
#define   buzzer    16  //buzzer no A2
#define   door_lock 15  //atuador no A1
#define   door_sens 14  //sensor da porta no A0
#define   SS_PIN    10  //RFID SS
#define   RST_PIN    9  //RFID RST



// --- Hardware do LCD ---
LiquidCrystal disp(8,  //RS no digital 8
                   7,  //EN no digital 7
                   5,  //D4 no digital 5
                   4,  //D5 no digital 4
                   3,  //D6 no digital 3
                   2); //D7 no digital 2


MFRC522 mfrc522(SS_PIN, RST_PIN);   // Cria instância com MFRC522


// --- Protótipo das Funções Auxiliares ---
void rfid_func();                            //Função para identificação das tags RFID
void systemBoot();                           //Função para exibir boot do sistema
 
 

// --- Variáveis Globais --- 
char st[20];
short invalid_counter = 0x00;  //armazena número de tentativas com tags inválidas



// --- Configurações Iniciais ---
void setup() 
{

  disp.begin(16,2);                                      //Inicializa LCD 16 x 2

  
 // -- Entradas e Saídas
  pinMode(buzzer,    OUTPUT);
  pinMode(door_lock, OUTPUT);
  pinMode(door_sens, INPUT_PULLUP); //sensor de porta
  
  Serial.begin(9600);   // Inicia comunicação Serial em 9600 baud rate
  SPI.begin();          // Inicia comunicação SPI bus
  mfrc522.PCD_Init();   // Inicia MFRC522
  
  Serial.println("Aproxime o seu cartao do leitor...");
  Serial.println();

  //saídas iniciam desligadas
  digitalWrite(door_lock, LOW);
  digitalWrite(buzzer,    LOW);



   systemBoot();                                        //mensagens de inicialização


   
   
  
} //end setup


// --- Loop Infinito ---
void loop() 
{


    disp.setCursor(0,0);                                 //Posiciona cursor na coluna 1, linha 1
    disp.print("Aproxime a tag");                        //Imprime mensagem
    disp.setCursor(0,1);                                 //Posiciona cursor na coluna 1, linha 2
    disp.print("do leitor...  ");                        //Imprime mensagem

    rfid_func();   //chama função para identificação de tags RFID

  

  
  
} //end loop


// === Funções Auxiliares ===
void rfid_func()                            //Função para identificação das tags RFID
{
      // -- Verifica novas tags --
      if ( ! mfrc522.PICC_IsNewCardPresent()) 
      {
        return;
      }
      // Seleciona um dos cartões
      if ( ! mfrc522.PICC_ReadCardSerial()) 
      {
        return;
      }
      
  // Mostra UID na serial
      Serial.print("UID da tag :");
      String conteudo= "";
      byte letra;
      for (byte i = 0; i < mfrc522.uid.size; i++) 
      {
         Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
         Serial.print(mfrc522.uid.uidByte[i], HEX);
         conteudo.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
         conteudo.concat(String(mfrc522.uid.uidByte[i], HEX));
      }
      Serial.println();
      Serial.print("Mensagem : ");
      conteudo.toUpperCase();



      if (conteudo.substring(1) == "86 D0 17 7E") //tag Chaveiro o
      {
        
        
        // Aciona  buzzer
         
        digitalWrite(buzzer,    HIGH);
        delay(300);
       
        disp.setCursor(0,0);                                 //Posiciona cursor na coluna 1, linha 1
        disp.print("Nome:           ");                      //Imprime mensagem
        disp.setCursor(0,1);                                 //Posiciona cursor na coluna 1, linha 2
        disp.print("Usuario1 ChavUID");                      //Imprime mensagem
        
        digitalWrite(buzzer,     LOW);
        delay(1500);

        disp.setCursor(0,1);                                 //Posiciona cursor na coluna 1, linha 2
        disp.print("                ");                      //Imprime mensagem 

         
         
      }
     
      if (conteudo.substring(1) == "54 DB 03 C5") //tag cartao
      {
        
        
        // Aciona   buzzer
        
        digitalWrite(buzzer,    HIGH);
        delay(300);
       
        disp.setCursor(0,0);                                 //Posiciona cursor na coluna 1, linha 1
        disp.print("Nome:           ");                      //Imprime mensagem
        disp.setCursor(0,1);                                 //Posiciona cursor na coluna 1, linha 2
        disp.print("Usuario2 CartUID");                      //Imprime mensagem
        
        digitalWrite(buzzer,     LOW);
        delay(1500);

        disp.setCursor(0,1);                                 //Posiciona cursor na coluna 1, linha 2
        disp.print("                ");                      //Imprime mensagem 
        
      } //end if outras tags
  
  
  
} //end rfid_func

 

void systemBoot()
{
// --- Boot do Sistema --
   disp.setCursor(0,0);                                 //Posiciona cursor na coluna 1, linha 1
   disp.print("Identificador   ");                      //Imprime mensagem
   disp.setCursor(0,1);                                 //Posiciona cursor na coluna 1, linha 2
   disp.print("de tags RFID    ");                      //Imprime mensagem
   delay(2500);
   disp.setCursor(0,0);                                 //Posiciona cursor na coluna 1, linha 1
   disp.print("WR Kits System  ");                      //Imprime mensagem
   disp.setCursor(0,1);                                 //Posiciona cursor na coluna 1, linha 2
   disp.print("v 001 11/2017   ");                      //Imprime mensagem
   delay(2500);


} //end systemBoot











 
 
