/* 

            Este código é copiado do professor e tem a função de demonstrar o uso do sensor flexível para controlar o ângulo de posicionamento de um servo.

*/


// ========================================================================================================
// --- Bibliotecas Auxiliares ---
#include <Servo.h>


// ========================================================================================================
// --- Mapeamento de Hardware ---
#define    sens1    A0
#define    sv1       6


// ========================================================================================================
// --- Declaração de Objetos ---
Servo    servo1;


// ========================================================================================================
// --- Variáveis Globais ---
int     angle = 0;


// ========================================================================================================
// --- Configurações Iniciais ---
void setup() 
{
  
  Serial.begin(115200);
  pinMode(sens1, INPUT);
  pinMode(sv1,  OUTPUT);

  servo1.attach(sv1);

  servo1.write(90);

} //end setup


// ========================================================================================================
// --- Loop Infinito ---
void loop() 
{
  angle = map(analogRead(sens1), 640, 810, 20, 160);
  
  servo1.write(angle);

} //end loop
