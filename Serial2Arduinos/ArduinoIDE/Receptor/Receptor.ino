/* 

          O objetivo deste código é receber, através da porta Serial, quais sensores digitais foram lidos no Arduíno transmissor, que le os sensores digitais.

          Na simulação o programa funcionou como esperado.
*/

// Variáveis globais auxiliares
byte content = 0;
int saidas[8] = {4,5,6,7,8,9,10,11};
int estados[8];

void setup() {

    for(int i=4; i < 12; i++)
        pinMode(i, OUTPUT);
  
    Serial.begin(115200);
}

void loop() {

    if(Serial.available()){  

      content = Serial.read();
      
      for(int i=0; i < 8; i++)
          estados[i] = content & (0x01 << i);            // Comando que armazena no vetor saidas os estados lidos dos sensores

      for(int i=0; i < 8; i++)
          digitalWrite(saidas[i], estados[i]);

    } // end if teste de recebimento

    content = 0;                                         
}
