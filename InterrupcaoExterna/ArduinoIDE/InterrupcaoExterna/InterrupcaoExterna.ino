/* 

      Este programa tem a função de demonstrar como fazer o uso das interrupções externas do ATMega328P através do Arduíno. A interrupção externa 0, ou
   INT0, está no pino D2 e a INT1 no pino D3.
      Aqui no ArduinoIDE, a função de interrupção pode ter qualquer nome, uma vez que quem garante a interrupção é a função reservada attachInterrupt.
   Porém, ela irá se chamar "void interrupt" como boa prática, assim como a função de interrupção deve ser chamada para os microcontroladore PIC.
      Para configurar a interrupção externa em borda de descida, utiliza-se o comando "FALLING", borda de subida "RISING", qualquer borda "CHANGE", 
   quando estiver em nível baixo "LOW" e alto "HIGH".

      Na simulação o programa funcionou como esperado.

*/

void interrupt(){
  
    digitalWrite(13, !digitalRead(13));   
}

void setup() {
  
    pinMode(2, INPUT);
    pinMode(13, OUTPUT);

    attachInterrupt(0, interrupt, RISING);    
}

void loop() {

    // Apenas aguarda a interrupção...
}
