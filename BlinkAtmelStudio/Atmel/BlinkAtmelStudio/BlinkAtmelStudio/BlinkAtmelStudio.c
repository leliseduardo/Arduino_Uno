/*
 * BlinkAtmelStudio.c
 *
 * Created: 01/10/2020 14:47:11
 *  Author: Eduardo
 *
 *	Description:
 *		Este programa tem a função de apresentar o Atmel Studio, simplesmente piscando um led.
 *
 *	Results:
 *		Na simulação, feita do Proteus, o programa funcionou como esperado.
 *
 */ 

// Freuquência
#define F_CPU 16000000

// Inclusão de bibliotecas
#include <avr/io.h>
#include <util/delay.h>

// Método de trabalhar com os ports
//
// registrador = registrador OR flag(1) [ligando um determinado bit]
// registrador = registrador AND (not flag(1)) [ desligando um determinado bit]

// Macros
#define set_bit(reg,bit)	(reg |= (1<<bit))				// Cria macro para configurar ou setar um pino
#define clear_bit(reg,bit)	(reg &= ~(1<<bit))				// Cria macro para configurar ou limpar um pino

int main(void)
{
	set_bit(DDRB,PORTB5);									// Configura pino5, do portb, como saída. Aqui 1 = saída e o = entrada
	
    while(1)
    {
        
		set_bit(PORTB,PORTB5);
		_delay_ms(500);
		clear_bit(PORTB,PORTB5);
		_delay_ms(500);
		
    }
}

/* 
		O método de trabalhar com as IOS dos microcontrolados Atmel é uma sugestão do datasheet. Este método faz uma operação lógica
	entre o registrador que se quer configurar e o nível lógico 1 rotacionado x vezes para esquerda, sendo o número x o valor do pino
	que se quer configurar. Assim, se o pino que se quer configurar é o pino 5, como no exemplo, a configuração para fazer desse pino
	uma saída é:
	
		registrador = registrador OR (1<<pin)
		DDRB = DDRB | (1<<5)
		DDRB |= (1<<5)
		Que significa a operação:
		
		0000 0000	DDRB 
			OR
		0001 0000	(1<<5)
	   -----------
	    0001 0000
		
		Para limpar um bit, a operação é análoga, mas com lógica AND e ~(1<<pin). Exemplo:
		
		registrador = registrador AND ~(1<<pin)
		DDRB = DDRB & ~(1<<5)
		DDRB &= ~(1<<5)
		DDRB &= (0>>-5)
		Que significa a operação:
		
		1111 1111	DDRB
		OR
		0001 0000	(0>>-5)
		-----------
		1111 1101	   
*/