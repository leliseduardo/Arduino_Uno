/* 

      O objetivo deste programa é utilizar agora dois shift-registers, ligados com as mesmas 3 portas. O registrador com os bits mais significativos irá decrementar de 255 até
   0, e o menos significativo irá contar de 0 até 255.

      Na simulação funcionou perfeitamente. Não tenho o CI74HC 595 para realizar a prática, mas o conhecimento já foi adquirido.
    
*/

// Mapemento de hardware
#define store 12
#define data 11 
#define shift 10

// Funções auxiliares
void shift_register(byte value);

void setup() {
  
    pinMode(store, OUTPUT);
    pinMode(data, OUTPUT);
    pinMode(shift, OUTPUT);

} // end void setup 

void loop() {

    for(int i=0; i < 256; i++){
        digitalWrite(store, LOW);
        shift_register(i);
        shift_register(255-i);
        digitalWrite(store, HIGH);
        delay(250);
    } // end for
}

/* 

          Como no código está sendo enviado dois valores para os registradores em cascata, o primeiro valor enviado, de 8 bits, é "empurrado" para o segundo registrador, o com
      bits menos significativos. O segundo valor enviado, portanto, fica no primeiro registrador, com os bits mais significativos. Logo, os bits mais significativos, do primeiro 
      registrador, de 16 bits vão decrescer, pois o segundo valor enviado decresce, e os bits menos significativos, do segundo registrador, de 16 bits irão crescer, pois é o 
      primeiro valor enviado. 
          A passagem do segundo valor do primeiro para o segundo registrador ocorre por meio do pino 9, que transmite o primeiro valor recebido para o pino de dados do segundo
      registrador.
         Caso se quisesse interligar três registrador, e obter 24 bits, bastaria ligar o pino 9 do segundo registrador no pino de dados do terceiro. Assim, enviando três valores
      de 8 bits para essa cascata de 3 registradores, o primeiro valor seria o menos significativo, e o último, ou terceiro valor, seria o mais significativo. Logo, se fosse 
      enviado 3 valores para essa cascata, o primeiro valor seria "empurrado" para o terceiro registrador, o segundo valor "empurrado" para o segundo registrador e o terceiro
      valor ficaria no primeiro registrador.
         Esse processo ocorre automáticamente nos registradores, pois, quando um segundo valor é enviado, o registrador desloca os valores antigos, passando-os para o pino
      9 desse registrador. Assim, ligando o pino 9 no pino de dados de outro registrador, os dados antigos do primeiro registrador passam para o segundo por deslocamento.  

*/

void shift_register(byte value){

      boolean control;
  
      digitalWrite(shift, LOW);
      digitalWrite(data, LOW);

      for(int i=0; i < 8; i++){
        
          digitalWrite(shift, LOW);

          if(value & (1<<i)){ // Testa se há algum valor para atualizar e, se tiver, desloca value i vezes para esquerda
            
                control = HIGH;
                          
           }
           else
                control = LOW;

           digitalWrite(data, control);
           digitalWrite(shift, HIGH);
           
      } // end for

      digitalWrite(shift, LOW);
  
} // end void shift_register

/* 

        Para entender esta função, precisa-se primeiro entender como funciona o shift-register. Este CI é controlado por 3 pinos, shift, data e store. Data recebe um bit, shift
     desloca esse bit do mais significativo para o menos e store atualiza a saída do registrador. O shift e store realizam suas funções quando são colocados em nível alto.
        A partir disso, a função acima recebe um valor de 8 bits que deseja-se escrever no registrador. Primeiramente coloca-se shift e data em 0, para limpar as entradas. 
     Depois, a execução entra em um laço for que realiza 8 vezes o loop. Considerando a forma binária do número recebido pela função, a cada execução do for é testado se o
     bit é zero ou 1, através de uma lógica AND, que retorna se cada bit de value é 0 ou 1. Se o bit for 1, a flag control é 1, se for zero, a flag 1 é zero. Assim, após o teste,
     ainda dentro do for, data é alterado de 0 para 1 ou vice-versa conforme o resultado do teste, e a o shift desloca, no registrador, o valor de data atual. Após o laço for
     o shift é desativado e a execução sai da função. A atualização das saídas do registrador acontece no loop infinito, setando Store. 
        A expressão (value & (1<<i)) faz a lógica AND entre value e 11111111, depois, value AND 11111110, depois, value AND 11111100. Assim, essa expressão não compara, e sim,
     resulta em um valor. Após 8 iterações, a lógica AND terá percorrido todo o value. Dessa forma o programa testa se o valor de cada bit de value, do menos significativo ao 
     mais, é 1 ou 0.

*/
