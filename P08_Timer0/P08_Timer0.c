//Inverte o estado dos LEDs a cada 1 segundo usando Timer 0;
#define _XTAL_FREQ 48000000 //define a frequência em 48MHz
#include <xc.h>
#include "config_4520.h" //inclui os bits de configuração

void main(void) {
    //Configuração dos LEDs -----------------
    ADCON1 = 0b00001111; //Declara todos os pinos como I/O digitais
    TRISB = 0b00000001; //configura os pinos RB7-RB1 como saída digital e RB0 como entrada digital
    PORTB = 0b00000000; //seta todos os pinos do PORTB em nível baixo, 0//Configuração do Timer 0 ---------------
    T0CON = 0b00000111; //Timer0 stop | 16- bit | Clock interno | Low-to-High | Prescaler ON | 256
    TMR0H = 0x48; //Carga inicial Timer0 (Mais significativo)
    TMR0L = 0xE5; //Carga inicial Timer0 (Menos significativo)
    INTCONbits.TMR0IF = 0; //Apaga a Flag do Timer0 (veja sobre interrupção)
    T0CONbits.TMR0ON = 1; //Timer0 on

    while(1) { //Repete indefinidamente
        if(INTCONbits.TMR0IF == 1) { //Se houve estouro do Timer0 (flag acionada), então:
            PORTB = ~PORTB; //inverte o estado dos pinos do PORTB a todo estouro do Timer0
            INTCONbits.TMR0IF = 0; //Apaga a Flag do Timer0 (reinicia)
            TMR0H = 0x48; //Carga inicial Timer0 (Mais significativo)
            TMR0L = 0xE5; //Carga inicial Timer0 (Menos significativo)
        }
    }
return;
}