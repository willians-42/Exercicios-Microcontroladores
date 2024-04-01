/*
 Arquivo: E13_relogio_main.c
 Autores: Willians Fernando de Oliveira (3007316) / Matheus José Ferreira Borelli (3012328)
 Proposito: Fazer um relógio digital (PIC18F4520);
    • O valor atual do relógio deve ser exibido na segunda linha do display LCD no formato HH:MM:SS;
    • O programa funciona em looping;
    • Usar o formato de 24horas.
 Criado em: 01 de Abril de 2024, 10:30
 */

#define _XTAL_FREQ 48000000 //define a frequência em 48MHz
#include <xc.h>
#include "config_4520.h" //inclui os bits de configuração
#include "LCD_4520.h" //inclui a biblioteca do LCD
#include <stdio.h> 

// Prototipo de funcoes
void inicializa(void);
void exibe_tempo(void);

// Variaveis globais
volatile unsigned int segundos = 0;
volatile unsigned int minutos = 0;
volatile unsigned int horas = 0;

// Funcao Principal
void main(void) {

    inicializa();

    while(1) { //Repete indefinidamente
        exibe_tempo();
        if(PIR1bits.TMR1IF == 1) { //Se houve estouro do Timer1 (flag acionada), então:
            segundos++; //incrementa os segundos
            if(segundos > 59) { //se os segundos ultrapassarem 59, reinicia para 0 e incrementa os minutos
                segundos = 0;
                minutos++;
                if(minutos > 59) { //se os minutos ultrapassarem 59, reinicia para 0 e incrementa as horas
                    minutos = 0;
                    horas++;
                    if(horas > 23) { //se as horas ultrapassarem 23, reinicia para 0
                        horas = 0;
                    }
                }
            }
    
            PIR1bits.TMR1IF = 0; //Apaga a Flag do Timer1 (reinicia)
            TMR1H =  0x3C; //Carga inicial Timer1 (Mais significativo) 
            TMR1L = 0xB0; //Carga inicial Timer1 (Menos significativo)
        }
    }
}

void inicializa(void){
     //Configuração do LCD -----------------
    TRISD = 0x00;
    PORTD = 0x00;  
    lcd_inicia(0x28, 0x0f, 0x06); //lnicializa o display LCD alfanumérico com quatro linhas de dados.

    /*
    Configuração do Timer 1:
    • O TIMER1 do PIC18F4520 é um temporizador de 16 bits, o que significa que ele pode contar de 0 a 65535 (2^16 - 1).
    • Utilizando um oscilador externo de 0.4 MHz com prescaler de 1:8, a frequência efetiva que o TIMER1 vê é 0.4 MHz / 8 = 0.05 MHz ou 50 kHz.
    • Para calcular a carga inicial, é necessário subtrair o tempo desejado do tempo estouro e, em seguida, converter de volta para uma contagem:
         Carga inicial = Contagem máxima - (Tempo desejado * Frequência efetiva)
         Carga inicial = 65536 - (1 s * 50 * 10^3) = 65536 - 50000 = 15536
    • 15536 (decimal) equivale a 0x3CB0 (hexadecimal)
    • Com isso, podemos atribuir esses valores aos registradores abaixo:
        TMR1H =  0x3C; //Carga inicial Timer1 (Mais significativo)
        TMR1L = 0xB0; //Carga inicial Timer1 (Menos significativo)
        T1CON = 0b10110011; 
            • bit | Estado | Propósito
                7 |    1   | Permite leitura/escrita do Timer1 com uma operacao de 16 bits
                6 |    0   | Oscilador de outra fonte
              5-4 |   1-1  | Prescalar 1:8
                3 |    0   | Desabilita oscilador do Timer1
                2 |    0   | Sincronizacao com oscilador externo
                1 |    1   | Oscilador externo do pino RCO/T1OSO/T13CKI
                0 |    1   | Habilita Timer1
    */
    
    T1CON = 0b10110011; 
    TMR1H =  0x3C; 
    TMR1L = 0xB0; 
    PIR1bits.TMR1IF = 0; //Apaga a Flag do Timer1 
}

void exibe_tempo(){
    lcd_LD_cursor(0); // inibe exibicao do cursor
    lcd_posicao(1, 1); // desloca o cursor para a posicao determinada
    imprime_string_lcd("E13_relogio");
    char buffer[10]; // variavel temporaria para armazenar texto
    sprintf(buffer,"%02d:%02d:%02d", horas, minutos, segundos);
    lcd_LD_cursor(0); 
    lcd_posicao(2, 1); // desloca o cursor para a posicao determinada
    imprime_string_lcd(buffer);
}
