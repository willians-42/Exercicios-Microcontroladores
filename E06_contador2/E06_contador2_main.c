/*
 Arquivo: E06_contador2_main.c
 Autor: Willians Fernando de Oliveira (Prontuario: 3007316)
 Proposito: Fazer um contador de 00 a 59 com intervalo de 500ms para ser exibido no display de 7 segmentos; 
 Inicialmente o display exibe 00 e toda vez que o botão A1 é pressionado, inicia a contagem; (PIC18F4520)
 Criado em: 02 de Marco de 2024, 19:30
 */

#include <xc.h>
#include "config_4520.h" // inclui os bits de configuracao
#define _XTAL_FREQ 20000000 // define a frequencia de operacao em 20 MHz
#define TEMPO_DELAY 500 // tempo do delay

void main(void) {
    // *** ATENCAO - PORTAS CONECTADAS NO DISPLAY EM ORDEM INVERSA EM RELACAO AO PDF DA AULA ***
    // hgfedcba - ordem de ativacao do display
    unsigned char configDisplay[10] = {0b00111111, 0b00000110, 0b01011011, 0b01001111, 0b01100110, 
    0b01101101, 0b01111101, 0b00000111, 0b01111111, 0b01101111}; // vetor com configuracao de exibicao de numeros no display - 0 a 9
    unsigned char *ponteiroConfigDisplay; // ponteiro
    ponteiroConfigDisplay = &configDisplay; // aponta para vetor de configuracao do display

    TRISC = 0x00; // configura portas C como saída digital
    TRISD = 0x00; // configura portas D como saída digital
    TRISAbits.RA1 = 1; // configura a porta A1 como entrada digital
    PORTC = 0X00; // seta todas as portas C em estado 0
    PORTD = 0X00; // seta todas as portas D em estado 0

        while(1){ // repete indefinidamente
            PORTD = *(ponteiroConfigDisplay+0); // exibe continuamente 0 no display 1
            PORTC = *(ponteiroConfigDisplay+0); // exibe continuamente 0 no display 2
            if (PORTAbits.RA1 == 0){ // caso o botao conectado em A1 seja pressionado, faca:
                __delay_ms(20);
                // display 1
                for (int i = 0; i <= 5; i++){ // loop para percorrer elementos do vetor com os numeros a ser exibidos no display 1
                    PORTD = *(ponteiroConfigDisplay+i); // exibe numeros de 0 a 5
                    // display 2
                    for (int j = 0; j <= 9; j++){ // loop para percorrer elementos do vetor com os numeros a ser exibidos no display 2
                        PORTC = *(ponteiroConfigDisplay+j); // exibe numeros de 0 a 9
                        __delay_ms(TEMPO_DELAY); // espera a quantidade de tempo especificada em TEMPO_DELAY
                    }
                    PORTC = *(ponteiroConfigDisplay+0);
                }
            }
        }
    return;
}