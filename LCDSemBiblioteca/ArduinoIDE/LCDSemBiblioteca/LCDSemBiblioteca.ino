/* =====================================================================================

   Este código é copiado do professor e demonstra como inicializar o display LCD sem biblioteca. Ainda, o código escreve algumas letras no display.
   
   Aula 267: Display LCD modo 8 bits sem biblioteca
   
   Autor: Eng. Wagner Rambo  
   Data: Agosto de 2020
    
   
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

   // ENVIA CARACTERE W (48h)
   digitalWrite(db0,  LOW); // H ascii table
   digitalWrite(db1,  LOW);
   digitalWrite(db2,  LOW);
   digitalWrite(db3, HIGH);
   digitalWrite(db4,  LOW);
   digitalWrite(db5,  LOW);
   digitalWrite(db6, HIGH);
   digitalWrite(db7,  LOW);
   digitalWrite(rs,  HIGH);
   delay(2);
   digitalWrite(en,  HIGH);
   delay(2);
   digitalWrite(en,   LOW);
   delay(2); 

   // ENVIA CARACTERE R (52h)
   digitalWrite(db0,  LOW); // R
   digitalWrite(db1, HIGH);
   digitalWrite(db2,  LOW);
   digitalWrite(db3,  LOW);
   digitalWrite(db4, HIGH);
   digitalWrite(db5,  LOW);
   digitalWrite(db6, HIGH);
   digitalWrite(db7,  LOW);
   digitalWrite(rs,  HIGH);
   delay(2);
   digitalWrite(en,  HIGH);
   delay(2);
   digitalWrite(en,   LOW);
   delay(2); 
    
} //end setup
 

// --- Loop Infinito ---
void loop()
{
  
  
     
} //end loop
 

// =====================================================================================
// --- Final do Programa ---
