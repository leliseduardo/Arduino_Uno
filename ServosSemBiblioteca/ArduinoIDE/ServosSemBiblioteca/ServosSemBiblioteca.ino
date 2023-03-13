/* ==========================================================================================

            Este código é copiado do professor e tem a função de de controlar 3 servos sem o uso da biblioteca deste motor.


  Curso de Arduino WR Kits

  Controle de Vários Servos sem Biblioteca

 
  Autor: Eng. Wagner Rambo 
  Data:  Julho de 2019

  https://wrkits.com.br/  

  Curso WR Kits Arduino para Iniciantes com certificado:
  https://go.hotmart.com/W13291812W 

========================================================================================== */

 
// =============================================================================================================
// --- Mapeamento de Hardware ---
#define      servo1     11                                //servo1  
#define      servo2     12                                //servo2  
#define      servo3     13                                //servo3
 

// =============================================================================================================
// --- Variáveis Globais ---     
int            psv1     = 1500,
               psv2     = 1500, 
               psv3     = 1500,
               cT2      = 0x00;                                //contador auxiliar para o Timer2
           
 

//=============================================================================================
// --- Interrupção ---
ISR(TIMER2_OVF_vect)                            //trata Overflow do Timer,
{
     
   //base de tempo de aprox. 1ms
   cT2       +=  1;                             //incrementa cT2
 

   if(cT2 == 20)                              //cT2 igual a 20?
   {                                            //sim
      //base de tempo de aprox. 20ms
      cT2 = 0;                                  //reinicia cT2

       
      
      digitalWrite(servo1, HIGH);
      delayMicroseconds(psv1);
      digitalWrite(servo1,  LOW);

      digitalWrite(servo2, HIGH);
      delayMicroseconds(psv2);
      digitalWrite(servo2,  LOW);

      digitalWrite(servo3, HIGH);
      delayMicroseconds(psv3);
      digitalWrite(servo3,  LOW);
      

   
   } //end if cT2
   
    
} //end Timer2 OVF


// =============================================================================================================
// --- Configurações iniciais ---
void setup()
{ 

   // T2_ovf = 256 x PS x CM
   // T2_ovf = 256 x 64 x 62.5E-9
   // T2_ovf = 1.024ms
   TCCR2A = 0xA3;                                        //pwm não invertido, fast pwm 
   TCCR2B = 0x04;                                        //pre scaler 1:64
   TIMSK2 = 0x01;                                        //liga interrupção do Timer2
   sei();                                                //habilita interrupção global
 

   pinMode(servo1,   OUTPUT);                            //saída para o servo1
   pinMode(servo2,   OUTPUT);                            //saída para o servo2
   pinMode(servo3,   OUTPUT);                            //saída para o servo3
                  
   digitalWrite(servo1,    LOW);                         //inicializa servo1 em LOW
   digitalWrite(servo2,    LOW);                         //inicializa servo2 em LOW
   digitalWrite(servo3,    LOW);                         //inicializa servo3 em LOW
 
     
} //end setup


// =============================================================================================================
// --- Loop Infinito ---
void loop()
{
  psv1 = map(analogRead(A1), 0, 1023, 600, 2400);
  psv2 = map(analogRead(A2), 0, 1023, 600, 2400);
  psv3 = map(analogRead(A3), 0, 1023, 600, 2400);
 
  
} //end loop
