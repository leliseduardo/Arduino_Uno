/*

          Este código foi copiado do professor e tem a função de demonstrar o uso de um sensor de obstáculos infravermelho, que foi utilizado como contador de voltas.

*/


// ========================================================================================================
// --- Mapeamento de Hardware ---
#define    motor     7
#define    sensor    2


// ========================================================================================================
// --- Variáveis Globais ---
int       count = 0;
boolean   flag  = 0;


// ========================================================================================================
// --- Configurações Iniciais ---
void setup() 
{
  
  Serial.begin(115200);
 
  pinMode(motor,  OUTPUT);
  pinMode(sensor, INPUT_PULLUP);

  digitalWrite(motor, HIGH);

} //end setup


// ========================================================================================================
// --- Loop Infinito ---
void loop() 
{
   Serial.print("  ");
   Serial.print(count);
   Serial.println(" voltas ");


   if(digitalRead(sensor)) flag = 1;

   if(!digitalRead(sensor) && flag)
   {
       flag = 0;
       count+=1;    
    
   } //end if


   if(count == 25)
   {
    
       count = 0;
       digitalWrite(motor, LOW);
       delay(3000); 
    
   }

   digitalWrite(motor, HIGH);

   

} //end loop
