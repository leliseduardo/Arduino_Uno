/* 

          Este código é copiado do professor e tem a função de demonstrar o uso do sensor de força resistivo, que consiste basicamente num resistor que varia sua resistencia
     de acordo com a força aplicada sobre ele. Essa variação ocorre de forma inversamente proporcional, isto é, quanto maior a força aplicada no sensor de força, menor é a 
     sua resistência.

*/


// ========================================================================================================
// --- Bibliotecas Auxiliares ---
#include <Wire.h>
#include <LiquidCrystal_I2C.h>


// ========================================================================================================
// --- Declaração de Objetos ---
LiquidCrystal_I2C lcd(0x3F,2,1,0,4,5,6,7,3, POSITIVE);


// ========================================================================================================
// --- Constantes Auxiliares ---
const int FSR_PIN = A0; // Pin connected to FSR/resistor divider

// Measure the voltage at 5V and resistance of your 3.3k resistor, and enter
// their value's below:
const float VCC = 4.98; // Measured voltage of Ardunio 5V line
const float R_DIV = 3230.0; // Measured resistance of 3.3k resistor


// ========================================================================================================
// --- Configurações Iniciais ---
void setup() 
{
  Serial.begin(9600);
  pinMode(FSR_PIN, INPUT);

  lcd.begin (16,2);
  lcd.setBacklight(HIGH);
  lcd.setCursor(0,0);
  lcd.print("Force:"); 
  lcd.setCursor(15,1);
  lcd.print("g");
  
} //end setup


// ========================================================================================================
// --- Loop Infinito ---
void loop() 
{
  int fsrADC = analogRead(FSR_PIN);
  // If the FSR has no pressure, the resistance will be
  // near infinite. So the voltage should be near 0.
  if (fsrADC != 0) // If the analog reading is non-zero
  {
    // Use ADC reading to calculate voltage:
    float fsrV = fsrADC * VCC / 1023.0;
    // Use voltage and static resistor value to 
    // calculate FSR resistance:
    float fsrR = R_DIV * (VCC / fsrV - 1.0);
    Serial.println("Resistance: " + String(fsrR) + " ohms");
    // Guesstimate force based on slopes in figure 3 of
    // FSR datasheet:
    float force;
    float fsrG = 1.0 / fsrR; // Calculate conductance
    // Break parabolic curve down into two linear slopes:
    if (fsrR <= 600) 
      force = (fsrG - 0.00075) / 0.00000032639;
    else
      force =  fsrG / 0.000000642857;
    Serial.println("Force: " + String(force) + " g");
    Serial.println();

    lcd.setCursor(8,1);
    lcd.print(force);
   // if(force < 0.5) lcd.clear();

    delay(1500);
  }
 
/*
else
  {
    // No pressure detected
  }
  */
} //end loop
