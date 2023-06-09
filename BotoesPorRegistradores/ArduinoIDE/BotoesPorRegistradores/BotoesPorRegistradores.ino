/* ============================================================

   Este código foi feito pelo professor e demonstra o uso de vários botões configurados a partir dos registradores do ATMega328P.
   
   Leitura Profissional de Teclado

   Compilador: Arduino IDE 1.8.4

   MCU: Atmega328p
   Autor: Eng. Wagner Rambo
   Data:  Abril de 2020


============================================================ */


// ============================================================
// --- Mapeamento de Hardware ---
#define   bt1   (1<<PD4)
#define   bt2   (1<<PD5)
#define   bt3   (1<<PD6)
#define   bt4   (1<<PD7)
#define   led1  (1<<PB0)
#define   led2  (1<<PB1)


// ============================================================
// --- Protótipo das Funções ---
void readKeyboard();


// ============================================================
// --- Variáveis Globais ---



// ============================================================
// --- Programa Principal ---
void setup()
{
   DDRD  &=  ~bt1;     //configura entrada para o botão 1
   DDRD  &=  ~bt2;     //configura entrada para o botão 2
   DDRD  &=  ~bt3;     //configura entrada para o botão 3
   DDRD  &=  ~bt4;     //configura entrada para o botão 4
   
   PORTD |=   bt1;     //habilita o pull-up interno para o botão 1
   PORTD |=   bt2;     //habilita o pull-up interno para o botão 2
   PORTD |=   bt3;     //habilita o pull-up interno para o botão 3
   PORTD |=   bt4;     //habilita o pull-up interno para o botão 4
   
   DDRB  |=   led1;    //configura saída para o led1
   DDRB  |=   led2;    //configura saída para o led2


   while(1)
   {
      readKeyboard();
    
 
   } //end while
    
} //end setup


// ============================================================
// --- Desenvolvimento das Funções ---
void readKeyboard()
{

static boolean  bt1_f = 0x00,
                bt2_f = 0x00,
                bt3_f = 0x00,
                bt4_f = 0x00;

  
   if(!(PIND&bt1)) bt1_f = 0x01;
   if(!(PIND&bt2)) bt2_f = 0x01;
   if(!(PIND&bt3)) bt3_f = 0x01;
   if(!(PIND&bt4)) bt4_f = 0x01;

   if((PIND&bt1) && bt1_f)
   {
      bt1_f = 0x00;

      PORTB |= led1;
        
   } //end if bt1  

   if((PIND&bt2) && bt2_f)
   {
      bt2_f = 0x00;

      PORTB &= ~led1;
        
   } //end if bt2  

   if((PIND&bt3) && bt3_f)
   {
      bt3_f = 0x00;

      PORTB |= led2;
        
   } //end if bt3 

   if((PIND&bt4) && bt4_f)
   {
      bt4_f = 0x00;

      PORTB &= ~led2;
        
   } //end if bt4
  
  
} //end readKeyboard
 





























// ============================================================
// --- FINAL DO PROGRAMA ---
