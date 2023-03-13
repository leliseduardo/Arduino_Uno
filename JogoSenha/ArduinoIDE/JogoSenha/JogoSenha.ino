/*

          Este programa foi copiado da aula, pois se trata de uma aplicação do circuito com teclado, assim, farei ele quando tiver tempo. Ainda sim, 
     copiei o código pois ele apresenta uma rotina de sorteio de número interessante, que é novidade.
          Neste código, a leitura do teclado pela função store faz com que o teclado leia mais de um número por clique, as vezes. Portanto, este código 
     precisa ser melhorado. 
   
*/


// --- Bibliotecas Auxiliares ---
#include <LiquidCrystal.h>            //Biblioteca para o display LCD


// --- Mapeamento de Hardware ---
#define  col_1   A1                   //coluna 1 controlada pelo pino analógico 1 (será usado como digital)
#define  col_2   2                    //coluna 2 controlada pelo pino digital 2
#define  col_3   3                    //coluna 3 controlada pelo pino digital 3
#define  row_A   4                    //linha A  controlada pelo pino digital 4
#define  row_B   5                    //linha B  controlada pelo pino digital 5
#define  row_C   6                    //linha C  controlada pelo pino digital 6
#define  row_D   7                    //linha D  controlada pelo pino digital 7

#define  buzzer  A0                   //Saída para controle do buzzer
#define  l_Red   A4                   //Saída para LED vermelho


// --- Protótipo das Funções Auxiliares ---
void store(char value);                            //Função para armazenar o número digitado no teclado matricial
void numero();                                     //Função para imprimir o número digitado na tela do LCD
void help(int shot, int password);                 //Função que compara o número do usuário com a senha real e dá dicas ao jogador
void error();                                      //Função que indica que a senha está errada


// --- Variáveis Globais ---
char control = 0x01;                  //variável de controle de teclado
char counter = 0x00;                  //variável auxiliar de contagem
char aux_store = 0x00;                //variável para controle de armazenamento de dígitos
char bip = 0x00;                      //variável auxiliar para limitar os bips

unsigned long shot_user;              //armazena o resultado total
int tentativa = 0x01;                 //numero da tentativa de acerto
int senha;                            //armazena o valor da senha


// -- Variáveis para armazenar a senha digitada pelo usuário --
short  number1 = 0x00, number2 = 0x00, number3 = 0x00;


// -- Variáveis de indicação --
boolean right = 0x00, sort = 0x00;
 

// --- Hardware do LCD ---
LiquidCrystal disp(13,  //RS no digital 13
                   12,  //EN no digital 12
                   11,  //D4 no digital 11
                   10,  //D5 no digital 10
                    9,  //D6 no digital  9
                    8); //D7 no digital  8
                    

// --- Rotina de Interrupção ---
ISR(TIMER2_OVF_vect)
{
    TCNT2=100;          // Reinicializa o registrador do Timer2
    counter++;          // incrementa counter
    
    if(counter == 0x06) // counter igual a D'6'?
    {                   // sim...
    
       counter = 0x00;  //reinicia counter
       
           
// -- Varredura do Teclado Matricial --

      if(digitalRead(col_1) && control == 0x01)        //Coluna 1 em nível high? Control igual 1?
      {                                   //Sim...
         control = 0x02;                  //control igual a 2
         digitalWrite(col_1,  LOW);       //apenas coluna 1 em nível baixo
         digitalWrite(col_2, HIGH);
         digitalWrite(col_3, HIGH);
      
      // -- Testa qual tecla foi pressionada e armazena o valor --
         if     (!digitalRead(row_A))  store(1);
         else if(!digitalRead(row_B))  store(4);
         else if(!digitalRead(row_C))  store(7);
         else if(!digitalRead(row_D))  store(11);
      
      }
      else if(digitalRead(col_2) && control == 0x02)   //Coluna 2 em nível high? Control igual 2?
      {                                   //Sim...
         control = 0x03;                  //control igual a 3
         digitalWrite(col_1, HIGH);
         digitalWrite(col_2,  LOW);       //apenas coluna 2 em nível baixo
         digitalWrite(col_3, HIGH);
         
      // -- Testa qual tecla foi pressionada e armazena o valor --
         if     (!digitalRead(row_A))  store(2);
         else if(!digitalRead(row_B))  store(5);
         else if(!digitalRead(row_C))  store(8);
         else if(!digitalRead(row_D))  store(0);

      }
      else if(digitalRead(col_3) && control == 0x03)   //Coluna 3 em nível high? Control igual 3?
      {                                   //Sim...
         control = 0x01;                  //control igual a 1     
         digitalWrite(col_1, HIGH);       //
         digitalWrite(col_2, HIGH);
         digitalWrite(col_3,  LOW);       //apenas coluna 3 em nível baixo
         
      // -- Testa qual tecla foi pressionada e armazena o valor --
         if     (!digitalRead(row_A))  store(3);
         else if(!digitalRead(row_B))  store(6);
         else if(!digitalRead(row_C))  store(9);
         else if(!digitalRead(row_D))  store(12);

      }
       
    } //end if counter
    
} //end ISR


