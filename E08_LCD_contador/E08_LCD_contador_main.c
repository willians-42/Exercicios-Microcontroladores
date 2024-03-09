/*
 Arquivo: E08_LCD_contador_main.c
 Autor: Willians Fernando de Oliveira (Prontuario: 3007316)
 Proposito: Exibir um contador de 0 a 9 na primeira coluna da segunda linha em um display LCD (PIC18F4520)
 Criado em: 09 de Marco de 2024, 19:20
 */

#define _XTAL_FREQ 48000000 //define a frequência em 48MHz
#include <xc.h>
#include "config_4520.h" //inclui os bits de configuração
#include "LCD_4520.h" //inclui biblioteca LCD
#include <stdio.h> //Biblioteca para uso da função sprintf
#define TEMPO_DELAY 500

void main(void) {
    TRISD = 0x00; //RD0 a RD7 - saída para o LCD
    PORTD = 0x00; //Coloca portD em 0V.
    char texto[20]; // Tamanho da string suficientemente grande para armazenar o inteiro convertido
    lcd_inicia(0x28, 0x0f, 0x06); //lnicializa o display LCD alfanumérico com quatro linhas de dados.

    while (1){ // Loop infinito
        for(int contador = 0;contador < 10; contador++){
            sprintf(texto, "%d", contador); //Converte a variável inteira contador em uma string chamada texto
            lcd_posicao (2,1); // Desloca o cursor para a primeira coluna da segunda linha.
            imprime_string_lcd(texto); // Exibe numero na posicao determinada no display LCD
            __delay_ms(TEMPO_DELAY);
        }
    }
}