/* 

              Este código visa demonstrar a frequência máxima de oscilação de um pino do ATMega328P, alternando seus estados diretamente pelos registradores. Ainda não é o
      menor nível de abstração, mas já é menor do que utilizando as funções do Arduíno. O nível mais baixo seria utilizar o Assembly.

              Na simulação o Proteus não dá conta de mostrar o sinal quadrado com a frequência tão alta, mas de acordo com o Osciloscópio do professor, a frequência máxima,
      utilizando a Makro toggle, é de 880ns.

*/

// Definição de Makros
#define   set_bit(reg, pin)     (reg |=  (1 << pin))            // Makro para setar d7
#define   reset_bit(reg, pin)   (reg &= ~(1 << pin))            // Makro para resetar d7
#define   toggle_bit(reg, pin)  (reg ^=  (1 << pin))            // Makro para mudar alternar o estado de um pino

void setup() {
  // put your setup code here, to run once:

}

void loop() {

    toggle_bit(PORTD, PORTD7);
    
}
