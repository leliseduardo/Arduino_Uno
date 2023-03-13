/*

          Este código é copiado do professor. A função do programa é fazer uma demonstração simples do uso da pastilha Peltier. Para isso, o sensor de temperatura LM35 é
    lido e, se atingir certa temperatura, liga a pastilha Peltier, que resfria o sistema.  

*/


// ========================================================================================================
// --- Mapeamento de Hardware ---
#define   peltier   13    //controle do relé de acionamento da pastilha Peltier
#define   temp      A0    //temperatura (LM35, sensor analógico linear)


// ========================================================================================================
// --- Variáveis Globais ---
void temperatura();  //função para medida e cálculo de temperatura


// ========================================================================================================
// --- Variáveis Globais ---
float tempC;   //armazena temperatura em Graus Celsius


// ========================================================================================================
// --- Configurações Iniciais ---
void setup()
{
   Serial.begin(9600);    //inicializa serial

   pinMode(peltier, OUTPUT); //saída para controle da pastilha
   pinMode(temp,     INPUT); //entrada para sensor de temperatura

   digitalWrite(peltier, LOW); //desliga relé de controle da pastilha
  
  
} //end setup


// ========================================================================================================
// --- Configurações Iniciais ---
void loop()
{
   temperatura();

   if(tempC > 40.0) digitalWrite(peltier, HIGH);

   else digitalWrite(peltier, LOW);
   
   delay(100);
   
  
  
} //end loop


void temperatura()
{
    tempC = analogRead(temp);
    tempC = (tempC*5.0)/1024.0;
    tempC = tempC*100.0;
    Serial.print("Temperatura = ");
    Serial.print(tempC);
    Serial.println(" C");
  
} //end temperatura
