/*

          Este código foi copiado do professor. Serve apenas para exemplificar a aplicação de um voltímetro com o Arduíno. Este projeto não será feito
      na prática neste momento, mas quando eu precisar e se precisar, aqui está um bom exemplo de como fazer um voltímetro.
   
*/

//========================================================================================//
// --- Mapeamento de Hardware ---
#define  dig_uni    8                          //dígito das unidades
#define  dig_dez    9                          //dígito das dezenas
#define  dig_cen   17                          //dígito das centenas
#define  dig_mil   16                          //dígito dos milhares
#define  v_input   A0                          //leitura de tensão


//========================================================================================//
// --- Protótipo das Funções ---
int display_n(int num);                        //Exibe o valor correspondente no display de catodo comum
int display_dp(int num);                       //Exibe o valor correspondente no display adicionando o ponto decimal
long average_volt();                           //Retorna a média de 100 leituras de tensão
void volts();                                  //Calcula a tensão em Volts


//========================================================================================//
// --- Variávei Globais ---
long store;                                    //Armazena a média de 100 leituras de tensão
long t_Volts = 1498;                                  //Armazena tensão em Volts
short control = 1;                             //Variável de controle (para saber qual display está ativo)
int mil, cen, dez, uni;                        //Variáveis auxiliares para dados nos displays


//========================================================================================//
// --- Rotina de Interrupção ---
ISR(TIMER2_OVF_vect)      // Trata Overflow do Timer2
{
    TCNT2 = 196;          // Reinicializa o registrador do Timer2
    
    
    if(!digitalRead(dig_mil) && control == 1)      //Dígito dos milhares desligado?
    {                                              //Variável de controle igual a 1?
        control = 0x02;                            //Sim, control recebe o valor 2
        digitalWrite(dig_uni, LOW);                //Apaga o dígito das unidades
        digitalWrite(dig_dez, LOW);                //Apaga o dígito das dezenas
        digitalWrite(dig_cen, LOW);                //Apaga o dígito das centenas
        PORTD   = 0x00;                            //Desliga PORTD
        mil     = t_Volts/1000;                    //Calcula o dígito dos milhares
        digitalWrite(dig_mil, HIGH);               //Ativa dígito dos milhares
        PORTD   = display_n(mil);                  //Escreve o valor no display dos milhares
        
    } //end if dig_mil
    
    else if(!digitalRead(dig_cen) && control == 2) //Dígito das centenas desligado?
    {                                              //Variável de controle igual a 2?
        control = 0x03;                            //Sim, control recebe o valor 3
        digitalWrite(dig_uni, LOW);                //Apaga o dígito das unidades
        digitalWrite(dig_dez, LOW);                //Apaga o dígito das dezenas
        digitalWrite(dig_mil, LOW);                //Apaga o dígito dos milhares
        PORTD   = 0x00;                            //Desliga PORTD
        cen = (t_Volts%1000)/100;                  //Calcula o dígito das centenas
        digitalWrite(dig_cen, HIGH);               //Ativa dígito das centenas
        PORTD   = display_dp(cen);                 //Escreve o valor no display das centenas
                                                   //com ponto decimal 
    } //end if dig_cen
        
    else if(!digitalRead(dig_dez) && control == 3) //Dígito das dezenas desligado?
    {                                              //Variável de controle igual a 3?
        control = 0x04;                            //Sim, control recebe o valor 3
        digitalWrite(dig_uni, LOW);                //Apaga o dígito das unidades
        digitalWrite(dig_cen, LOW);                //Apaga o dígito das centenas
        digitalWrite(dig_mil, LOW);                //Apaga o dígito dos milhares
        PORTD   = 0x00;                            //Desliga PORTD
        dez = (t_Volts%100)/10;                    //Calcula o dígito das dezenas
        digitalWrite(dig_dez, HIGH);               //Ativa dígito das dezenas
        PORTD   = display_n(dez);                  //Escreve o valor no display das dezenas
        
    } //end else if dig_dez
        
    else if(!digitalRead(dig_uni) && control == 4) //Dígito das unidades desligado?
    {                                              //Variável de controle igual a 4?
        control = 0x01;                            //Sim, control recebe o valor 1 (para encerrar a lógica)
        digitalWrite(dig_dez, LOW);                //Apaga o dígito das dezenas
        digitalWrite(dig_cen, LOW);                //Apaga o dígito das centenas
        digitalWrite(dig_mil, LOW);                //Apaga o dígito dos milhares
        PORTD   = 0x00;                            //Desliga PORTD
        uni = t_Volts%10;                          //Calcula o dígito das unidades
        digitalWrite(dig_uni, HIGH);               //Ativa dígito das unidades
        PORTD   = display_n(uni);                  //Escreve o valor no display das unidades
        
     } //end else if dig_uni
     
} //end Timer2 OVF




