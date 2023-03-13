/* 

          O objetivo deste código é introduzir a programação do Arduíno, ou ATMega328P, por registradores, da mesma forma que é feito no Atmel Studio. Por ser um software mais
    leve, gratuito e open source, o Arduino IDE pode-sse tornar uma melhor opção para a programação deste microcontroladores. 
          Este código não apresentará a função void loop, pois o objetivo é tentar igualar o máximo possível o uso do Arduíno IDE com uma IDE padrão de microcontrolador.

*/

void setup() {

    DDRB |= (1 << 5);                   // Configura o bit 5 do PORTB como saída digital
    PORTB &= ~(1 << 5);                 // Inicia o bit 5 do portb em Low

    while(1){
      
        PORTB |= (1 << 5);
        delay(100);
        PORTB &= ~(1 << 5);
        delay(100);
    }
} // end void setup




/* 
 *  
          A experessão:

          DDRB |= (1 << 5), é igual à:

          DDRB = DDRB | (1 << 5), e (1 << 5) é igual à:

          (1 << 5) = 0b10000 = deslocar o bit 1 5 vezes para esquerda

          Assim, a expressão, que é denominada como técnica de bitwise, tem a função de fazer a lógica OR entre o bit 5 de DDRB e o bit 1, acionando a penas o bit 5 de DDRB.


          Analaogamente, a expressão: 

          PORTB &= ~(1 << 5), é igual à:

          PORTB = PORTB & ~(1 << 5), e ~(1 << 5) = ~(0b10000) = 0b00000 = inverso do bit 1 deslocado 5 vezes para esquerda, que é igual ao bit 0 deslocado 5 vezes a esquerda

          Assim, essa expressão tem a função de fazer a lógica AND entre o bit 5 do PORTB e o bit 1 invertido, logo 0, que faz com que o bit 5 do PORTB seja limpo.

          A técnica utilizada, chamada bitwise, é amplamente utilizada nos microcontroladores AVR por aconselhamento de seu próprio datasheet. Essa técnica pararece vir da
          programação em Assembly, que utiliza as operações binárias na manipulação de bits e registradores.

*/
