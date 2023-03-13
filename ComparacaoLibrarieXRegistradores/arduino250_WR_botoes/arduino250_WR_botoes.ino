/* ========================================================================================================

  Curso de Arduino WR Kits

  Utilizando ifs - Leitura de Botões

 
  Autor: Eng. Wagner Rambo 
  Data:  Janeiro de 2020

  https://wrkits.com.br/  

  Curso WR Kits Arduino para Iniciantes com certificado:
  https://go.hotmart.com/W13291812W 

======================================================================================================== */

 
void setup() {

    pinMode(2, INPUT_PULLUP);
    pinMode(3, INPUT_PULLUP);
    pinMode(7,       OUTPUT);
 
    digitalWrite(7,    LOW);

} //end setup

void loop() 
{
  
   if(!digitalRead(2)) digitalWrite(7, HIGH);
   if(!digitalRead(3)) digitalWrite(7,  LOW);
 
} //end loop















