/* ========================================================================================================


   Este  código é copiado do professor e tem a função de filtrar um sinal lido pela porta ADC, através do filtro de média média móvel.

   Filtro para ruído das entradas analógicas
    
   Autor: Eng. Wagner Rambo  Data: Dezembro de 2018
   
   www.wrkits.com.br | facebook.com/wrkits | youtube.com/user/canalwrkits 

     
======================================================================================================== */


// ========================================================================================================
// --- Constantes Auxiliares ---
#define     num    100         //número de iterações da média móvel


// ========================================================================================================
// --- Protótipo das Funções ---
long moving_average(int sig);


// ========================================================================================================
// --- Variáveis Globais ---
int values[num];              //vetor com num posições, armazena os valores para cálculo da média móvel

int adc_noise1,               //armazena a leitura sem filtro da entrada analógica
    adc_noise2;               //armazena a leitura filtrada da entrada analógica


// ========================================================================================================
// --- Configurações Iniciais ---
void setup() 
{
  
  Serial.begin(115200);      //inicia comunicação serial 115200 baud rate

} //end setup

 
// ========================================================================================================
// --- Loop Infinito ---
void loop() 
{
  adc_noise1 = analogRead(0);
  adc_noise2 = moving_average(adc_noise1);

  Serial.print(adc_noise1);
  Serial.print(" ");
  Serial.println(adc_noise2);

  delay(80);
    
  
} //end loop
 

// ========================================================================================================
// --- Desenvolvimento das Funções ---
long moving_average(int sig)
{
  int i;               //variável auxiliar para iterações
  long acc = 0;        //acumulador
  
  //Desloca o vetor completamente eliminando o valor mais antigo
  for(i = num; i > 0; i--) values[i] = values[i-1];    
  
  values[0] = sig;           //carrega o sinal no primeiro elemento do vetor
  
 // long sum = 0;            //Variável para somatório
  
  for(i = 0; i < num; i++) acc += values[i];
   
  
  return acc / num;         //Retorna a média móvel

} //end moving_average
