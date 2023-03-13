/* ========================================================================================================

  Esta aula é copiada do professor e tem a função de demonstrar como se configura um teclado matricial para fazer o controle de uma tranca eletrônica. A tranca só irá abrir se a senha
  correta for digitada.

  Software para Teclado com Senha numérica

 
  Autor: Eng. Wagner Rambo 
  Data:  Dezembro de 2019

  https://wrkits.com.br/  

  Curso WR Kits Arduino para Iniciantes com certificado:
  https://go.hotmart.com/W13291812W 

======================================================================================================== */

 
// =============================================================================================================
// --- Mapeamento de Hardware ---
#define  col_1    6                    //coluna 1 do teclado
#define  col_2    5                    //coluna 2 do teclado
#define  col_3    4                    //coluna 3 do teclado
#define  col_4    3                    //coluna 4 do teclado
#define  row_A   10                    //linha  A do teclado
#define  row_B    9                    //linha  B do teclado
#define  row_C    8                    //linha  C do teclado
#define  row_D    7                    //linha  D do teclado

#define  buzz    11                    //buzzer
#define  relay    2                    //relé


// =============================================================================================================
// --- Protótipo das Funções ---
void readKeyboard();                  //Função para leitura do teclado
void store(char value);               //Função para armazenar o número digitado no teclado matricial
void numero();                        //Função para imprimir o número digitado na tela do LCD


// =============================================================================================================
// --- Variáveis Globais ---
int password[5] = {5,4,3,2,1};        //vetor para armazenamento de senha numérica

char control = 0x01;                  //variável de controle de teclado
char counter = 0x00;                  //variável auxiliar de contagem
int  number  = 0x00;                  //variável para armazenar o número pressionado no teclado

bool door    = 0x00,                  //variável de controle para abertura do dispositivo
     ndoor   = 0x00;                  //variável de controle para manter trancado


// =============================================================================================================
// --- Interrupção ---
ISR(TIMER2_OVF_vect)
{
    TCNT2=100;          // Reinicializa o registrador do Timer2
    counter++;          // incrementa counter
    
    if(counter == 0x05) // counter igual a D'5'?
    {                   // sim...
    
       counter = 0x00;  //reinicia counter
       
       readKeyboard();  //lê teclado     

            
    
    } //end if counter
}


// =============================================================================================================
// --- Configurações Iniciais ---
void setup()
{
     Serial.begin(9600);                                    //Inicializa comunicação serial 9600 baud rate

     pinMode(row_A, INPUT_PULLUP);                          //entrada para linha A
     pinMode(row_B, INPUT_PULLUP);                          //entrada para linha B
     pinMode(row_C, INPUT_PULLUP);                          //entrada para linha C
     pinMode(row_D, INPUT_PULLUP);                          //entrada para linha D
     pinMode(col_1, OUTPUT);                                //saída para coluna  1
     pinMode(col_2, OUTPUT);                                //saída para coluna  2
     pinMode(col_3, OUTPUT);                                //saída para coluna  3
     pinMode(col_4, OUTPUT);                                //saída para coluna  4
     pinMode(buzz,  OUTPUT);                                //saída para buzzer
     pinMode(relay, OUTPUT);                                //saída para relé
     pinMode(13,    OUTPUT);                                //saída para LED onboard
     
     digitalWrite(col_1, HIGH);                             //Inicializa coluna 1 em HIGH
     digitalWrite(col_2, HIGH);                             //Inicializa coluna 2 em HIGH
     digitalWrite(col_3, HIGH);                             //Inicializa coluna 3 em HIGH
     digitalWrite(col_4, HIGH);                             //Inicializa coluna 4 em HIGH
     digitalWrite(buzz,   LOW);                             //buzz inicia desligado
     digitalWrite(relay,  LOW);                             //relé inicia desligado
     digitalWrite(13,     LOW);                             //led onboard inicia desligado

     Serial.println("......................");              //mostra senha via serial ao iniciar...
     delay(400);
     Serial.print  ("O sistema tem a senha:  ");
     Serial.print  (password[0]);
     Serial.print  (password[1]);
     Serial.print  (password[2]);
     Serial.print  (password[3]);
     Serial.println(password[4]);
     delay(400);
     Serial.println("Sistema Liberado");
     
     TCCR2A = 0x00;                                         //Timer operando em modo normal
     TCCR2B = 0x07;                                         //Prescaler 1:1024
     TCNT2  = 100;                                          //10 ms overflow again
     TIMSK2 = 0x01;                                         //Habilita interrupção do Timer2
    
} //end setup


// =============================================================================================================
// --- Loop Infinito ---
void loop()
{
 
  if(door)                                                  //flag door verdadeira?
  {                                                         //sim
     door = 0;                                              //limpa flag
     digitalWrite(13,    HIGH);                             //led onboard liga
     digitalWrite(relay, HIGH);                             //ativa relé
     digitalWrite(buzz,  HIGH);                             //ativa buzzer
     delay(2300);                                           //por 2,3 segundos
     digitalWrite(relay, LOW);                              //desliga relé
     digitalWrite(buzz,  LOW);                              //desliga buzz
     digitalWrite(13,    LOW);                              //desliga led onboard
    
  } //end if door

  if(ndoor)                                                 //flag ndoor verdadeira?
  {                                                         //sim
    ndoor = 0;                                              //limpa flag
    
    for(int i=0; i<4; i++)                                  //repete 4 vezes
    {
      Serial.println("ERRRRROOOOU!");                       //mensagem de erro
      digitalWrite(buzz, HIGH);                             //aciona buzzer
      delay(100);                                           //por 100ms
      digitalWrite(buzz,  LOW);                             //desliga buzzer
      delay(200);                                           //por 200ms
    
    } //end for
    
  } //end if ndoor
    
} //end loop



   // Estouro = Timer2_cont x prescaler x ciclo de máquina
   
   // Ciclo de máquina = 1/Fosc = 1/16E6 = 62,5ns = 62,5E-9s
   
   // Estouro = (256 - 100) x 1024 x 62,5E-9 = 9,98ms 

   // Varredura = Estouro x Counter = 9,98ms x 5 = 49,9ms


