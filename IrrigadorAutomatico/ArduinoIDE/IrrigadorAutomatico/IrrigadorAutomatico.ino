/* 

            Este código é copiado do professor. Ele tem a função de acionar uma válvula solenóide, que equivale a um relé, que irá liberar o fluxo de água para uma irrigação
     automática. Esta liberação ocorrerá a partir do momento que um ldr identificar que ficou noite, através da luminosidade. Da mesma forma, quando virar dia, a válvula
     também será acionada. 
            Este código é um exemplo simples de um controle de irrigação automático e pode ser melhorado, colocando um RTC externo ou projetando um interno através dos 
     timers. Ainda, o tempo ajustado para a válvula ficar ligada é de apenas 5s. Isso pode ser ajsutado para ficar um tempo maior. 

*/


// ========================================================================================================
// --- Mapeamento de Hardware ---
#define      ldr      A0                                  //entrada para sensor de luminosidade
#define      led      13                                  //saída para led auxiliar
#define      valve    11                                  //saída para controle de válvula solenoide


// ========================================================================================================
// --- Variáveis Globais ---
int        count_T2  = 0x00,                              //contador auxiliar para temporização
           timer     = 0x00;                              //variável de temporização

boolean    runSys    = 0x00,                              //flag para armar/desarmar sistema
           timeout   = 0x00;                              //flag auxiliar para temporizador


// ========================================================================================================
// --- Interrupção ---
ISR(TIMER2_OVF_vect)
{

    TCNT2 = 100;                                          //Reinicializa o registrador do Timer2
    count_T2++;                                           //Incrementa count_T2

    // -- Base de Tempo de 1 Segundo --
    if(count_T2 == 100)                                   //count_T2 igual a 100?
    {                                                     //Sim...
        count_T2 = 0x00;                                  //Reinicia
        if(timeout) timer++;                              //incrementa timer, se timeout estiver setada

        if(timer == 5)                                    //final da temporização?
        {                                                 //Sim...
            timer = 0x00;                                 //reinicia timer
            timeout = 0x00;                               //limpa timeout
            digitalWrite(valve, LOW);                     //desliga válvula
            digitalWrite(led,   LOW);                     //desliga led
            runSys = 0x01;                                //seta runSys
        
        } //end if timer
        
        
    } //end if count_T2
    
    

} //end ISR


// ========================================================================================================
// --- Configurações Iniciais ---
void setup()
{

    pinMode(ldr,  INPUT);                                 //Configura entrada para sensor de luminosidade
    pinMode(led, OUTPUT);                                 //Configura saída para led auxiliar
    pinMode(valve, OUTPUT);                               //Configura saída para controle de válvula solenoide


    TCCR2A = 0x00;                                        //Timer operando em modo normal
    TCCR2B = 0x07;                                        //Prescaler 1:1024
    TCNT2  = 100;                                         //Inicializa TCNT2 com 100
    TIMSK2 = 0x01;                                        //Habilita interrupção do Timer2
  
} //end setup


// ========================================================================================================
// --- Loop Infinito ---
void loop()
{
//||||||||||||||||||||||||||||||||||||||||||||||||||||||||
    if(analogRead(ldr) < 512 && !runSys)                  //anoiteceu e flag runSys limpa?
    {                                                     //Sim...
       timeout = 0x01;                                    //seta timeout
       digitalWrite(valve, HIGH);                         //liga válvula para irrigação
       digitalWrite(led,   HIGH);                         //liga led auxiliar

    } //end if ldr

    if(analogRead(ldr) > 550) runSys = 0x00;              //limpa runSys quando amanhecer
  
  
} //end loop
