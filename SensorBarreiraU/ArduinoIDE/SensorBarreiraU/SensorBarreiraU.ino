/* 

              Este código é copiado do professor e tem a função de demontrar o uso de um sensor foto interruptor, isto é, um sensor de barreira em formato de U. 

*/


// ========================================================================================================
// --- Bibliotecas Auxiliares ---
#include <Wire.h>
#include <LiquidCrystal_I2C.h>


// ========================================================================================================
// --- Variáveis Globais ---
int card  = 0,
    timer = 0;

boolean ctrl = 0;


// ========================================================================================================
// --- Declaração de Objetos ---
LiquidCrystal_I2C lcd(0x3F,2,1,0,4,5,6,7,3, POSITIVE);


// ========================================================================================================
// --- Interrupção Externa ---
void func()
{
    card += 1;
    ctrl  = 1;  
  
} //end func


// ========================================================================================================
// --- Configurações Iniciais ---
void setup() 
{

  Serial.begin(115200);

  lcd.begin (16,2);
  
  pinMode(2, INPUT);

  attachInterrupt(0, func, FALLING);

  Serial.println("Passe o cartão no leitor...");

  lcd.setBacklight(HIGH);
  lcd.setCursor(0,0);
  lcd.print("Passe o cartao");
  lcd.setCursor(0,1);
  lcd.print("no leitor...");
   
  
 

} //end setup


// ========================================================================================================
// --- Loop Infinito ---
void loop() 
{

   if(ctrl) timer++;
   delay(1);
   
   if(timer == 741)
   {
  
      Serial.print(" Card ID >>> ");
      Serial.println(card);

      lcd.setCursor(13,1);
      lcd.print(card);
 
      ctrl  = 0;
      timer = 0;
      card  = 0;
   
   }

   





} //end loop
