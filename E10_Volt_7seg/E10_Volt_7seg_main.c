/*
 Arquivo: E10_Volt_7seg_main.c
 Autor: Willians Fernando de Oliveira (Prontuario: 3007316)
 Proposito: Fazer um voltímetro para exibir o valor de entrada do canal AN0 nos dois displays de 7 segmentos;
 No display da esquerda será o valor inteiro e no display da direita o valor decimal (PIC18F4520)
 Criado em: 16 de Marco de 2024, 19:30
 */

#define _XTAL_FREQ 48000000 //Frequência do oscilador (48MHz)
#define TEMPO_DELAY 100 // tempo delay em ms
#include <xc.h>
#include "config_4520.h" //inclui os bits de configuração
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
       // *** ATENCAO - PORTAS CONECTADAS NO DISPLAY EM ORDEM INVERSA EM RELACAO AO PDF DA AULA ***
    // hgfedcba - ordem de ativacao do display
    unsigned char configDisplay[10] = {0b00111111, 0b00000110, 0b01011011, 0b01001111, 0b01100110, 
    0b01101101, 0b01111101, 0b00000111, 0b01111111, 0b01101111}; // vetor com configuracao de exibicao de numeros no display - 0 a 9
    float tensao = (adc_value * 5.0)/1023.0; // calculo do valor de tensao
    unsigned int inteira = tensao; // parte inteira do numero real 
    unsigned int decimal = (tensao - inteira)*10; //parte decimal do numero real
    PORTD = configDisplay[inteira]; // exibe parte inteira do numero no primeiro display
    PORTC = configDisplay[decimal]; // exibe parte decimal do numero no  segundo display
    __delay_ms(TEMPO_DELAY); // aguarda a quantidade de tempo determinada para ler o valor novamente
}

void main() { //Programa principal
    TRISC = 0x00; // configura portas C como saída digital
    TRISD = 0x00; // configura portas D como saída digital
    PORTC = 0X00; // seta todas as portas C em estado 0
    PORTD = 0X00; // seta todas as portas D em estado 0
    TRISAbits.RA0 = 1; // Configura o PORT RA0 como entrada (analógica)
    ADC_Init(); // Inicializa o módulo ADC
  
    while(1) {
        unsigned int adc_value = ADC_Read(0); // Lê o valor do canal 0
        exibe_mensagem(adc_value);
    }
} 