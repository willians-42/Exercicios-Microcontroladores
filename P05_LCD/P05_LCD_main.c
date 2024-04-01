//Teste do display LCD;

#define _XTAL_FREQ 48000000 //define a frequência em 48MHz
#include <xc.h>
#include "config_4520.h" //inclui os bits de configuração
#include "LCD_4520.h" //inclui biblioteca LCD

void main(void) {
    TRISD = 0x00; //RD0 a RD7 - saída para o LCD
    PORTD = 0x00; //Coloca portD em 0V.
    lcd_inicia(0x28, 0x0f, 0x06); //lnicializa o display LCD alfanumérico com quatrolinhas de dados.
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
    while (1) {// Looping infinito

        imprime_string_lcd("IFSP"); //Envia String para o Display LCD
        __delay_ms(1000);
        lcd_posicao (2,7);// Desloca o cursor para a sétima coluna da segunda linha.
        lcd_escreve_dado('P'); //Imprime um caractere ASCII no display.
        lcd_escreve_dado('I'); //Imprime um caractere ASCII no d1splay.
        lcd_escreve_dado('C'); //Imprime um caractere ASCII no display.
        __delay_ms(1000);
        lcd_desloca_mensagem(1); // Desloca a mensagem para a esquerda.
        __delay_ms(1000);
        lcd_desloca_mensagem(0); // Desloca a mensagem para a direita.
        __delay_ms(1000);
        lcd_LD_cursor(0); // Desliga o cursor.
        __delay_ms(1000);
        lcd_LD_cursor(1); // Desliga o display.
        __delay_ms(1000);
        lcd_LD_cursor(2); // Liga o display com o cursor piscante.
        __delay_ms(1000);
        lcd_desloca_cursor(0); // Desloca o cursor para a direita.
        __delay_ms(1000);
        lcd_desloca_cursor(1); // Desloca o cursor para a esquerda.
        __delay_ms(1000);
        lcd_limpa_tela(); // Limpa a tela do display e posiciona o cursor na linha um e coluna um.
        __delay_ms(1000);
    }
}
