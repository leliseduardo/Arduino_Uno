/* 

                Na aula anterior, denominada "SensorCapacitivo", notou-se que, na leitura do sensor capacitivo ocorrem bouncings, fazendo com que a leitura dele não fique 
         precisa numa rotina normal de leitura no loop infinito. Por isso, o objetivo deste programa é usar a interrupção externa INT0 para fazer a leitura do sensor, e
         acionar em borda de subida. Dessa forma consegue-se eliminar os bouncings do circuito.

                Na simulação o circuito e o programa funcionaram como esperado.

*/

// Mapeamento de hardware
#define sensor 2
#define led 13

void leitura_Sensor(){                                    // Fução que a interrupção externa INT0 chama
  
    digitalWrite(led, !digitalRead(led));
} // end void leitura_Sensor

void setup() {

    pinMode(sensor, INPUT);
    pinMode(led, OUTPUT);

    attachInterrupt(0, leitura_Sensor, RISING);           // Função que faz a interrupção externa INT0 executar a função leitura_Sensor quando houver borda de subida

    digitalWrite(led, LOW);
} // end void setup

void loop() {

    
} // end void loop
