//Usa o modo Capture como um frequencímetro
#define _XTAL_FREQ 48000000 // Frequência do oscilador (48MHz)
#include <xc.h>
#include "config_4520.h" // Inclui os bits de configuração
#include "LCD_4520.h" // Inclui biblioteca LCD
#include <stdio.h> // Biblioteca para uso da função sprintf
void main() {
    unsigned long signal_period,data1,data2; //Positivos com 32 bits
    char frequency_Hz[20]; //Positivos e negativos com 8 bits
    float Frequency; //32 bits com 6 digitos de precisão
    //Configuração do LCD
    TRISD = 0x00; //RD0 a RD7 - saída para o LCD
    PORTD = 0x00; //Coloca portD em 0V - saída para o LCD
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
    imprime_string_lcd("Frequencia (Hz)"); //Envia String para o Display LCD
    //Configuração do CCP1
    TRISCbits.TRISC2=1; //Seta pino RC2 como entrada (CCP1)
    CCP1CON = 0b00000101; //Habilita modo de Captura na borda de subida
    CCPR1=0; //Registrador que armazena o valor do módulo CCP1 é zerado
    PIE1bits.CCP1IE=1; //Habilita interrupção do módulo CCP1
    PIR1bits.CCP1IF=0; //Flag de interrupção do CCP1 é zerado
    //Configuração do Timer 1 (incrementa a cada 0,083us)
    T1CON = 0b10000000; //16 bit | 1:1 Prescale | Internal clock | Timer OFF
    TMR1=0; //Registrador que armazena o valor do Timer1 é zerado
    TMR1IF=0; //Flag de interrupção do Timer 1 é zerado
    TMR1ON=1; //Timer1 ON
    while(1) {
        while(!(PIR1bits.CCP1IF)); //Programa fica travado aqui enquanto CCP1IF = 0 (não há interrupção)
            PIR1bits.CCP1IF=0; //Quando há interrupção, ou seja, borda de subida, zera a flag
            data1 = CCPR1; //Copia a contagem da primeira borda de subida detectada
            while(!(PIR1bits.CCP1IF)); //Programa fica travado aqui enquanto CCP1IF = 0 (não há interrupção)
                PIR1bits.CCP1IF=0; //Quando há interrupção, ou seja, borda de subida, zera a flag
                data2 = CCPR1; //Copia a contagem da segunda borda de subida detectada
                if(data1 < data2) //Se a contagem da primeira borda é menor que a contagem da segunda borda
            {
            signal_period = data2 - data1; //Calcula o período do sinal (sem considerar o Timer) 
            /*frequencia = 1/Periodo, mas neste caso o incremento do timer é a cada 0,083us, ou seja, f = (1/T)/0,083u ou f = (1/T)*12M */
            Frequency = (1 / (float)signal_period)*12000000;//Calcula a frequência 
            /* o valor de Frequency será formatado como um número de ponto flutuante (%f) com três casas decimais (%.3f) */
            sprintf(frequency_Hz, "%.3f ", Frequency);
            lcd_posicao (2,1); //Desloca o cursor para a primeira coluna da segunda linha
            imprime_string_lcd(frequency_Hz); //Envia para o LCD
        }
        TMR1=0; //Registrador que armazena o valor do Timer1 é zerado
    }
}
