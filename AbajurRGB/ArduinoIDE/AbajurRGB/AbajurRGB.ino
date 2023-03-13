/*

            Este código é copiado do professor, e tem a função de variar as intencidades dos leds vermelho, verde e azul para que cores aleatórias 
      sejam geradas. Este projeto não será testado na prática, mas é um bom exemplo do uso de leds RGB.
   
*/

// --- Mapeamento de Hardware ---
#define ledRed    11 //led vermelho
#define ledGreen  10 //led verde
#define ledBlue    9 //led azul


// --- Variáveis Globais ---
float RGB1[3]; //vetor RGB1
float RGB2[3]; //vetor RGB2
float INC[3];  //vetor de incremento

int red, green, blue; //armazena o respectivo valor RGB

 
// --- Configurações Iniciais ---
void setup()
{
    randomSeed(analogRead(0)); //gera números aleatórios a partir da semente lida em A0 (ruído analógico)
    
    //Valores RGB iniciam em zero
    RGB1[0] = 0;
    RGB1[1] = 0;
    RGB1[2] = 0;
    
    //Valores RGB aleatórios entre 0 e 255 (transição de cor que o abajur fará)
    RGB2[0] = random(256);
    RGB2[1] = random(256);
    RGB2[2] = random(256);
    
} //end setup


// --- Loop Infinito ---
void loop()
{
     randomSeed(analogRead(0)); //obtém um valor aleatório
 
     
     //Consulta os valores RGB do início ao fim, e avalia o incremento a ser feito
     for(int x=0; x<3; x++) INC[x] = (RGB1[x] - RGB2[x]) / 256;
     
 
     for(int x=0; x<256; x++)
     {
        //obtém os valores de vermelho, verde e azul
        red = int(RGB1[0]);
        green = int(RGB1[1]);
        blue = int(RGB1[2]); 
        
        //gera o PWM no respectivo pino
        analogWrite(ledRed, red);
        analogWrite(ledGreen, green);
        analogWrite(ledBlue, blue);
        
        delay(10); //tempo entre as transições
        
        //subtrai o valor do incremento
        RGB1[0] -= INC[0];
        RGB1[1] -= INC[1];
        RGB1[2] -= INC[2];
        
     } //end for
     
     
     // gera novos valores aleatórios para a próxima transição
     for(int x=0; x<3; x++)
     {
       // força a ocorrência das cores primárias 
        RGB2[x] = random(556)-300;
        
        RGB2[x] = constrain(RGB2[x], 0, 255); //mantém RGB2[x] na faixa entre 0 e 255
        
        delay(1000);
        
     } //end for
     
} //end loop


/*

     TABELA DE COMBINAÇÃO DE CORES
     
     Vermelho  Verde   Azul    |  Cor Resultante
     -------------------------------------------
        255      0      0      |     Vermelho
         0      255     0      |     Verde
         0       0     255     |     Azul
        255     255     0      |     Amarelo
         0      255    255     |     Ciano
        255      0     255     |     Magenta
        255     255    255     |     Branco


*/
