/* 
  
          Este programa não foi feito por mim, foi criado pelo Wagner Rambo do WRKits. Ele tem o objetivo de ligar um motor a partir do módulo de 3 relés criado pelo professor.
     Não irei refazer este código pois é um projeto específico com o uso de um shield de relés específicos criado pelo professor. Porém, este projeto serve como base para a 
     criação de módulo relé para outros projetos que eu necessite. 
  
*/


// --- Mapeamento de Hardware ---
#define  rele01  5
#define  rele02  6
#define  rele03  7
#define  butt01  8
#define  butt02  9
#define  butt03 10
#define  butt04 11

// --- Protótipo da Função Auxiliar ---
void testButtons(); //testa botões e controle relés

 // --- Configurações Iniciais ---
void setup() 
{
   for(char i=5;  i<8; i++)  pinMode(i, OUTPUT);       //Saídas para os relés
   for(char j=8; j<12; j++)  pinMode(j, INPUT_PULLUP); //Entradas com pull-up para botões
   
   //Relés iniciam desligados
   digitalWrite(rele01, LOW);
   digitalWrite(rele02, LOW);
   digitalWrite(rele03, LOW);
   
} //end setup

// --- Loop Infinito ---
void loop() 
{
   
  testButtons();                   //Chama função para teste dos botões

} //end loop


// --- Desenvolvimento Função Auxiliar ---
void testButtons()                //Função para teste dos botões e controle dos relés
{
   if(!digitalRead(butt01))       //Botão 1 pressionado?
   {                              //Sim...
     delay(70);                   //Debouncing
     digitalWrite(rele01, HIGH);  //Liga relé 01
   }
   if(!digitalRead(butt02))       //Botão 2 pressionado?
   {                              //Sim...
     delay(70);                   //Debouncing
     digitalWrite(rele01, LOW);   //Desliga relé 01
   }
   if(!digitalRead(butt03))       //Botão 3 pressionado?
   {                              //Sim...
     delay(70);                   //Debouncing
     digitalWrite(rele02, HIGH);  //Liga relé 02
   }
   if(!digitalRead(butt04))       //Botão 4 pressionado?
   {                              //Sim...
     delay(70);                   //Debouncing
     digitalWrite(rele02, LOW);   //Desliga relé 02
   }

} //end testButtons
