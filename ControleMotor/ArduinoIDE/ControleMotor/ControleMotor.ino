/* 

          O objetivo deste programa é fazer o controle de um motor. Dois potenciômetro controlarão um a velocidade e outro a direção de giro do motor. Os potenciômetros serão 
     lidos pelos ADC's do Arduíno. Três saídas digitais irão controlar um drive para o motor, que consistem em uma ponte H dentro de um circuito impresso, o L293D. Duas das
     saídas controlam a direção do motor e uma delas gera um PWM, que controla a velocidade do motor. 
          Este projeto e os próximos serão simulados no Proteus 7.7, pois somente ele possui o ATMEGA328P PTH, de 28 pinos.

          Como não tenho o CI L293D, não tenho como fazer a prática.
          
          Na simulação o programa funcionou perfeitamente. A configuração do ATMEGA328P no Proteus é muito importante para o funcionamento. Tanto a frequência quanto os fuses.
     
*/

// Mapamento de hardware

#define velocidade A0
#define sentido A1
#define s1 6
#define s2 7
#define pwm 3

// Variáveis auxiliares
int leituraVelocidade = 0, leituraSentido = 0;


void setup() {

  pinMode(velocidade, INPUT);
  pinMode(sentido, INPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(pwm, OUTPUT);

  Serial.begin(9600);
  
} // end void setup


void loop() {

  leituraSentido = analogRead(sentido);
  leituraVelocidade = analogRead(velocidade) / 4;

  if(leituraSentido < 450){

    analogWrite(pwm, leituraVelocidade);
    Serial.println(leituraSentido);

    digitalWrite(s1, HIGH);
    digitalWrite(s2, LOW);
    
  } // end if
  else if(leituraSentido > 550){

    analogWrite(pwm, leituraVelocidade);
    Serial.println(leituraSentido);

    digitalWrite(s2, HIGH);
    digitalWrite(s1, LOW);
    
  } // end if
  else{

    analogWrite(pwm, leituraVelocidade);
    Serial.println(leituraSentido);

    digitalWrite(s1, LOW);
    digitalWrite(s2, LOW);
    
  } // end if

} // end void loop
