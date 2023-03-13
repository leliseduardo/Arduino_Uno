/*
 
		O objetivo deste programa é configurar o timer0 do ATMEGA328P a partir de seus registradores, e não utilizando bibliotecas,
	como se faz no ArduínoIDE. 
		Aqui, no Atmel Studio, torna-se possível a programação deste microcontrolador em baixo nível, assim como foi feito com o Pic.
	Assim, pode-se claramente reparar entre as semelhanças e diferenças entre os microcontroladores e seus fabricantes.
		Para calcular o tempo de estouro do timer0, o processo é o mesmo que em microcontroladores Pic, como é mostrado abaixo:
		
		Estouro:
		
		Overflow = (255 - TCNT0) * Prescaler * Ciclo de máquina
		
		Ciclo de máquina:
		
		8051 = 1/(clock/12)
		
		PIC = 1/(clock/4)
		
		AVR = 1(clock/1)
		
		Logo:
		
		Ciclo de máquina = 1/(16MHz/1) = 62,5ns
		
		Overflow = (255-0) * 1:256 * 62,5ns = 4,08ms
		
		Assim, percebe-se que o ciclo de máquina dos microcontroladores AVR é muito menor, ou seja, o AVR é mais rápido. Enquanto no
	ciclo de máquina dos PIC's o ciclo de máquina é o clock/4, no AVR, o ciclo de ´máquina é clock/1, isto é, a própria frequência de
	clock.
	
		Na simulação o programa funcionou perfeitamente.
 
*/ 

// Inclusão de bibliotecas
#include <avr/io.h>
#include <avr/interrupt.h>

// Variáveis auxiliares
int cont = 0x00;

/* 

		Como se quer uma troca de estado do pino PD0 a cada 200ms, que resulta num perído de oscilação de 400ms, basta calcular o 
	valor necessário que cont deve chegar, considerando o tempo de cada overflow.
	
	Tempo troca estado = Overflow * cont
	200ms = 4,08ms * cont
	cont = 200ms/4,08ms = 49,02
	
	Logo, cont = 49
	
	Para alternar PD0, utiliza-se a lógica XOR, da seguinte forma:
	
		^ = XOR
	
		PORTD ^= 0x01, que é igual a
		PORTD = PORTD ^ 0x01, que é igual a seguinte operação
		
		0 0 0 0 0 0 0 0 (PORTD) 
	XOR
		0 0 0 0 0 0 0 1 (0x01)
	  ---------------------------
		0 0 0 0 0 0 0 1 (PORTD)
	XOR
		0 0 0 0 0 0 0 1 (0x01)
	  ---------------------------
	    0 0 0 0 0 0 0 0 (PORTD)
		
	Logo, dessa forma, PD0 írá alternar	
		
*/

// Função de interrupção
ISR(TIMER0_OVF_vect){
	
	cont++;
	
	if(cont == 49){
		
		PORTD ^= 0x01;					// Faz lógica XOR entre PORTD e 0x01, alternando apenas o pino PD0
		
		cont = 0x00;
		
	} // end if
	
}

int main(void){

	// Configuração de registradores
	
	cli();								// Desliga interrupção global
	
	DDRD |= (1<<0);						// Configura apenas PD0 como saída digital
	PORTD &= ~(1<<0);					// Inicia PD0 em Low
	
	TCNT0 = 0x00;						// Inicia a contagem do timer0 em 0
	TCCR0B = 0x04;						// Configura o prescaler em 1:256
	TIMSK0 = 0x01;						// Habilita a interrupção do timer0 por overflow
	
	sei();								// Habilita interrupção global
	
	// O fabricante do mcu recomenda desligar a interrupção global, configurar os registradores de interrupção, e depois habilitar 
	// novamente a interrupção global.
	
    while(1)
    {
        
		// Apenas aguarda a interupção
		
    }
} // end int main