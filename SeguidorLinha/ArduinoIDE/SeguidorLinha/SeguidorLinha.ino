/*

            Este código é copiado do professor e tem a função de demonstrar o uso de um Shield para um robô seguidor de linha.  

*/


// ========================================================================================================
// --- Mapeamento de Hardware ---
#define    sens_4    6                                  //sensor de linha 4
#define    sens_2    7                                  //sensor de linha 2
#define    m_inv1    8                                  //bit de inversão do motor 1
#define    m_pwm1    9                                  //bit de controle pwm do motor 1
#define    m_inv2   10                                  //bit de inversão do motor 2
#define    m_pwm2   11                                  //bit de controle pwm do motor 2
 

// ========================================================================================================
// --- Configurações Iniciais ---
void setup() 
{

    pinMode(sens_2,  INPUT);                            //entrada para o sensor de linha 2
    pinMode(sens_4,  INPUT);                            //entrada para o sensor de linha 4
    pinMode(m_inv1, OUTPUT);                            //saída para controle de inversão do motor 1
    pinMode(m_pwm1, OUTPUT);                            //saída para controle pwm do motor 1
    pinMode(m_inv2, OUTPUT);                            //saída para controle de inversão do motor 2
    pinMode(m_pwm1, OUTPUT);                            //saída para controle pwm do motor 2

    digitalWrite(m_inv1,  LOW);                         //Robô move-se para frente
    digitalWrite(m_inv2,  LOW);                         //
    analogWrite(m_pwm1, 0x00);                          //motor 1 inicia parado
    analogWrite(m_pwm2, 0x00);                          //motor 2 inicia parado



} //end setup


// ========================================================================================================
// --- Loop Infinito ---
void loop() 
{

  if(!digitalRead(sens_2))                              //sensor esquerdo está na linha preta?
  {                                                     //sim
    analogWrite(m_pwm1, 0x80);                          //aumenta velocidade do motor da direita
    analogWrite(m_pwm2, 0x00);                          //para motor da esquerda
    
  } //end if sens_2

 
  if(!digitalRead(sens_4))                              //sensor direito está na linha preta?
  {                                                     //sim
    analogWrite(m_pwm1, 0x00);                          //para motor da direita
    analogWrite(m_pwm2, 0x80);                          //aumenta velocidade do motor da esquerda
    
  } //end if sens_1


  //Se nenhum sensor estiver na linha preta, move robô para frente
  else
  {
    analogWrite(m_pwm1, 0x75);
    analogWrite(m_pwm2, 0x75);  
    
  } //end else
  
    
} //end loop