//========================================================================================//
// --- Configurações Iniciais ---
void setup()
{
     for(short i=0x00;i<0x08;i++) pinMode(i, OUTPUT);
     
     pinMode(dig_uni, OUTPUT);
     pinMode(dig_dez, OUTPUT);
     pinMode(dig_cen, OUTPUT);
     pinMode(dig_mil, OUTPUT);
     
     
     // -- Configuração do Estouro do Timer 2 --
     TCCR2A = 0x00;   //Timer operando em modo normal
     TCCR2B = 0x07;   //Prescaler 1:1024
     TCNT2  = 196;    //Inicia conteúdo do Timer2 em 196d
     TIMSK2 = 0x01;   //Habilita interrupção do Timer2


} //end setup


//========================================================================================//
// --- Loop Infinito ---
void loop()
{
  
   volts();
   delay(200);


} //end loop


//========================================================================================//
// --- Desenvolvimento das Funções ---

//========================================================================================//
// --- Exibe o dado no display de catodo comum ---
int display_n(int num)
{
    int cathode;                               //armazena código BCD

    //-- Vetor para o código BCD --
    int SEGMENTO[10] = {0x3F,                  //BCD zero   '0'
                        0x06,                  //BCD um     '1'
                        0x5B,                  //BCD dois   '2'
                        0x4F,                  //BCD três   '3'
                        0x66,                  //BCD quatro '4'
                        0x6D,                  //BCD cinco  '5'
                        0x7D,                  //BCD seis   '6'
                        0x07,                  //BCD sete   '7'
                        0x7F,                  //BCD oito   '8'
                        0x67};                 //BCD nove   '9'

    cathode = SEGMENTO[num];                   //para retornar o cathode

    return(cathode);                           //retorna o número BCD

} //end display


//========================================================================================//
// --- Exibe o dado no display de catodo comum adicionando o ponto decimal ---
int display_dp(int num)                        //Adiciona o ponto decimal
{
    int cathode;                               //armazena código BCD

    //Vetor para o código BCD
    int SEGMENTO[10] = {0xBF,                  //BCD zero   '0.'
                        0x86,                  //BCD um     '1.'
                        0xDB,                  //BCD dois   '2.'
                        0xCF,                  //BCD três   '3.'
                        0xE6,                  //BCD quatro '4.'
                        0xEd,                  //BCD cinco  '5.'
                        0xFd,                  //BCD seis   '6.'
                        0x87,                  //BCD sete   '7.'
                        0xFF,                  //BCD oito   '8.'
                        0xE7};                 //BCD nove   '9.'

    cathode = SEGMENTO[num];                   //para retornar o cathode

    return(cathode);                           //retorna o número BCD

} //end display


//========================================================================================//
// --- Calcula Tensão em Volts ---
void volts()                                   //Função para cálculo da tensão em Volts
{
     store = average_volt();                   //Recebe o valor médio da tensão retornado pela função average_volts()
     t_Volts = (store*4000)/1024;              //Converte o valor para Volts

} //end celsius


//========================================================================================//
// --- Calcula a Média (Filtro Digital) ---
long average_volt()                            //Função que calcula a média de 100 leituras de tensão
{                                              //Garante maior precisão na medida
     unsigned char i;                          //Variável de iterações
     long volt_store = 0;                      //Variável local para armazenar o valor da tensão

     for(i=0; i<100; i++)                      //Somatório de 100 leituras
     {
              volt_store += analogRead(v_input);  //temp_store = temp_store + analogRead(v_input) (faz o somatório das 100 iterações)
     }

     return(volt_store/100);                   //retorna a média das iterações
     
} //end average_temp



/*

   Descrição: Mede a tensão na entrada A0.

   Projetou-se um divisor de tensão para medir tensões de 0 a 40V.

   O display é atualizado a cada estouro do TMR2
 
   
 Cálculos:

   Overflow do Timer2:
   
    T2_OVF = Timer2_cont x prescaler x ciclo de máquina
   
    Ciclo de máquina = 1/Fosc = 1/16E6 = 62,5ns = 62,5E-9s
   
    T2_OVF = (256 - 196) x 1024 x 62,5E-9 = 3,84ms 
   
   
   Divisor de tensão:
   
            R2
   Vo = --------- x Vi
         R2 + R1
         
             R2
   R1 = ( -------- x Vi ) - R2
             Vo
             
             
   Vi = 40V   Vo = 5V   R2(arb) = 27k
   
   
           27000
   R1 = ( ------- x 40 ) - 27000  =  189000 = 189k
             5
             
   Para R1, utiliza-se os valores comerciais de 150k e 39k ligados em série



*/
