/*

        Este é um exemplo de criação de bibliotecas para Arduíno. No caso, o ifndef foi alterado para ficar igual está
    demonstrado em aula, mas não tem problmea deixa-los como o CodeBlocks cria.

        Na simulação esta biblioteca funcionou como esperado.

*/

#ifndef Osciladores_h
#define Osciladores_H
#include "Arduino.h"

class Osciladores{

public:
    Osciladores(int pin);
    void osc_1k();
    void osc_2k();

private:
    int _pin;

}; // end class Osciladores

#endif // OSCILADORES_H_INCLUDED
