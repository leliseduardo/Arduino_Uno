/*
 
		O objetivo deste programa � configurar o timer0 do ATMEGA328P a partir de seus registradores, e n�o utilizando bibliotecas,
	como se faz no Ardu�noIDE. 
		Aqui, no Atmel Studio, torna-se poss�vel a programa��o deste microcontrolador em baixo n�vel, assim como foi feito com o Pic.
	Assim, pode-se claramente reparar entre as semelhan�as e diferen�as entre os microcontroladores e seus fabricantes.
		Para calcular o tempo de estouro do timer0, o processo � o mesmo que em microcontroladores Pic, como � mostrado abaixo:
		
		Estouro:
		
		Overflow = (255 - TCNT0) * Prescaler * Ciclo de m�quina
		
		Ciclo de m�quina:
		
		8051 = 1/(clock/12)
		
		PIC = 1/(clock/4)
		
		AVR = 1(clock/1)
		
		Logo:
		
		Ciclo de m�quina = 1/(16MHz/1) = 62,5ns
		
		Overflow = (255-0) * 1:256 * 62,5ns = 4,08ms
		
		Assim, percebe-se que o ciclo de m�quina dos microcontroladores AVR � muito menor, ou seja, o AVR � mais r�pido. Enquanto no
	ciclo de m�quina dos PIC's o ciclo de m�quina � o clock/4, no AVR, o ciclo de �m�quina � clock/1, isto �, a pr�pria frequ�ncia de
	clock.
	
		Na simula��o o programa funcionou perfeitamente.
 
*/ 

// Inclus�o de bibliotecas
#include <avr/io.h>
#include <avr/interrupt.h>

// Vari�veis auxiliares
int cont = 0x00;

/* 

		Como se quer uma troca de estado do pino PD0 a cada 200ms, que resulta num per�do de oscila��o de 400ms, basta calcular o 
	valor necess�rio que cont deve chegar, considerando o tempo de cada overflow.
	
	Tempo troca estado = Overflow * cont
	200ms = 4,08ms * cont
	cont = 200ms/4,08ms = 49,02
	
	Logo, cont = 49
	
	Para alternar PD0, utiliza-se a l�gica XOR, da seguinte forma:
	
		^ = XOR
	
		PORTD ^= 0x01, que � igual a
		PORTD = PORTD ^ 0x01, que � igual a seguinte opera��o
		
		0 0 0 0 0 0 0 0 (PORTD) 
	XOR
		0 0 0 0 0 0 0 1 (0x01)
	  ---------------------------
		0 0 0 0 0 0 0 1 (PORTD)
	XOR
		0 0 0 0 0 0 0 1 (0x01)
	  ---------------------------
	    0 0 0 0 0 0 0 0 (PORTD)
		
	Logo, dessa forma, PD0 �r� alternar	
		
*/

// Fun��o de interrup��o
ISR(TIMER0_OVF_vect){
	
	cont++;
	
	if(cont == 49){
		
		PORTD ^= 0x01;					// Faz l�gica XOR entre PORTD e 0x01, alternando apenas o pino PD0
		
		cont = 0x00;
		
	} // end if
	
}

int main(void){

	// Configura��o de registradores
	
	cli();								// Desliga interrup��o global
	
	DDRD |= (1<<0);						// Configura apenas PD0 como sa�da digital
	PORTD &= ~(1<<0);					// Inicia PD0 em Low
	
	TCNT0 = 0x00;						// Inicia a contagem do timer0 em 0
	TCCR0B = 0x04;						// Configura o prescaler em 1:256
	TIMSK0 = 0x01;						// Habilita a interrup��o do timer0 por overflow
	
	sei();								// Habilita interrup��o global
	
	// O fabricante do mcu recomenda desligar a interrup��o global, configurar os registradores de interrup��o, e depois habilitar 
	// novamente a interrup��o global.
	
    while(1)
    {
        
		// Apenas aguarda a interup��o
		
    }
} // end int main