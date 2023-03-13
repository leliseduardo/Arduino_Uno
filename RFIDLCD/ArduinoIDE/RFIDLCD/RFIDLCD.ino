/*

          Este código é copiado do professor e tem a função de destrancar uma fechadura a partir da tag RFID certa, e mostrar se a tag é aceita ou não
    através do display LCD. o Display estará mostrando que o acesso é via RFID e quando uma tag não autorizada se aproximar, o display mostra que está
    tag não está autorizada. O mesmo acontece para a tag autorizada, com o display mostrando que está é uma tag aceita.
          Enquanto a fechadura estiver aberta, nenhuma outra leitura será feita, e o led amarelo permance aceso. Quando a fechadura é fechada o led apaga
    e as leituras do RFID recomeçam. 
   
*/

// --- Bibliotecas Auxiliares ---
#include <SPI.h>
#include <MFRC522.h>                                    //Biblioteca para RFID
#include <LiquidCrystal.h>                              //Biblioteca para o display LCD


// --- Mapeamento de Hardware ---
#define   buzzer    16  //buzzer no A2
#define   door_lock 15  //atuador no A1
#define   door_sens 14  //sensor da porta no A0
#define   SS_PIN    10
#define   RST_PIN    9



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
 

// --- Variáveis Globais --- 
char st[20];



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


   disp.setCursor(0,0);                                 //Posiciona cursor na coluna 1, linha 1
   disp.print("Acesso por RFID ");                      //Imprime mensagem
   
  
} //end setup


// --- Loop Infinito ---
void loop() 
{

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



      if (conteudo.substring(1) == "86 D0 17 7E") //tag Chaveiro para liberar acesso
      {
        Serial.println("Acesso liberado!");
        Serial.println();
        
        // Aciona  buzzer
        disp.setCursor(0,1);                                 //Posiciona cursor na coluna 1, linha 2
        disp.print("Aberto  UID true");                      //Imprime mensagem 
        digitalWrite(buzzer,    HIGH);
        delay(800);
      
        disp.setCursor(0,1);                                 //Posiciona cursor na coluna 1, linha 2
        disp.print("                ");                      //Imprime mensagem 
        digitalWrite(buzzer,     LOW);
        delay(1200);

        //Mantém acesso liberado até acionar o sensor de porta
        while(digitalRead(door_sens)) digitalWrite(door_lock, HIGH);
        digitalWrite(door_lock, LOW);
         
      }
     
      if (conteudo.substring(1) != "86 D0 17 7E") //outras tags
      {
        Serial.println("Acesso Negado");
        Serial.println();
        
        // Aciona   buzzer
        disp.setCursor(0,1);                                 //Posiciona cursor na coluna 1, linha 2
        disp.print("Negado UID false");                      //Imprime mensagem 
        digitalWrite(buzzer,    HIGH);
        delay(800);

        disp.setCursor(0,1);                                 //Posiciona cursor na coluna 1, linha 2
        disp.print("                ");                      //Imprime mensagem 
        digitalWrite(buzzer,     LOW);
        delay(1200);
        
      }
  
  
  
} //end rfid_func















 
 
