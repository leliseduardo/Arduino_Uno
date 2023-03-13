/* 

            Este código tem a função de demonstrar um RTC a partir da temporiazação do timer2. Para diminuir a latência de interrupção, os pinos serão configurados e manipula-
     dos através dos registradores do ATMega328P.

     ***** TIMER 2 *****
      
     Ciclo de máquina = 62,5ns

     Overflow = (256 - TCNT2) * Prescaler * Ciclo de maquina
     Overflow = (256 - 56) * 1:32 * 62,5ns
     Overflow = 250 * 32 * 62,5ns
     Overflow = 400us 

     Se o tempo que se quer é 1s:

     1s / 400us = 2500

     Logo, 2500 * 400us = 1s

              Testando o tempo, na simulação, do RTC feito com as funções do Arduíno, obteve-se um tempo de 1,01s. Usando os registradores do mcu, obteve-se um tempo de 1,00s.
    Porém, sabe-se que ainda existe a latência de interrupção e o tempo não é exatamente 1s na vida real, mas bem próximo disso.

              Portando, na simulação o programa funcionou como esperado.

*/

// Mapeamento de hawdware
#define out 7

// Variáveis auxiliares
int cont = 0x00;
int mascara = B10000000;                      // Máscara que se utiliza para alternar o valor de um bit com a lógica XOR

// Função de interrupção
ISR(TIMER2_OVF_vect){
  
    TCNT2 = 56;

    cont++;

    if(cont == 2500){

        cont = 0x00;
      
        //digitalWrite(out, !digitalRead(out));
        PORTD ^= mascara;                    // Através da lógica XOR e da máscara, alterna o estado de D7
    }
} // end funçao interrupão


void setup() {
  
    //pinMode(out, OUTPUT);
    //digitalWrite(out, LOW);
    DDRD = 0x80;                              // Configura apenas D7 como saída digital
    PORTD = 0x00;                             // Inicia todas as saídas do portd em Low

    TCCR2A = 0x00;                            // Configura o timer2 em funcionamento normal
    TCNT2 = 56;                               // Inicia o contador em 56 para contagem de 200
    TCCR2B = 0x03;                            // Configura o prescaler para 1:32
    TIMSK2 = 0x01;                            // Habilita a interrupção por overflow do timer2
}

void loop() {

    // Apenas aguarda a interrupção
}
