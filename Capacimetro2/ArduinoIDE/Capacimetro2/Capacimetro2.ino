/* ========================================================================================================
 
   Este código foi copiado do professor e tem a função de implementar um capacímetro de leitura rápida. 

   Capacímetro com Arduino e 555
    
   Autor: Eng. Wagner Rambo  Data: Novembro de 2018
   
   www.wrkits.com.br | facebook.com/wrkits | youtube.com/user/canalwrkits 

     
======================================================================================================== */


// ========================================================================================================
// --- Bibliotecas Auxiliares ---
#include <LiquidCrystal.h>


// ========================================================================================================
// --- Mapeamento de Hardware ---
#define    freq_in   8


// ========================================================================================================
// --- Constantes Auxialires ---
#define    RA     9900.0
#define    RB   103300.0


// ========================================================================================================
// --- Declaração de Objetos ---
LiquidCrystal lcd(12, 11, 5, 4, 3, 7);


// ========================================================================================================
// --- Protótipo das Funções ---
float cap(float freq, float resA, float resB);


// ========================================================================================================
// --- Variáveis Globais ---
int     H_us = 0,            
        L_us = 0;  
                     
float   T_us = 0.0,       
        frequency = 0.0,       
        cap_val = 0.0,
        res_val = 0.0;


// ========================================================================================================
// --- Configurações Iniciais ---
void setup()
{
    pinMode(freq_in,INPUT);
    lcd.begin(16, 2);
    
} //end setup


// ========================================================================================================
// --- Loop Infinito ---
void loop()
{
// ========================================================= 

    H_us = pulseIn(freq_in, HIGH);                          //lê o tempo em HIGH e armazena em H_us
    L_us = pulseIn(freq_in,  LOW);                          //lê o tempo em  LOW e armazena em L_us
    
    T_us= float(H_us + L_us);                               //calcula período

    frequency=1.0E6/T_us;                                   //calcula frequência, multiplica-se por
                                                            // 1000000 pois o período está em micro segundo

    cap_val = cap(frequency, RA, RB);                       //passa os parâmetros para a função
    
    lcd.setCursor(0,1);                                     //posiciona cursor
    lcd.print(cap_val);                                     //imprime o valor da capacitância
    lcd.print(" nF ");                                      //imprime a unidade com sub múltiplo
    delay(741);                                             //taxa de atualização
    
} //end loop


// ========================================================================================================
// --- Desenvolvimento das Funções ---


// ========================================================================================================
// --- Função para cálculo de capacitância ---
//
//  Calcula capacitância a partir da frequência lida pelo Arduino e constantes RA e RB
//
//  A equação para o cálculo está no Datasheet do 555, no qual isolou-se o valor de C
//
float cap(float freq, float resA, float resB)
{

  float capacitor;                                          //variável local para armazenar capacitância
  
  lcd.clear();                                              //limpa LCD
  lcd.setCursor(0,0);                                       //posiciona cursor
  lcd.print("Capacitor:");                                  //imprime texto
  
  capacitor = 1.0E9*(1.44/((resA+2*resB)*freq));            //calcula capacitância
                                                            //multiplica-se o resultado por 1000000000
                                                            //para obter-se o valor em nF
                                                            
  return capacitor;                                         //retorna o resultado
  
} //end cap
