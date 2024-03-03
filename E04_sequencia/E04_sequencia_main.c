/*
 Arquivo: E04_sequencia_main.c
 Autor: Willians Fernando de Oliveira (Prontuario: 3007316)
 Proposito: Acionar LEDs de RB0 a RB7 em sequencia direta e depois inversa com intervalos de 1 segundo atraves do 
 acionamento do botao conectado em RA0, no inicio e no fim dos ciclos os LEDs permanecem apagados (PIC18F4520)
 Criado em: 03 de Marco de 2024, 09:35
 */

#include <xc.h>
#include "config_4520.h" // inclui arquivo com bits de configuracao
#define _XTAL_FREQ 20000000 //define a frequência em 20MHz
#define TEMPO_DELAY 500 // tempo do delay 

void main(void) {
    
    TRISB = 0x00; //configura todos os pinos do PORTB como saída digital
    TRISAbits.RA0 = 1;//configura pino RA0 como input (entrada)
    PORTB = 0X00;  //seta todos os pinos do PORTB em nível baixo, 0
    PORTAbits.RA0 = 1; // seta pino RA0 em nivel alto, 1

    while(1){ //Repete indefinidamente
        PORTB = 0X00; //seta todos os pinos do PORTB em nível baixo, 0
        __delay_ms(TEMPO_DELAY/40);
        if (PORTAbits.RA0 == 0){//Se o pino RA0 == 0, faça:
            __delay_ms(TEMPO_DELAY/40);
            for(int i = 0; i <= 7; i++){ //Conta de 0 a 7,
                PORTB = (1 << i); //Coloca o bit 1 no PORTB deslocado 'i' posições à esquerda
                __delay_ms(TEMPO_DELAY);//intervalo de 1 segundo
            }
            for(int i = 6;i >= 0; i--){ //Conta de 6 a 0, passo 1
                PORTB = (1 << i); //Coloca o bit 1 no PORTB deslocado 'i' posições à esquerda
                __delay_ms(TEMPO_DELAY);//intervalo de 1 segundo
            }
        }
    }
    return;
}
