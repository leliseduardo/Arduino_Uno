/* ========================================================================================================

  Curso de Arduino WR Kits

  Interrupção Externa - Leitura de Botões

 
  Autor: Eng. Wagner Rambo 
  Data:  Janeiro de 2020

  https://wrkits.com.br/  

  Curso WR Kits Arduino para Iniciantes com certificado:
  https://go.hotmart.com/W13291812W 

======================================================================================================== */

 
// ========================================================================================================
// --- Interrupção ---
ISR(INT0_vect)
{
    PORTD |= (1<<PORTD7);
    
} //end turnOn
 
ISR(INT1_vect)
{
    PORTD &= ~(1<<PORTD7);
  
  
} //end turnOff
 

void setup() {
 
    DDRD &= ~(1 << DDD2);                     //configura PD2 como entrada
    DDRD &= ~(1 << DDD3);                     //configura PD3 como entrada
    DDRD |=  (1 << DDD7);                     //configura PD7 como saída

    PORTD |= (1 << PORTD2);                   //habilita pull-up interno de PD2
    PORTD |= (1 << PORTD3);                   //habilita pull-up interno de PD3
 
    EICRA |= (1 >> ISC11) | (0 << ISC10) |    //configura interrupção externa 1 como borda de descida
             (1 << ISC01) | (0 << ISC00);     //configura interrupção externa 0 como borda de descida
             
    EIMSK |= (1 << INT0)  | (1 << INT1);      //habilita interrupção externa 0 e externa 1

    sei();                                    //liga interrupções

    PORTD &= ~(1 << PORTD7);

} //end setup

void loop() 
{
  
   //aguarda interrupções...
 
} //end loop















