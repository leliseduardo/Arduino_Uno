/*
 * BlinkAtmelStudio.c
 *
 * Created: 01/10/2020 14:47:11
 *  Author: Eduardo
 *
 *	Description:
 *		Este programa tem a fun��o de apresentar o Atmel Studio, simplesmente piscando um led.
 *
 *	Results:
 *		Na simula��o, feita do Proteus, o programa funcionou como esperado.
 *
 */ 

// Freuqu�ncia
#define F_CPU 16000000

// Inclus�o de bibliotecas
#include <avr/io.h>
#include <util/delay.h>

// M�todo de trabalhar com os ports
//
// registrador = registrador OR flag(1) [ligando um determinado bit]
// registrador = registrador AND (not flag(1)) [ desligando um determinado bit]

// Macros
#define set_bit(reg,bit)	(reg |= (1<<bit))				// Cria macro para configurar ou setar um pino
#define clear_bit(reg,bit)	(reg &= ~(1<<bit))				// Cria macro para configurar ou limpar um pino

int main(void)
{
	set_bit(DDRB,PORTB5);									// Configura pino5, do portb, como sa�da. Aqui 1 = sa�da e o = entrada
	
    while(1)
    {
        
		set_bit(PORTB,PORTB5);
		_delay_ms(500);
		clear_bit(PORTB,PORTB5);
		_delay_ms(500);
		
    }
}

/* 
		O m�todo de trabalhar com as IOS dos microcontrolados Atmel � uma sugest�o do datasheet. Este m�todo faz uma opera��o l�gica
	entre o registrador que se quer configurar e o n�vel l�gico 1 rotacionado x vezes para esquerda, sendo o n�mero x o valor do pino
	que se quer configurar. Assim, se o pino que se quer configurar � o pino 5, como no exemplo, a configura��o para fazer desse pino
	uma sa�da �:
	
		registrador = registrador OR (1<<pin)
		DDRB = DDRB | (1<<5)
		DDRB |= (1<<5)
		Que significa a opera��o:
		
		0000 0000	DDRB 
			OR
		0001 0000	(1<<5)
	   -----------
	    0001 0000
		
		Para limpar um bit, a opera��o � an�loga, mas com l�gica AND e ~(1<<pin). Exemplo:
		
		registrador = registrador AND ~(1<<pin)
		DDRB = DDRB & ~(1<<5)
		DDRB &= ~(1<<5)
		DDRB &= (0>>-5)
		Que significa a opera��o:
		
		1111 1111	DDRB
		OR
		0001 0000	(0>>-5)
		-----------
		1111 1101	   
*/