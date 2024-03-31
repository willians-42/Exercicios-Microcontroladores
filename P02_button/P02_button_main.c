// O botao A0 ligara todos os LEDs do PORTB
// O botao A1 desligara todos os LEDs do PORTB

#define _XTAL_FREQ 20000000 // define a frequencia em 20MHz
#include <xc.h>
#include "config_4520.h"

void main(void) {
    TRISB = 0x00; // todos os pinos como saida digital
    PORTB = 0x00; // seta todos os pinos em nivel baixo(0)
    TRISAbits.RA0 = 1; // seta pino A0 como entrada
    TRISAbits.RA1 = 1; // seta pino A1 como entrada
    unsigned int estado = 0; // variavel pra indicar o estado dos botoes
    
    while(1){
        if (PORTAbits.RA0 == 0 && estado == 0){ // caso botao A0 pressionado, liga os LEDs
            estado = 1; // interrompe forcadamente o loop
            PORTB = 0b11111111;
            __delay_ms(100); // espera um pouco, trata o debounce
        }
        if (PORTAbits.RA1 == 0 && estado == 1){ // caso botao A1 pressionado, desliga os LEDs
            estado = 0; // interrompe forcadamente o loop
            PORTB = 0b00000000;
            __delay_ms(100); // espera um pouco, trata o debounce
        }
    }
    return;
}
