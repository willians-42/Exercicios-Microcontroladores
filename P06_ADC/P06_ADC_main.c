//Faz um "bargraph" de LEDs com o potenciômetro

#include <xc.h>
#include "config_4520.h" //inclui os bits de configuração
#define _XTAL_FREQ 48000000 //Frequência do oscilador (48MHz)

void ADC_Init(){ //Função de Configuração do ADC

    ADCON0 = 0b00000001; // 00 (fixo), seleciona o canal AN0 (0000), GO/DONE=idle (0), e habilita o ADC (1)
    ADCON1 = 0b00001110; // 00 (fixo), Vref- é Vss (0), Vref+ é Vdd (0), configura somente AN0 como entrada analógica (1110)
    ADCON2 = 0b10101010; // justificado a direita (1), 0 (fixo), 12TAD (101) para 10 bits o mínimo é 11TAD, Tabela 19-1: Fosc/32 para 48MHz (010)
}

unsigned int ADC_Read(unsigned char channel){ //Leitura do canal analógico
    ADCON0 = (ADCON0 & 0b11000011) | (channel << 2); // Seleciona o novocanal
    __delay_us(20); // Aguarda o tempo de aquisição (consulte o datasheet para obter o valor adequado)
    GO_nDONE = 1; // Inicia a conversão
    while (GO_nDONE){
    // Aguarda a conclusão da conversão (enquanto Go/Done=1, o programa fica parado aqui)
    } 
    return ((ADRESH << 8) + ADRESL); // Retorna o resultado da conversão (bits mais significativos são deslocados 8 bits a esquerda e junta com os bits menos significativos para formar o valor total da conversão)
}

void main() { //Programa principal
    TRISAbits.RA0 = 1; // Configura o PORT RA0 como entrada (analógica)
    TRISB = 0x00; // Configura todas as portas B como saída (LEDs)
    ADC_Init(); // Inicializa o módulo ADC

    while(1) {
        unsigned int adc_value = ADC_Read(0); // Lê o valor do canal 0
        if(adc_value <= 128){ //Se o valor lido for <=128
            PORTB = 0b00000001;
        }
        if(adc_value > 128 && adc_value <= 256) {
            PORTB = 0b00000011;
        }
        if(adc_value > 256 && adc_value <= 384) {
            PORTB = 0b00000111;
        }
        if(adc_value > 384 && adc_value <= 512) {
            PORTB = 0b00001111;
        }
        if(adc_value > 512 && adc_value <= 640) {
            PORTB = 0b00011111;
        }
        if(adc_value > 640 && adc_value <= 768) {
            PORTB = 0b00111111;
        }
        if(adc_value > 768 && adc_value <= 896) {
            PORTB = 0b01111111;
        }
        if(adc_value > 896) {
            PORTB = 0b11111111;
        }
        __delay_ms(100); // Aguarda 100 ms para ler novamente
    }
}