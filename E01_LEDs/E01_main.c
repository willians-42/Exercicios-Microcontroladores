/*
 Arquivo: E01_main.c
 Autor: Willians Fernando de Oliveira (Prontuario: 3007316)
 Proposito: Piscar LEDs conectados aos pinos B6 e B7 de forma alternada com intervalo de 400ms (PIC18F4520)
 Criado em: 15 de Fevereiro de 2024, 19:38
 */

#include <xc.h>
#include "config_4520.h" // Inclusao do cabecalho com os bits de configuracao
#define _XTAL_FREQ 20000000 // Define a frequência em 20MHz (mesma frequência do cristal que estará no circuito)

void main(void) {
    /* 
    Configuracao dos pinos B6 e B7 como saídas digitais:
    Utilizado o comando TRIS, e necessario especificar qual o grupo de I/Os (A ~ E), no caso, RB, e qual o bit, no caso, 0;
    */
    TRISBbits.RB6 = 0;
    TRISBbits.RB7 = 0;
   
    while(1) { // Loop infinito
        /*
        Configuracao dos pinos B6 e B7 como nível baixo (0 ou 0V) ou como nível alto (1 ou 5V), ou seja, respectivamente, LED apagado e LED aceso:
        Utilizado o comando PORT, e necessario especificar qual o grupo de I/Os (A ~ E), no caso, RB, e qual o bit, no caso, 0 ou 1; 
        */
        PORTBbits.RB6 = 1; 
        PORTBbits.RB7 = 0; 
        __delay_ms(400);
        PORTBbits.RB6 = 0;
        PORTBbits.RB7 = 1;
        __delay_ms(400);
    }
    return;
}
