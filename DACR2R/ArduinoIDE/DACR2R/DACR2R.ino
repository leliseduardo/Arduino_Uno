/* ==========================================================================================

        Este código é copiado do professor e tem a função de demonstrar o funcionamente de um DAC R2R.

  DAC com Rede R2R

 
  Autor: Eng. Wagner Rambo 
  Data:  Agosto de 2019

  https://wrkits.com.br/  

  Curso WR Kits Arduino para Iniciantes com certificado:
  https://go.hotmart.com/W13291812W 

========================================================================================== */


unsigned char val = 0;
boolean flag = 0;

// ==========================================================================================
// --- Configurações Iniciais ---
void setup() 
{
  for(int i=8;i<13;i++) pinMode(i, OUTPUT);
  Serial.begin(9600);
  PORTB = 0x00;
 

} //end setup


// ==========================================================================================
// --- Loop Infinito ---
void loop() 
{
  
  if(val == 31) flag = 1;

  if(flag) 
  {
    val--;
    if(!val) flag = 0;
  }
  
  
  else val++;
  
  PORTB = val;
  delay(5);

  Serial.println(val);

 
} //end loop
