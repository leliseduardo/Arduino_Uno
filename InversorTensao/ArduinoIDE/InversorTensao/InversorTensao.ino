/* 

            Este programa tem a função de criar um inversor de tensão, circuito que converte tensão DC em tensão AC. Para isso, oscila dois pinos do Arduíno em 120Hz, para
     que a saída tenha 60Hz. Os pinos podem ser ligados a transístores, que poderão estar ligados à transformadores, que irão gerar a tensão alternada. Entre o desligamento
     de um transistor e o acionamento de outro, existe um tempo denominado tempo morto. Esse tempo é necessário para que os dois transístores não fiquem acionados ao mesmo
     tempo e não gerem um curto circuito. Não é necessário configurar este tempo, o próprio ciclo de máquina, por menor que seja, já garante este tempo morto. 
            Este inversor aqui criado, gera tenões apenas positivas, não gerando uma tensão realmente alternada. O que se tem na saída do transformador é uma tensão contínua
     variável, que oscila entre zero e seu pico.

            Na simulação o circuito funcionou perfeitamente.

*/

// Mapeamento de hardware
#define t1  2
#define t2  3

// Constantes gloabais auxiliares
const int periodo = 8333;                // Para uma alternância dos pinos em 120Hz

// Variáveis globais auxiliares
int tempoDecorrido;
int tempoAtual = 0x00;

void setup() {

    pinMode(t1, OUTPUT);
    pinMode(t2, OUTPUT);

    digitalWrite(t1, LOW);
    digitalWrite(t2, HIGH);
} // end void setup

void loop() {

    tempoDecorrido = micros();
  
    if(tempoDecorrido - tempoAtual > periodo){

        tempoAtual = tempoDecorrido;
      
        if(digitalRead(t1)){

            digitalWrite(t1, LOW);

            digitalWrite(t2, !digitalRead(t2));
        } // end if t1 ligado
        else{

            digitalWrite(t2, LOW);

            digitalWrite(t1, !digitalRead(t1));
        } // end else t1 ligado
    } // end if temporizado
} // end void loop
