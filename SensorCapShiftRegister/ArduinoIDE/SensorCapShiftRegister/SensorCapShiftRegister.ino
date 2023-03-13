/*

            Este código é copiado do professor e demonstra o uso de um sensor capacitivo junto a um shift register. O sensor capacitivo, que funciona como um botão digital,
      a cada toque recebido aciona uma das saídas do shift register, tornando possível o acionamento de várias cargas dessa forma.

*/

// ========================================================================================================
// --- Mapeamento de Hardware ---
#define    cap      4
#define    clk      8
#define    latch    9
#define    data    10


// ========================================================================================================
// --- Variáveis Globais --- 
byte   num = 0x01;


// ========================================================================================================
// --- Configurações Iniciais ---
void setup()
{
   pinMode(cap,    INPUT);
   pinMode(clk,   OUTPUT);
   pinMode(data,  OUTPUT);
   pinMode(latch, OUTPUT); 


   shiftOut(data, clk, LSBFIRST, num);  
   digitalWrite(latch,  LOW);
   digitalWrite(latch, HIGH);
   digitalWrite(latch,  LOW);

} //end setup


// ========================================================================================================
// --- Loop Infinito ---
void loop()
{
  
  
  if(digitalRead(cap))
  {
      shiftOut(data, clk, LSBFIRST, num);  
      digitalWrite(latch,  LOW);
      digitalWrite(latch, HIGH);
      digitalWrite(latch,  LOW);
    
      num <<= 1; // num = num << 1;
      if(!num) num = 0x01;
     
      delay(250);
  }

 
} //end loop

 
