// Pisca o LED que está no pino B0
#define _XTAL_FREQ 20000000

#include <xc.h>
#include "config_4520.h"

void main(void) {
    TRISBbits.RB0 = 0;
    while(1){
        PORTBbits.RB0 = 0;
        __delay_ms(500);
        PORTBbits.RB0 = ~(PORTBbits.RB0);
        __delay_ms(500);
    }
    return;
}
