/* 

        O objetivo deste programa é implementar um medidor de distâncias a partir do sensor de distância ultrassonico. Neste exemplo não será utilizada a biblioteca pronta do 
    sensor HC-SR04, e sim um código em que se cria as funções de leitura. 
        O esquemático do circuito encontra-se no proteus.
        A bibliote do sensor ultrassonico disponibilizado pelo professor foi adicionado no ArduinoIDE.

        A fórmula de conversão de tempo em distância segue a seguinte regra de três:

        1s = 1000000us e velocidade do som de ida e volta do ultrassom = 340/2 = 170m/s = 17000cm/s


        1000000us ---------- 17000cm
            t     ---------- 1cm
                  t = 58,82us

        Logo, a cada 58,82us do tempo do pulso de echo, existe 1cm de distância do sensor a um obstáculo.


        Na prática o circuito e o programa funcionaram perfeitamente, como esperado. 

*/


// Mapeamento de hardware
#define trigger 9
#define echo 8

// Protótipo de funções
void pulso_Trigger();

// Variáveis auxiliares
float pulso = 0.0;
float dist = 0.0;

// Configurações de inicialização
void setup() {

     pinMode(trigger, OUTPUT);                      // Configura trigger como saída digital
     pinMode(echo, INPUT);                          // Configura echo como entrada digital

     digitalWrite(trigger, LOW);                    // Inicializa trigger em Low

     Serial.begin(9600);                            // Inicializa comunicação serial com baudRate = 9600

} // end void setup

void loop() {

     pulso_Trigger();                               // Chama a função pulso_Trigger

     pulso = pulseIn(echo, HIGH);                   // Função que retorna o tempo em que um pino ficou em determinado estado. No caso, o tempo que echo ficou em High

     dist = pulso / 58.82;                          // Calcula a distancia entre sensor e obstáculo, a partir do tempo do pulso do echo

     Serial.println(dist);

     delay(500);                                    // Espera 500ms

} // end void loop

void pulso_Trigger(){
  
     digitalWrite(trigger, HIGH);                    // Liga trigger
     delayMicroseconds(10);                          // Espera 10us
     digitalWrite(trigger, LOW);                     // Desliga trigger
  
} // end void pulso_Trigger
