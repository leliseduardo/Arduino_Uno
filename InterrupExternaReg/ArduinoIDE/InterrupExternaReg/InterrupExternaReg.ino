/* 

            Esta aula tem o objetivo de demosntrar como configurar uma interrupção externa diretamente pelos registradores, não utilizando nenhuma função da biblioteca
    Arduíno.
            Para isso, a interrupção externa, toda vez que acontecer, irá incrementar a variável cont. O pino PD7 irá alternar o seu estado a cada 741ms, causando a 
    interrupção externa. Foi criada uma variável de controle, denominada control, para imprimir o contúdo da variável cont apenas quando o programa sair da função de
    interrupção.

            Na prática o circuito e o programa funcionaram perfeitamente.

*/

// Variáveis auxiliares
int cont = 0x00;
int control = 0x00;

ISR(INT0_vect){

    cont++;
    control = 0x01;
} // end ISR

void setup() {
  
    DDRD &= ~(1 << DDD2);           // Configura PD2 como entrada
    DDRD |=  (1 << DDD7);           // Configura PD7 como saída

    PORTD |= (1 << PORTD2);         // Habilita o pull-up interno de PD2

    EICRA |= (1 << ISC01) | (1 << ISC00);     // Configura a interrupção externa como borda de subida
    EIMSK |= (1 << INT0);                     // Habilita a interrupção externa 0

    sei();                                    // Liga interrupções    

    Serial.begin(9600);
    Serial.println("Iniciando...");
}

void loop() {

    if(control){

        control = 0x00;
        Serial.println(cont);
    } // end if

    PORTD ^= (1 << PORTD7);
    delay(741);
}
