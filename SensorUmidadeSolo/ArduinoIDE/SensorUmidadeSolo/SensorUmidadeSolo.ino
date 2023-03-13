/* 

              Este código tem a função de utilizar o sensor de umidade do solo, que nada mais é do que um sensor resistivo que diminui sua resistência quanto mais úmido 
       estiver o solo, e maior a resistência quanto mais seco estiver os solo.

              Esquema de ligação do driver do sensor:
              Driver do sensor         Arduíno
                     A0                   A3
                     D0                   A2 (ou d16)
                     GND                  A1 (ou d15)
                     VCC                  A0 (ou d14)            


              Na prática o circuito e o programa funcionaram perfeitamente.

*/

// Mapeamento de hardware
#define sinalAnalogico A3
#define sinalDigital   16
#define gndSensor      15
#define vccSensor      14

// Variáveis auxiliares
int umidade = 0x00;

void setup() {
  
    pinMode(sinalAnalogico, INPUT);
    pinMode(sinalDigital, INPUT_PULLUP);
    pinMode(gndSensor, OUTPUT);
    pinMode(vccSensor, OUTPUT);

    digitalWrite(gndSensor, LOW);
    digitalWrite(vccSensor, HIGH);

    Serial.begin(9600);
}

void loop() {

    umidade = analogRead(sinalAnalogico);

    Serial.print("Umidade do sensor de solo: ");
    Serial.println(umidade);

    if(umidade > 512)
      Serial.println("Umidade baixa!");
    else
      Serial.println("Umidade alta!");

    delay(1000);
}
