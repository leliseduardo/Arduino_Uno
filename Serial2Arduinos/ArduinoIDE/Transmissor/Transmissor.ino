/* 

          O objetivo deste código é enviar, através da porta Serial, os sensores digitais lidos através de um Arduíno, para que o receptor possa usar essa informação.

          Na simulação o programa funcionou como esperado.
*/

// Variáveis globais auxiliares
byte content = 0;
int sensores[8] = {4,5,6,7,8,9,10,11};

void setup() {

    for(int i=4; i < 12; i++)
        pinMode(i, INPUT_PULLUP);
  
    Serial.begin(115200);
}

void loop() {
  
    for(int i=0; i < 8; i++)
        content |= (digitalRead(sensores[i]) << i);       // Comando que armazena, bit a bit, a leitura dos sensores em content

    Serial.write(content);

    content = 0;                                         
}
