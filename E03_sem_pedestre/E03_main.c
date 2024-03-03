/*
 Arquivo: E03_main.c
 Autor: Willians Fernando de Oliveira (Prontuario: 3007316)
 Proposito: Programacao de Semáforo de Veículos para uma via simples com botao de pedestre (PIC18F4520)
 Criado em: 23 de Fevereiro de 2024, 10:00
 */

#include <xc.h>
#include "config_4520.h" // Inclusao do cabecalho com os bits de configuracao

#define _XTAL_FREQ 20000000 // Define a frequência em 20MHz (mesma frequência do cristal que estará no circuito)
#define TIME_INTERVAL 3000
#define PED_BUTTON PORTDbits.RD0 // botao pedestre
#define PED_GREEN PORTDbits.RD2 // verde pedestre
#define PED_RED PORTDbits.RD3 // vermelho pedestre
#define CAR_GREEN PORTDbits.RD5 // verde carro
#define CAR_YELLOW PORTDbits.RD6 // amarelo carro
#define CAR_RED PORTDbits.RD7 // vermelho carro

void main(void) {
    
     /* 
    Configuracao dos pinos D2, D3, D5, D6 e D7 como saídas digitais (outputS) e pino D0 como entrada digital (input):
    Utilizado o comando TRIS, e necessario especificar qual o grupo de I/Os (A ~ E), no caso, RD, e qual o bit, no caso, 0 e 1;
    */
    TRISD = 0b00000001;
    PORTD = 0b00000000;
   
    while(1) { // Loop infinito (repete indefinidamente)
        
        if(PED_BUTTON == 0){ // caso botao nao apertado, faca:

            // 
            PED_GREEN = 0; 
            PED_RED = 1; 
            CAR_GREEN = 1; 
            CAR_YELLOW = 0; 
            CAR_RED = 0; 
            __delay_ms(TIME_INTERVAL/30); 

        } else {
            
            PED_GREEN = 0; 
            PED_RED = 1; 
            CAR_GREEN = 0; 
            CAR_YELLOW = 1; 
            CAR_RED = 0; 
            __delay_ms(TIME_INTERVAL);

            PED_GREEN = 1; 
            PED_RED = 0; 
            CAR_GREEN = 0; 
            CAR_YELLOW = 0; 
            CAR_RED = 1; 
            __delay_ms(TIME_INTERVAL);

            PED_GREEN = 0; 
            for (int cont = 0; cont < 20; cont++){
                PED_RED = !PED_RED;
                __delay_ms(100);
            }
            PED_RED = 1;
            CAR_GREEN = 1;
            CAR_YELLOW = 0; 
            CAR_RED = 0; 
            __delay_ms(TIME_INTERVAL);
        }
    }
    return;
}
