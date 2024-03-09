/*
 Arquivo: E07_LCD_nome_main.c
 Autor: Willians Fernando de Oliveira (Prontuario: 3007316)
 Proposito: Deixar o primeiro nome do autor no centro do display LCD e desloca-lo a medida que os botoes A0 e A1 sao pressionados,
 respectivamente, para a esquerda e para a direita. (PIC18F4520)
 Criado em: 09 de Marco de 2024, 18:20
 */

#define _XTAL_FREQ 48000000 //define a frequência em 48MHz
#define TEMPO_DELAY 10
#include <xc.h>
#include "config_4520.h" //inclui os bits de configuração
#include "LCD_4520.h" //inclui biblioteca LCD

void main(void) {
    TRISD = 0x00; //RD0 a RD7 - saída para o LCD
    PORTD = 0x00; //Coloca portD em 0V.
    TRISA = 0b00000011;
    PORTA = 0b00000011; 
    lcd_inicia(0x28, 0x0f, 0x06); //lnicializa o display LCD alfanumérico com quatro linhas de dados.
/*
Configuração do display LCD:
(0x28), Tabela 8.2:
- Comunicação 4 vias
- Display com 2 linhas
- Matriz 8x5
(0x0F), Tabela 8.3
- Liga display
- Cursor piscante
(0x06), Tabela 8.2
- Desloca o cursor para a direita quando um caractere for inserido.
*/

    while (1){ // Loop infinito
        lcd_posicao (1,5);// Desloca o cursor para o meio da tela
        imprime_string_lcd("WILLIANS"); //Envia String para o Display LCD
        __delay_ms(TEMPO_DELAY);

        if (PORTAbits.RA0 == 0){
            // 0 desloca para a direita, 1 para a esquerda
            lcd_desloca_mensagem(0); // Desloca a string para a esquerda.
            __delay_ms(TEMPO_DELAY);
        }
         if (PORTAbits.RA1 == 0){
            // 0 desloca para a direita, 1 para a esquerda
            lcd_desloca_mensagem(1); // Desloca a string para a esquerda.
            __delay_ms(TEMPO_DELAY);
        }
    }
    return;
}

