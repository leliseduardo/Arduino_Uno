/*
 * max_freq.asm
 *
 *  Created: 12/06/2018 01:19:17
 *   Author: Eng Wagner Rambo
 *   Data:   Junho de 2018
 */ 


; ===========================================================================
; --- Vetor de Reset ---
.org	0x00							;origem no endereço 00h de memória


; ===========================================================================
; --- Configurações iniciais "void setup()" ---
inicio:

	ldi		r16,0x80					;carrega 80h no registrador auxiliar 16
	out		DDRD,r16					;configura PORTD7 como saída
	ldi		r16,0x00					;carrega 00h no registrador auxiliar 16
	out		PORTD,r16					;inicializa PORTD

	nop									;no operation


; ===========================================================================
; --- Loop Infinito "void loop()" ---
loop:

	sbi		PORTD,PD7
	cbi		PORTD,PD7

	rjmp	loop

; ===========================================================================
; --- Final do Programa ---