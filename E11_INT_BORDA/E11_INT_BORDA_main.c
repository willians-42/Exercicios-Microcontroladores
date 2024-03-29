/*
 Arquivo: E11_INT_BORDA_main.c
 Autor: Willians Fernando de Oliveira (Prontuario: 3007316)
 Proposito: Fazer um contador de pessoas para um dos portões de um estádio de futebol (PIC18F4520).
    •A ideia é contar apenas as pessoas que entraram pelo portão antes do início do jogo;
    •O sensor vai de 0 para 1 quando uma pessoa entra. Assim que a pessoa passa pelo portão, o sensor volta para 0. Só entra uma pessoa por vez;
    •Utilize a interrupção por mudança de estado (KBI3) para fazer este código;
    •Assim que o jogo é iniciado, uma pessoa da organização vai verificar a contagem final no display LCD.
 Criado em: 29 de Marco de 2024, 18:30
 */

#define _XTAL_FREQ 48000000 // define a frequência em 48MHZ

#include <xc.h>
#include "config_4520.h" //inclui os bits de configuração
#include "LCD_4520.h" // biblioteca LCD
#include <stdio.h> // biblioteca padrao C

// Prototipo das funcoes 
void interrompe();
void inicializacao();
void exibe_mensagem();

// Variavel global para armazenar contagem
volatile unsigned int contador = 0;

// Funcao principal
void main(void) {
    inicializacao();

    while (1) { // Repete indefinidamente
        exibe_mensagem(contador);
    }
    return;
}

//*Rotina da interrupcão chamada interrompe
void __interrupt() interrompe(void) { 
    if (INTCONbits.RBIF) {  //*Se houver interrupcão por mudanca de estado, faca:
        INTCONbits.RBIF = 0; //*Reseta Bit de sinalizacão (flag) da interrupcão por mudanca de estado;
        counter++; //*Adiciona uma unidade a variavel global de contagem
    }
}

// Funcao para exibir valores na tela do display LCD
void exibe_mensagem(volatile unsigned int cc) {
    char str[30];                 // variavel de texto para armazenar valor da contagem
    sprintf(str, "cont: %d", cc); // converte valor calculado para uma string
    lcd_LD_cursor(0);             // inibe a exibicao do cursor
    lcd_posicao(1, 1);            // desloca o cursor para a posicao determinada
    imprime_string_lcd(str);      // envia String para o Display LCD
    __delay_ms(100);                // aguarda a quantidade de tempo determinada para ler o valor novamente
}

// Configuracoes 
void inicializacao(void){
    // INTCON
    INTCONbits.GIE = 1; //*Habilitação geral das interrupções;
    INTCONbits.RBIE = 1; //Habilita Interrupção por mudança de estado;
    INTCONbits.RBIF = 0; // Bit de sinalização de interrupção por mudança de estado
    // INTCON 2
    INTCON2bits.RBPU = 1;    //*Desabilita resistores de pull-up dO PORTB (já temos o nosso no circuito)
    INTCON2bits.RBIP = 1; // Alta prioridade da interrupção por mudança de estado(0 para baixa prioridade).
    //PINOS
    TRISB = 0b10000000;  //*configura o pino RB7 como entrada digital
    // DISPLAY LCD
    TRISD = 0x00;
    PORTD = 0x00;
    lcd_inicia(0x28, 0x0f, 0x06); //lnicializa o display LCD alfanumérico com quatro linhas de dados.
}
