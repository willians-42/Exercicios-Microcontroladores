/*
 Arquivo: E05_contador_main.c
 Autor: Willians Fernando de Oliveira (Prontuario: 3007316)
 Proposito: Programacao de um contador de 0 a 9 com intervalo de 500ms para ser exibido em um display de 7 segmentos, 
 inicialmente o display exibe 0 e toda vez que o botão A1 for pressionado, inicia a contagem . (PIC18F4520)
 Criado em: 02 de Marco de 2024, 17:40
 */

#include <xc.h>
#include "config_4520.h" // Inclui os bits de configuracao
#define _XTAL_FREQ 20000000 // Define a frequencia de operacao em 20 MHz

void main(void) {
    // hgfedcba - ordem de ativacao do display
    unsigned char configDisplay[10] = {0b00111111,0b00000110,0b01011011,0b01001111, 0b01100110,0b01101101,0b01111101, 
      0b00000111,0b01111111, 0b01101111}; // vetor com configuracao de exibicao de numeros no display - 0 a 9

    TRISD = 0x00; // configura PORTD como saída digital
    TRISAbits.RA1 = 1; // configura a porta A1 como entrada
    PORTD = 0X00; // seta todas as portas D em estado 0

        while(1){ // repete indefinidamente
            PORTD = configDisplay[0]; // exibe continuamente 0 no display
            if (PORTAbits.RA1 == 0){ // caso o botao conectado em A1 seja pressionado, faca:
                __delay_ms(20);
                for (int i = 1; i <= 9; i++){ // loop para percorrer elementos do vetor com os numeros a ser exibidos
                    PORTD = configDisplay[i]; // exibe numeros de 1 a 9
                    __delay_ms(500); // espera 0.5 segundo
                }
            }
        }
    return;
}