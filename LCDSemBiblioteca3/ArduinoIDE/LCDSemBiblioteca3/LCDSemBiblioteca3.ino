/* =====================================================================================

   Esta aula é copiada do professor e tem a função de paerfeiçoar o envio de caracteres para o display.
   
   Aula 269: Display LCD modo 8 bits função para envio de caracteres
   
   Autor: Eng. Wagner Rambo  
   Data: Setembro de 2020
    
   
===================================================================================== */
 

// =====================================================================================
// --- Mapeamento de Hardware ---
#define  db7  7
#define  db6  6
#define  db5  5
#define  db4  4
#define  db3  11
#define  db2  10
#define  db1  9
#define  db0  8

#define  rs   13
#define  en   12


// =====================================================================================
// --- Protótipo das Funções ---
void send_char(char character);
void lcd_init();
void lcd_clear();
 

// =====================================================================================
// --- Configurações Iniciais ---
void setup()
{
   
   //configura saídas
   pinMode(db0, OUTPUT);
   pinMode(db1, OUTPUT);
   pinMode(db2, OUTPUT);
   pinMode(db3, OUTPUT);
   pinMode(db4, OUTPUT);
   pinMode(db5, OUTPUT);
   pinMode(db6, OUTPUT);
   pinMode(db7, OUTPUT);
   pinMode(rs,  OUTPUT);
   pinMode(en,  OUTPUT);

   //inicializa saídas
   digitalWrite(db0,  LOW);
   digitalWrite(db1,  LOW);
   digitalWrite(db2,  LOW);
   digitalWrite(db3,  LOW);
   digitalWrite(db4,  LOW);
   digitalWrite(db5,  LOW);
   digitalWrite(db6,  LOW);
   digitalWrite(db7,  LOW);
   digitalWrite(en,   LOW);
   digitalWrite(rs,   LOW);
   delay(2);

   lcd_init();
   
 
    
} //end setup

 
// =====================================================================================
// --- Loop Infinito ---
void loop()
{
    
     
} //end loop


// =====================================================================================
// --- Desenvolvimento das Funções ---


// =====================================================================================
// --- Função para Envio de Caracteres ---
void send_char(char character)
{
   
   digitalWrite(db7, (character >> 7) & 0x01);
   digitalWrite(db6, (character >> 6) & 0x01);
   digitalWrite(db5, (character >> 5) & 0x01);
   digitalWrite(db4, (character >> 4) & 0x01);
   digitalWrite(db3, (character >> 3) & 0x01);
   digitalWrite(db2, (character >> 2) & 0x01);
   digitalWrite(db1, (character >> 1) & 0x01);
   digitalWrite(db0, (character >> 0) & 0x01);
 
   digitalWrite(rs,  HIGH);
   delay(2);
   digitalWrite(en,  HIGH);
   delay(2);
   digitalWrite(en,   LOW);
   delay(2);   
  
} //end send_char


// =====================================================================================
// --- Função para Inicializar LCD ---
void lcd_init()
{
   // LIMPA LCD
   digitalWrite(db0, HIGH);
   digitalWrite(db1,  LOW);
   digitalWrite(db2,  LOW);
   digitalWrite(db3,  LOW);
   digitalWrite(db4,  LOW);
   digitalWrite(db5,  LOW);
   digitalWrite(db6,  LOW);
   digitalWrite(db7,  LOW);
   digitalWrite(en,   LOW);
   delay(2);
   digitalWrite(en,  HIGH);
   delay(2);
   digitalWrite(en,   LOW);
   delay(2);

   // MODO DE 8 BITS
   digitalWrite(db0,  LOW);
   digitalWrite(db1,  LOW);
   digitalWrite(db2,  LOW);
   digitalWrite(db3, HIGH);
   digitalWrite(db4, HIGH);
   digitalWrite(db5, HIGH);
   digitalWrite(db6,  LOW);
   digitalWrite(db7,  LOW);
   digitalWrite(en,   LOW);
   delay(2);
   digitalWrite(en,  HIGH);
   delay(2);
   digitalWrite(en,   LOW);
   delay(2);

   // LIGA LCD, LIGA CURSOR, DESLIGA BLINK
   digitalWrite(db0,  LOW);
   digitalWrite(db1, HIGH);
   digitalWrite(db2, HIGH);
   digitalWrite(db3, HIGH);
   digitalWrite(db4,  LOW);
   digitalWrite(db5,  LOW);
   digitalWrite(db6,  LOW);
   digitalWrite(db7,  LOW);
   digitalWrite(en,   LOW);
   delay(2);
   digitalWrite(en,  HIGH);
   delay(2);
   digitalWrite(en,   LOW);
   delay(2);

   // HABILITA INCREMENTO, DESLIGA SCROLL
   digitalWrite(db0,  LOW);
   digitalWrite(db1, HIGH);
   digitalWrite(db2, HIGH);
   digitalWrite(db3,  LOW);
   digitalWrite(db4,  LOW);
   digitalWrite(db5,  LOW);
   digitalWrite(db6,  LOW);
   digitalWrite(db7,  LOW);
   digitalWrite(en,   LOW);
   delay(2);
   digitalWrite(en,  HIGH);
   delay(2);
   digitalWrite(en,   LOW);
   delay(2);
  
} //end lcd_init



void lcd_clear()
{

   // LIMPA LCD
   digitalWrite(rs,   LOW);
   digitalWrite(db0, HIGH);
   digitalWrite(db1,  LOW);
   digitalWrite(db2,  LOW);
   digitalWrite(db3,  LOW);
   digitalWrite(db4,  LOW);
   digitalWrite(db5,  LOW);
   digitalWrite(db6,  LOW);
   digitalWrite(db7,  LOW);
   digitalWrite(en,   LOW);
   delay(2);
   digitalWrite(en,  HIGH);
   delay(2);
   digitalWrite(en,   LOW);
   delay(2);

} //end lcd_clear




// =====================================================================================
// --- Final do Programa ---
