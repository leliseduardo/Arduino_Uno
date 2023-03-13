/* 

            Este código é copiado do professor e tem a função de demonstrar o uso do termômetro a prova d'água DS18B20 e um display lcd I2C. No display é impresso o valor 
      de temperatura atual e os valores máximos e mínimos já lidos pelo sensor.

*/


// ========================================================================================================
// --- Bibliotecas Auxiliares ---
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>


// ========================================================================================================
// --- Mapeamento de Hardware ---
#define    ONE_WIRE_BUS     3          //sinal do sensor DS18B20


// ========================================================================================================
// --- Declaração de Objetos ---
OneWire oneWire(ONE_WIRE_BUS);        //objeto one_wire
DallasTemperature sensors(&oneWire);
DeviceAddress sensor1;
LiquidCrystal_I2C lcd(0x3F,2,1,0,4,5,6,7,3, POSITIVE);


// ========================================================================================================
// --- Protótipo das Funções ---
void mostra_endereco_sensor(DeviceAddress deviceAddress);  //Função para mostrar endereço do sensor


// ========================================================================================================
// --- Variáveis Globais ---
float tempMin = 999;   //armazena temperatura mínima
float tempMax = 0;     //armazena temperatura máxima
boolean mm = 0;

 


// ========================================================================================================
// --- Configurações Iniciais ---
void setup() 
{
  Serial.begin(9600);
  
  sensors.begin();
  lcd.begin (16,2);
  
  // Localiza e mostra enderecos dos sensores
  Serial.println("Localizando sensores DS18B20...");
  Serial.print("Foram encontrados ");
  Serial.print(sensors.getDeviceCount(), DEC);
  Serial.println(" sensores.");
  
  if (!sensors.getAddress(sensor1, 0)) 
     Serial.println("Sensores nao encontrados !"); 
     
  // Mostra o endereco do sensor encontrado no barramento
  Serial.print("Endereco sensor: ");
  mostra_endereco_sensor(sensor1);
  Serial.println();
  Serial.println();

  // Mostra texto fixo em LCD I2C
  lcd.setCursor(0,0);
  lcd.print("Temp=");

  lcd.setBacklight(LOW);
  
  

} //end setup


// ========================================================================================================
// --- Loop Infinito ---
void loop() 
{
  // Le a informacao do sensor
  sensors.requestTemperatures();
  float tempC = sensors.getTempC(sensor1);
  
  // Atualiza temperaturas minima e maxima
  if (tempC < tempMin)
  {
    tempMin = tempC;
  }
  if (tempC > tempMax)
  {
    tempMax = tempC;
  }
  
  // Mostra dados no serial monitor
  Serial.print("Temp C: ");
  Serial.print(tempC);
  Serial.print(" Min : ");
  Serial.print(tempMin);
  Serial.print(" Max : ");
  Serial.println(tempMax);

  // Mostra dados no Display LCD I2C
  lcd.setCursor(6,0);
  lcd.print(tempC);
  lcd.print(" C");

  if(mm)
  {
     lcd.setCursor(0,1);
     lcd.print("Max = ");
     lcd.print(tempMax);  
     lcd.print(" C");
  }

  else
  {
     lcd.setCursor(0,1);
     lcd.print("Min = ");
     lcd.print(tempMin);  
     lcd.print(" C");
  }
   

  mm = !mm; //complementa flag mm
  //atualiza leituras a cada 1,35 segundos
  delay(1350);
  
 
} //end loop


// ========================================================================================================
// --- Desenvolvimento das Funções ---


// ========================================================================================================
// --- Função para mostrar endereço do sensor de temperatura ---
void mostra_endereco_sensor(DeviceAddress deviceAddress)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    // Adiciona zeros se necessário
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
}


 
  
