/* 

        O objetivo deste programa é utilizar o CI 94HC595 para expandir as portas do Arduíno. Este CI nada mais é do que um registrador de deslocamento (shift register) de 8
   bits. Assim, é possível controlar 8 saídas do registrador de deslocamento com apenas 3 saídas do Arduíno.
        Neste aula o professor confundiu Store com Shift e fez o código errado. Porém, já corrigi e a explicação da função está num comentário abaixo dela.

        Esta é uma ótima opção para circuitos que se deseja expandir muito as saídas.

        Na execução o programa funcionou como esperado.     

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
 
    digitalWrite(store, LOW);
    shift_register(10);
    digitalWrite(store, HIGH);

}

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
