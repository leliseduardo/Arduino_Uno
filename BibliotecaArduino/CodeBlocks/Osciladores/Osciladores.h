/*

        Este � um exemplo de cria��o de bibliotecas para Ardu�no. No caso, o ifndef foi alterado para ficar igual est�
    demonstrado em aula, mas n�o tem problmea deixa-los como o CodeBlocks cria.

        Na simula��o esta biblioteca funcionou como esperado.

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
