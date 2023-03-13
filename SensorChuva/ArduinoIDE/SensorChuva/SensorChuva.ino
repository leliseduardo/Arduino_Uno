/* 

      O objetivo deste programa é simular o funionamento de um sensor de chuva construído pelo professor. Não irei construí-lo por falta de tempo, mas a simulação já estará
   suficiente para entender a lógica de funcionamento. Quando precisar, construo o sensor. 
      O sensor de chuva gera um pulso inversamente proporcional à umidade da placa do sensor e, com isso, consegue-se medir a quantidade de chuva.

      Na simulação o programa funcionou como esperado.

*/

// Mapeamento de hardware
#define sensor 7

// Variáveis auxiliares
int leitura;

void setup() {

   pinMode(sensor, INPUT);

   Serial.begin(9600);

}

void loop() {

   leitura = pulseIn(sensor, HIGH);

   leitura = map(leitura, 18000, 2000, 0, 100);

   Serial.print(leitura);
   Serial.println('%');

   delay(500);

}