// --- Configurações Iniciais ---
void setup()
{
     disp.begin(16,2);                                      //Inicializa LCD 16 x 2
  
     for(char i=2;i<4;i++) pinMode(i, OUTPUT);              //Saídas para varredura das colunas 2 e 3
     for(char j=4;j<8;j++) pinMode(j,  INPUT);              //Entradas para as linhas
     
     pinMode(col_1,   OUTPUT);                              //Saída para varredura da coluna 1
     pinMode(buzzer , OUTPUT);                              //Saída para o buzzer
     pinMode(l_Red,   OUTPUT);                              //Saída para o LED vermelho de indicação
     
     
     digitalWrite(col_1, HIGH);                             //Inicializa coluna 1 em HIGH
     digitalWrite(col_2, HIGH);                             //Inicializa coluna 2 em HIGH
     digitalWrite(col_3, HIGH);                             //Inicializa colune 3 em HIGH
     
     digitalWrite(buzzer, LOW);                             //Buzzer desligado
     digitalWrite(l_Red,  LOW);                             //LED vermelho desligado
     
     
     
     TCCR2A = 0x00;   //Timer operando em modo normal
     TCCR2B = 0x07;   //Prescaler 1:1024
     TCNT2  = 100;    //10 ms overflow again
     TIMSK2 = 0x01;   //Habilita interrupção do Timer2
     
     // -- Mensagens iniciais --
     disp.clear();
     delay(200);
     disp.setCursor(0,0);
     disp.print(" Jogo da Senha ");
     disp.setCursor(1,1);
     disp.print("by WR Kits");
     delay(3000);
     disp.setCursor(0,0);
     disp.print("Acerte o numero ");
     disp.setCursor(1,1);
     disp.print(" entre 0 e 999  ");
     delay(3000);
     disp.clear();
     delay(200);
     
 
} //end setup
 

// --- Loop Infinito ---
void loop()
{
    if(!sort)                  //rand igual a zero?
    {
       randomSeed(millis() * analogRead(5));   //gera uma semente aleatória a partir da função millis
                                               //e da leitura analógica no pino A5 (ruído)
                                               
       senha = random(999);    //sorteia um número entre 0 e 999 e salva em senha
       
       sort = 0x01;            //invalida este laço para não atualizar a senha
       
    } //end if !sort
  
  
     numero();                 //Chama função para mostrar números digitados
     
     
    if(right)                              //right igual a 1?
    {
       help(shot_user, senha);             //chama função de ajuda para comparar a senha com o chute do jogador
       
       delay(2000);                        //aguarda 2 segundos após avaliação 
                  
       disp.clear();                       //limpa display
             
       delay(100);                         //aguarda 100 mili segundos
             
       right = 0x00;                       //right volta a ser zero
       
       bip = 0x00;                         //bip volta a ser zero
       
     } //end if right
      
     
} //end loop



   // Estouro = Timer2_cont x prescaler x ciclo de máquina
   
   // Ciclo de máquina = 1/Fosc = 1/16E6 = 62,5ns = 62,5E-9s
   
   // Estouro = (256 - 100) x 1024 x 62,5E-9 = 9,98ms 

   // Varredura = Estouro x Counter = 9,98ms x 10 = 99,8ms
   
   
   
// --- Funções Auxiliares (Desenvolvimento) ---


