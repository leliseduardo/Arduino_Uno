/* ========================================================================================================

  Curso de Arduino WR Kits

  Utilizando attachInterrupt - Leitura de Botões

 
  Autor: Eng. Wagner Rambo 
  Data:  Janeiro de 2020

  https://wrkits.com.br/  

  Curso WR Kits Arduino para Iniciantes com certificado:
  https://go.hotmart.com/W13291812W 

======================================================================================================== */


void turnOn()
{
   digitalWrite(7, HIGH);  

}

void turnOff()
{
   digitalWrite(7,  LOW);  
  
}

 
void setup() {

    pinMode(2, INPUT_PULLUP);
    pinMode(3, INPUT_PULLUP);
    pinMode(7,       OUTPUT);
 
    digitalWrite(7,    LOW);

    attachInterrupt(digitalPinToInterrupt(2), turnOn,  FALLING);
    attachInterrupt(digitalPinToInterrupt(3), turnOff, FALLING);

} //end setup

void loop() 
{

   //aguarda interrupções...
 
} //end loop















