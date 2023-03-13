/* 

          O objetivo deste programa é gerar uma onda quadrada e, através de dois potenciômetros, variar a frequencia deste sinal.

          Na simulação o circuito e o programa funcionaram perfeitamente.

*/

// Mapeamento de hardware
#define ajuste A0
#define ajusteFino A1
#define saida 8

// Variáveis auxiliares
int freq;

void setup() {

    pinMode(ajuste, INPUT);
    pinMode(ajusteFino, INPUT);
    pinMode(saida, INPUT);
} // end void setup

void loop() {

    freq = ((analogRead(ajuste)*10) + analogRead(ajusteFino));

    tone(saida, freq);
} // end void loop
