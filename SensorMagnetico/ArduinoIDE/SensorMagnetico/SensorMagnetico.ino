/* 

            O objetivo deste programa é utlizar um reed switch como sensor magnético que, quando fechar seus contatos pela aproximação de um imã, irá
       soar um alarme.

            Na simulação e na prática o circuito e o programa funcionaram perfeitamente.

*/

// Mapeamento de hardware
#define alarme 8
#define sensor 9

void setup() {

    pinMode(alarme, OUTPUT);
    pinMode(sensor, INPUT_PULLUP);    
} // end void setup

void loop() {

    if(!digitalRead(sensor)){

        while(1){

            tone(alarme, 1000);
            delay(500);
            tone(alarme, 3000);
            delay(500);        
        } // end while    
    } // end if sensor
} // end void loop
