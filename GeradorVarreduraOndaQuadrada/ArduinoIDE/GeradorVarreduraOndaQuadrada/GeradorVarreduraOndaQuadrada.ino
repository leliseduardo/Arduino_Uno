/* 

          O objetivo deste programa é criar um gerador de onda quadrada que varia a frequência continuamente entra um intervalo mínimo e máximo de 
     frequências. Esta função é chamada de sweep e está presente na maioria dos geradores de frequências profissional.

          Na simulação o programa e o circuito funcionaram perfeitamente. 
        
*/

// Mapeamento de hardware
#define sweep 6
#define ajusteMin A0
#define ajusteMax A1

// Protótipos de funções auxiliares
int freq_Min(int minima, int maxima);
int freq_Max(int minima, int maxima);
void gera_Sweep(int minima, int maxima, int tempo);

// Variáveis auxiliares
int freqMin;
int freqMax;
int valPWM;
float valSeno;


void setup() {

    pinMode(sweep, OUTPUT);
    pinMode(ajusteMax, INPUT);
    pinMode(ajusteMax, INPUT);
} // end void setup

void loop() {

    freqMin = freq_Min(1, 100);
    freqMax = freq_Max(5000, 10000);

    gera_Sweep(freqMin, freqMax, 10);
} // end void loop


int freq_Min(int minima, int maxima){

    int frequencia;

    frequencia = analogRead(ajusteMin);

    frequencia = map(frequencia, 0, 1024, minima, maxima);

    return frequencia;
} // end int freq_min



int freq_Max(int minima, int maxima){
  
    int frequencia;

    frequencia = analogRead(ajusteMax);

    frequencia = map(frequencia, 0, 1024, minima, maxima);

    return frequencia;
} // end int freq_Max


void gera_Sweep(int minima, int maxima, int tempo){
  
    for(int i=0; i < 180; i++){

        valSeno = (sin(i*(3.141592/180)));

        valPWM = minima + (int(valSeno*maxima));

        tone(sweep, valPWM);

        delay(tempo);
    } // end for 
} // end void gera_Sweep

/* 

      A função gera_Sweep, através do laço for, faz com que o valor do PWM varie da frequência mínima até a frequência máxima, num tempo determinado
   por delay*i(máximo), variando a frequência numa curva senoidal. 
      Deve-se entender que o sinal de saída é quadrado, mas o modo como a frequência se alterna no tempo é de forma senoidal. Isto é, variando rapida-
   mente, e varia devagar perto da frequência máxima. Como foi configurado uma variação do seno de 0º a 180º, deve-se lembrar que, até 90º, o valor do
   seno aumenta, quando é 90º, seno 90º = 1, e de 90º até 180º o seno diminui até chegar em seno 180º = 0.

*/
