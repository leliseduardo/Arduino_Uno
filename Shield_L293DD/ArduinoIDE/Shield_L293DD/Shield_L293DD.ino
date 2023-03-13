/* 

              Este código é copiado do professor. Este código faz a utilização simples do shield L293D, girando o motor hora num sentido, hora no outro.

*/


// ========================================================================================================
// --- Mapeamento de Hardware ---
#define    pwmB    6
#define    dirB    7
#define    dirA    8
#define    pwmA    9


// ========================================================================================================
// --- Configurações Iniciais ---
void setup()
{
     pinMode(pwmB, OUTPUT);
     pinMode(dirB, OUTPUT);
     pinMode(dirA, OUTPUT);
     pinMode(pwmA, OUTPUT);

     digitalWrite(pwmB,  LOW);
     digitalWrite(dirB,  LOW);
     digitalWrite(dirA,  LOW);
     digitalWrite(pwmA,  LOW);
  
  
} //end setup

  
void loop()
{

     digitalWrite(pwmB,  HIGH);
     digitalWrite(dirB,   LOW);
     digitalWrite(dirA,   LOW);
     digitalWrite(pwmA,  HIGH);
     delay(2535);

     digitalWrite(pwmB,  HIGH);
     digitalWrite(dirB,  HIGH);
     digitalWrite(dirA,  HIGH);
     digitalWrite(pwmA,  HIGH);
     delay(2535);
     
  
  
  
} //end loop
