//Exibe o número 3 no Display de 7 segmentos
//Teste em Placa3_7seg.simu

#define _XTAL_FREQ 20000000 //define a frequência em 20MHz

#include <xc.h>
#include "config_4520.h" //inclui os bits de configuração

void main(void) {
    TRISD = 0x00; //configura PORTD como saída digital
    PORTD = 0x00; //coloca PORTD em 0
    PORTD = 0b11110010; //Exibe o número 3
}
