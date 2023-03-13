/* 

          Este código é copiado do professor de demonstra o uso de um shift register 74HC595 a partir da função interna do Arduíno "shiftOut".

*/


// ========================================================================================================
// --- Mapeamento de Hardware ---
#define    clk      8
#define    latch    9
#define    data    10


// ========================================================================================================
// --- Variáveis Globais ---
byte   num = 0x00;


// ========================================================================================================
// --- Configurações Iniciais ---
void setup() 
{
   pinMode(clk,   OUTPUT);
   pinMode(data,  OUTPUT);
   pinMode(latch, OUTPUT);

    

} //end setup


// ========================================================================================================
// --- Loop Infinito ---
void loop() 
{

 
  num ^= 0b10000010; // num = num xor 10000010
   
  shiftOut(data, clk, LSBFIRST, num); // 1000010
  digitalWrite(latch,  LOW);
  digitalWrite(latch, HIGH);
  digitalWrite(latch,  LOW);
  delay(500);
 
 
 

} //end loop
