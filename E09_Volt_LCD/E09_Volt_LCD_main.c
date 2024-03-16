/*
 Arquivo: E09_Volt_LCD_main.c
 Autor: Willians Fernando de Oliveira (Prontuario: 3007316)
 Proposito: Fazer um voltímetro para exibir o valor de entrada do canal AN0 no display LCD; Na linha 1 será exibido: Tensão: X,XXX V (PIC18F4520)
 Criado em: 16 de Marco de 2024, 18:15
 */

#define _XTAL_FREQ 48000000 //Frequência do oscilador (48MHz)
#define TEMPO_DELAY 100 // tempo delay em ms
#include <xc.h>
#include "config_4520.h" //inclui os bits de configuração
#include "LCD_4520.h" // configuracoes de exibicao do display
#include <stdio.h>

void ADC_Init(){ //Função de Configuração do ADC
    ADCON0 = 0b00000001; // 00 (fixo), seleciona o canal AN0 (0000), GO/DONE=idle (0), e habilita o ADC (1)
    ADCON1 = 0b00001110; // 00 (fixo), Vref- é Vss (0), Vref+ é Vdd (0), configura somente AN0 como entrada analógica (1110)
    ADCON2 = 0b10101010; // justificado a direita (1), 0 (fixo), 12TAD (101) para 10 bits o mínimo é 11TAD, Tabela 19-1: Fosc/32 para 48MHz (010)
}

unsigned int ADC_Read(unsigned char channel) { //Leitura do canal analógico
    ADCON0 = (ADCON0 & 0b11000011) | (channel << 2); // Seleciona o novocanal
    __delay_us(20); // Aguarda o tempo de aquisição (consulte o datasheet para obter o valor adequado)
    GO_nDONE = 1; // Inicia a conversão
    while (GO_nDONE){
    // Aguarda a conclusão da conversão (enquanto Go/Done=1, o programa fica parado aqui)
    } 
    return ((ADRESH << 8) + ADRESL); // Retorna o resultado da conversão (bits mais significativos são deslocados 8 bits a esquerda e junta com os bits menos significativos para formar o valor total da conversão)
}

void exibe_mensagem(unsigned int adc_value) {
    float tensao = (adc_value * 5.0)/1023.0; // calculo do valor de tensao
    char str[10]; // variavel de texto para armazenar valor de tensao
    sprintf(str,"Tensao: %.3f V",tensao); // converte valor calculado para uma string
    lcd_LD_cursor(0); // inibe a exibicao do cursor
    lcd_posicao (1,1);// desloca o cursor para a posicao determinada
    imprime_string_lcd(str); //envia String para o Display LCD 
    __delay_ms(TEMPO_DELAY); // aguarda a quantidade de tempo determinada para ler o valor novamente
}

void main() { //Programa principal
    TRISAbits.RA0 = 1; // Configura o PORT RA0 como entrada (analógica)
    ADC_Init(); // Inicializa o módulo ADC
    lcd_inicia(0x28, 0x0f, 0x06); //lnicializa o display LCD alfanumérico com quatro linhas de dados.

    while(1) {
        unsigned int adc_value = ADC_Read(0); // Lê o valor do canal 0
        exibe_mensagem(adc_value); // Exibe a tensao na tela LCD
    }
} 