// =============================================================================================================
// --- Desenvolvimento das Funções ---
void readKeyboard()                       //Função para leitura do teclado
{

   if(digitalRead(col_1) && control == 0x01)       //Coluna 1 em nível high? Control igual 1?
   {                                               //Sim...
         control = 0x02;                           //control igual a 2
         digitalWrite(col_1,  LOW);                //apenas coluna 1 em nível baixo
         digitalWrite(col_2, HIGH);
         digitalWrite(col_3, HIGH);
         digitalWrite(col_4, HIGH);
      
      // -- Testa qual tecla foi pressionada e armazena o valor --
         if     (!digitalRead(row_A))  store(1);
         else if(!digitalRead(row_B))  store(4);
         else if(!digitalRead(row_C))  store(7);
         else if(!digitalRead(row_D))  store(11);
      
   } //end if col_1
   
   else if(digitalRead(col_2) && control == 0x02)   //Coluna 2 em nível high? Control igual 2?
   {                                                //Sim...
         control = 0x03;                            //control igual a 3
         digitalWrite(col_1, HIGH);
         digitalWrite(col_2,  LOW);                 //apenas coluna 2 em nível baixo
         digitalWrite(col_3, HIGH);
         digitalWrite(col_4, HIGH);
         
      // -- Testa qual tecla foi pressionada e armazena o valor --
         if     (!digitalRead(row_A))  store(2);
         else if(!digitalRead(row_B))  store(5);
         else if(!digitalRead(row_C))  store(8);
         else if(!digitalRead(row_D))  store(0);

   } //end if col_2
   
   else if(digitalRead(col_3) && control == 0x03)   //Coluna 3 em nível high? Control igual 3?
   {                                                //Sim...
         control = 0x04;                            //control igual a 4     
         digitalWrite(col_1, HIGH);                 //
         digitalWrite(col_2, HIGH);
         digitalWrite(col_3,  LOW);                 //apenas coluna 3 em nível baixo
         digitalWrite(col_4, HIGH);
         
      // -- Testa qual tecla foi pressionada e armazena o valor --
         if     (!digitalRead(row_A))  store(3);
         else if(!digitalRead(row_B))  store(6);
         else if(!digitalRead(row_C))  store(9);
         else if(!digitalRead(row_D))  store(12);

   } //end if col_3

   else if(digitalRead(col_4) && control == 0x04)   //Coluna 3 em nível high? Control igual 4?
   {                                                //Sim...
         control = 0x01;                            //control igual a 1     
         digitalWrite(col_1, HIGH);                 //
         digitalWrite(col_2, HIGH);
         digitalWrite(col_3, HIGH);                 
         digitalWrite(col_4,  LOW);                 //apenas coluna 4 em nível baixo
         
      // -- Testa qual tecla foi pressionada e armazena o valor --
         if     (!digitalRead(row_A))  store(13);
         else if(!digitalRead(row_B))  store(14);
         else if(!digitalRead(row_C))  store(15);
         else if(!digitalRead(row_D))  store(16);

   } //end if col_4
  
  
} //end readKeyboard



void store(char value1)                   //Função para armazenar o valor digitado no teclado
{
   char i;                                //variável de iterações
        
   TIMSK2 = 0x00;                         //Desabilita interrupção do Timer2
   
   digitalWrite(buzz, HIGH);              //aciona buzzer
   delay(300);                            //por 300ms
   digitalWrite(buzz,  LOW);              //desliga buzzer
   delay(100);                            //por 100ms
  
        
   number = value1;                       //atualiza number

   numero();                              //chama função para processar número

   TIMSK2 = 0x01;                         //Habilita interrupção do Timer2
   
} //end store


void numero()                                           //Função para imprimir o número digitado
{
   static int passn = 0,                                //controle de digitações
              acc   = 0;                                //acumulador de números corretos

    
    Serial.print(passn);                                //imprime na serial número de digitações
    Serial.print("  |  ");
   if     (number == 11) Serial.println("*");
   else if(number == 12) Serial.println("#");
   else if(number == 13) Serial.println("A");
   else if(number == 14) Serial.println("B");
   else if(number == 15) Serial.println("C");
   else if(number == 16) Serial.println("D");
   else Serial.println(number);                         //Mostra número  

   if(number == password[passn]) acc += 1;              //se o número coincidir com a senha, incrementa acumulador

   Serial.print("acc = ");                              //imprime na serial valor do acumulador
   Serial.println(acc);
   
   passn += 1;                                          //incrementa número de digitações
   if(passn > 4)                                        //se maior que 4
   { 
      passn = 0;                                        //reinicia
      
      if(acc == 5)                                      //verificação de senha. Acumulador igual a 5?
      {                                                 //sim
        acc = 0;                                        //reinicia
        Serial.println("Senha correta");                //imprime mensagem de senha correta
        door = 1;                                       //seta flag door
      } //end if
      else                                              //senão
      {                                                 //acc diferente de 5
        acc = 0;                                        //reinicia
        Serial.println("Senha invalida");               //imprime mensagem de senha inválida
        ndoor = 1;                                      //seta flag ndoor
        
      } //end else
      
   } //end if passn
   
} //end numero


 
