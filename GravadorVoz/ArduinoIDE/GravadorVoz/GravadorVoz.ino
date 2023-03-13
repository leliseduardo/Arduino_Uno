/*

            Este programa é copiado do professor, e tem a função de gravar um som durante 8s, a partir do momento em que o sensor de distância por 
      ultrassom detecta uma distância menor que 15cm.
            Este é um exemplo do módulo ISD1820, que utiliza o CI ISD1820, que tem a função de gravar um som e a possibilidade de reproduzi-lo.
   
*/


// --- Mapeamento de Hardware ---
#define   rec         10                 //Saída para controle da função record do módulo ISD1820
#define   play        11                 //Saída para controle da função play do módulo ISD1820
#define   echo        12                 //Entrada para o pino de echo do sensor
#define   trig        13                 //Saída para o pino de trigger do sensor


// --- Protótipo das Funções Auxiliares ---
void recordPlay(int time_rec);           //Função para gravar e reproduzir a partir do módulo ISD1820
float measureDistance();                 //Função para medir, calcular e retornar a distância em cm
void trigPulse();                        //Função que gera o pulso de trigger de 10µs


// --- Variáveis Globais ---
float dist_cm;                           //Armazena a distância em centímetros entre o robô e o obstáculo


// --- Configurações Iniciais ---
void setup()
{ 
   pinMode(rec,  OUTPUT);                       //Saída para a função record
   pinMode(play, OUTPUT);                       //Saída para a função play
   pinMode(trig, OUTPUT);                       //Saída para o pulso de trigger
   pinMode(echo, INPUT);                        //Entrada para o pulso de echo
 
     
   digitalWrite(rec,  LOW);                     //Pino de gravação inicia em low
   digitalWrite(play, LOW);                     //Pino de reprodução inicia em low   
   digitalWrite(trig, LOW);                     //Pino de trigger inicia em low    
  
} //end setup


void loop()
{
  
    dist_cm = measureDistance();             //mede a distância e armazena em dist_cm
    
    
    if(dist_cm < 15) recordPlay(8);          //se distância inferior a 15 cm, 
                                             //grava 8 segundos de som e em seguida reproduz

    delay(80);                               //periodo de trigger do sensor

} //end loop


// --- Desenvolvimento das Funções Auxiliares ---


void recordPlay(int time_rec)                 //Função para gravar e reproduzir
{
    char i = 0x00;                            //variável para iterações
  
    digitalWrite(rec, HIGH);                  //ativa gravação
    for(i = 0; i<time_rec; i++) delay(1000);  //grava por time_rec segundos
    digitalWrite(rec,  LOW);
    
    
    delay(100);                               //aguarda 100ms
    
    digitalWrite(play, HIGH);                 //ativa reprodução
    delay(50);
    digitalWrite(play, LOW);


} //end recordPlay


float measureDistance()                       //Função que retorna a distância em centímetros
{
  float pulse;                                //Armazena o valor de tempo em µs que o pino echo fica em nível alto
        
  trigPulse();                                //Envia pulso de 10µs para o pino de trigger do sensor
  
  pulse = pulseIn(echo, HIGH);                //Mede o tempo em que echo fica em nível alto e armazena na variável pulse
    
  /*
    >>> Cálculo da Conversão de µs para cm:
    
   Velocidade do som = 340 m/s = 34000 cm/s
   
   1 segundo = 1000000 micro segundos
   
      1000000 µs - 34000 cm/s
            X µs - 1 cm
            
                  1E6
            X = ------- = 29.41
                 34000
                 
    Para compensar o ECHO (ida e volta do ultrassom) multiplica-se por 2
    
    X' = 29.41 x 2 = 58.82
 
  */
  
  return (pulse/58.82);                      //Calcula distância em centímetros e retorna o valor
  
  
} //end measureDistante


void trigPulse()                             //Função para gerar o pulso de trigger para o sensor HC-SR04
{
   digitalWrite(trig,HIGH);                  //Saída de trigger em nível alto
   delayMicroseconds(10);                    //Por 10µs ...
   digitalWrite(trig,LOW);                   //Saída de trigger volta a nível baixo

} //end trigPulse
