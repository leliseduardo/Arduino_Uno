/* 

            Este código é copiado do professor e demonstra a utilização de um sensor de índice UV. Este sensor, através de um sinal analógico, demonstra qual é a incidência
     de raios ultravioleta, medição muito importante para dataloggers climáticos.

*/


// ========================================================================================================
// --- Mapeamento de Hardware ---
#define   analog   1
#define   gnd      14
#define   vcc      16


// ========================================================================================================
// --- Protótipo das Funções --- 
void measure_UV();


// ========================================================================================================
// --- Variáveis Globais --- 
int adc_value = 0,
    UV_index  = 0;


// ========================================================================================================
// --- Configurações Iniciais ---
void setup()
{
  Serial.begin(115200);
  
  pinMode(analog, INPUT);
  pinMode(vcc,   OUTPUT);
  pinMode(gnd,   OUTPUT);

  digitalWrite(vcc, HIGH);
  digitalWrite(gnd,  LOW);
 
} //end setup


// ========================================================================================================
// --- Loop Infinito ---
void loop()
{
  
  measure_UV();
  Serial.println(UV_index);


  delay(150);
  
} //end loop


// ========================================================================================================
// --- Desenvolvimento das Funções --- 
void measure_UV()
{
  
    adc_value = analogRead(analog);
    
    //Converte valor do ADC para tensão em mili Volts:
    int mV = (adc_value * (5.0 / 1023.0)) * 1000;
  
    
    //Compara valores da tabela de índice UV
    if(mV > 0 && mV < 50)           UV_index = 0;
   
    else if(mV > 50 && mV <= 227)   UV_index = 0;
    
    else if(mV > 227 && mV <= 318)  UV_index = 1;
    
    else if (mV > 318 && mV <= 408) UV_index = 2;
    
    else if (mV > 408 && mV <= 503) UV_index = 3;
    
    else if (mV > 503 && mV <= 606) UV_index = 4;
    
    else if (mV > 606 && mV <= 696) UV_index = 5;
    
    else if (mV > 696 && mV <= 795) UV_index = 6;
    
    else if (mV > 795 && mV <= 881) UV_index = 7;
    
    else if (mV > 881 && mV <= 976) UV_index = 8;
   
    else if (mV > 976 && mV <= 1079) UV_index = 9;
   
    else if (mV > 1079 && mV <= 1170) UV_index = 10;
    
    else if (mV > 1170) UV_index = 11;

 
} //end measure_UV
