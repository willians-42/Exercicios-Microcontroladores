//Pisca todos os LEDs conectados no PORTB com interrupção;
#define _XTAL_FREQ 48000000 //define a frequência em 48MHz
#include <xc.h>
#include "config_4520.h" //inclui os bits de configuração

void interrompe(void);

void __interrupt() interrompe(void){ //*Rotina da interrupção chamada interrompe
    if(INTCONbits.INT0IF == 1){ //*Se houver interrupção, flag = 1, faça:
        INTCONbits.INT0IF = 0; //*Reseta Bit de sinalização (flag) de interrupção externa INT0;
        PORTB = 0b10101010; //*LEDs acendem de forma intercalada
    }
}

void main(void) {
    INTCONbits.GIE = 1; //*Habilitação geral das interrupções;
    INTCONbits.INT0IE = 1; //*Habilita Interrupção INT0 externa;
    INTCONbits.INT0IF = 0; //*Reseta Bit de sinalização (flag) de interrupção externa INT0;
    INTCON2bits.INTEDG0 = 0;//*Habilita Interrupção externa INT0 por borda de descida (botão vai de 1 para 0);
    INTCON2bits.RBPU = 1; //*Desabilita resistores de pull-up do PORTB (já temos o nosso no circuito)

    ADCON1 = 0b00001111; //Declara todos os pinos como I/O digitais
    TRISB = 0b00000001; //**configura os pinos RB7-RB1 como saída digital e RB0 como entrada digital
    PORTB = 0b00000000; //seta todos os pinos do PORTB em nível baixo, 0
    while(1){ //Repete indefinidamente
        __delay_ms(500); //delay de 0,5s
        PORTB = ~PORTB; //inverte o estado dos pinos do PORTB
    }
return;
}