void store(char value)                   //Função para armazenar o valor digitado no teclado
{
   char i;                                //variável de iterações
        
   TIMSK2 = 0x00;                         //Desabilita interrupção do Timer2
          
    
     aux_store++;                         //Incrementa aux_store
   
     digitalWrite(buzzer, HIGH);          //Bip breve no buzzer ao digitar no teclado
     delay(500);
     digitalWrite(buzzer, LOW);
     
      
         switch(aux_store)                      //controle do aux_store
         {
            case 0x01: number1 = value; break;  //caso 1, armazena valor em number1
            case 0x02: number2 = value; break;  //caso 2, armazena valor em number2
            case 0x03: number3 = value; break;  //caso 3, armazena valor em number3
                     
         } //end switch aux_store
         
         if(aux_store > 0x03)        //Se aux_store for maior que 4...
         {
           aux_store = 0x00;         //...volta a valer zero
           
           
           
           tentativa++;                                         //Incrementa tentativa
           
           right = 0x01;
           
           shot_user = (number1*100) + (number2*10) + number3;
           
           delay(100);
           
           
           
         } //end if aux_store
         
    
   
   TIMSK2 = 0x01;   //Habilita interrupção do Timer2
   
} //end store


void numero()                                           //Função para imprimir o número digitado na tela do LCD
{


  
  // -- String para exibir números no display --
   String password = String(number1) + String(number2) + String(number3);
   
   
   disp.setCursor(0,0);                                 //Posiciona cursor na coluna 1, linha 1
   disp.print("Tentativa: ");                           //Imprime mensagem
   disp.print(tentativa);
   
     
   disp.setCursor(5,1);                                 //Posiciona cursor na coluna 6, linha 2
   disp.print(password);                                //mostra senha digitada
   
   
    
} //end numero


void help(int shot, int password)         //Função que compara o número do usuário com a senha real e dá dicas ao jogador
{
    if(shot > password)                   //chute do jogador maior que a senha?
    {                                     //Sim...
       disp.setCursor(0,0);
       disp.print("A senha e menor");     //indica para o usuário
       disp.setCursor(1,1);               //que o número da senha é menor
       disp.print("que  ");
       disp.print(shot);
       error();                       //chama função que indica o erro
       
    } //end if
    
    else                                  //Senão...
    {
       if(shot < password)                //chute do jogador menor que a senha?
       {                                  //Sim...
           disp.setCursor(0,0);
           disp.print("A senha e maior"); //indica para o usuário
           disp.setCursor(1,1);           //que o número da senha é maior
           disp.print("que  ");
           disp.print(shot);
           error();                       //chama função que indica o erro
       
       } //end if aninhado
       
       else                               //Senão...
       {                                  //É porque são iguais e o jogador acertou!
           disp.clear();
           delay(100);
           disp.setCursor(0,0);
           disp.print(" Parabens!");
           disp.setCursor(1,1);
           disp.print(" Voce acertou!");
           
           
           
            while(bip < 0x03)                                   //Enquanto bip menor que 3...
            {
                 bip++;                                         //Incrementa bip
                 digitalWrite(buzzer,HIGH);                     //Aciona buzzer por
                 delay(500);                                    // 500 ms
                 digitalWrite(buzzer, LOW);                     //Desliga buzzer por
                 delay(200);                                    // 200 ms
            } //end while
            
            
           disp.setCursor(0,0);
           disp.print("Na tentativa ");
           disp.print(tentativa);
            
           delay(2000);
           
           tentativa = 0x00;               //Reinicia tentativa
           
           sort = 0x00;                    //Zera sort para novo sorteio
           
           number3 = 0x00;                 //Reinicia os números exibidos no display
           number2 = 0x00;
           number1 = 0x00;
            
       } //end else aninhado
    
    
    } //end else
    

} //end help


void error()
{
   while(bip < 0x02)                                   //Enquanto bip menor que 4...
    {
         bip++;                                         //Incrementa bip
         digitalWrite(buzzer,HIGH);                     //Aciona buzzer
         digitalWrite(l_Red, HIGH);                     //e desliga LED vermelho
         delay(800);                                    //por 1 segundo
         digitalWrite(buzzer, LOW);                     //Desliga buzzer
         digitalWrite(l_Red,  LOW);                     //e liga LED vermelho
         delay(300);                                    //por meio segundo
    } //end while

} //end error
