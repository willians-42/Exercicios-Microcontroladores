/*
 Arquivo: E02_main.c
 Autor: Willians Fernando de Oliveira (Prontuario: 3007316)
 Proposito: Programacao de Semáforo de Veículos para uma via simples (PIC18F4520)
 Criado em: 22 de Fevereiro de 2024, 19:38
 */

#include <xc.h>
#include "config_4520.h" // Inclusao do cabecalho com os bits de configuracao

#define _XTAL_FREQ 20000000 // Define a frequência em 20MHz (mesma frequência do cristal que estará no circuito)
#define intervaloTempo 2500

void main(void) {
    
     /* 
    Configuracao dos pinos D5, D6 e D7 como saídas digitais:
    Utilizado o comando TRIS, e necessario especificar qual o grupo de I/Os (A ~ E), no caso, RD, e qual o bit, no caso, 0;
    */
    TRISDbits.RD5 = 0;
    TRISDbits.RD6 = 0;
    TRISDbits.RD7 = 0;
   
    while(1) { // Loop infinito
        
        // LED vermelho aceso, restante apagado
        PORTDbits.RD5 = 0; 
        PORTDbits.RD6 = 0; 
        PORTDbits.RD7 = 1; 
        __delay_ms(intervaloTempo);

        // LED amarelo aceso, restante apagado
        PORTDbits.RD5 = 0; 
        PORTDbits.RD6 = 1; 
        PORTDbits.RD7 = 0; 
        __delay_ms(intervaloTempo/2);

       // LED verde aceso, restante apagado
        PORTDbits.RD5 = 1; 
        PORTDbits.RD6 = 0; 
        PORTDbits.RD7 = 0; 
        __delay_ms(intervaloTempo);
    }
    return;
}
