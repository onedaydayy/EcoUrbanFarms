#include "config.h"
#include <xc.h>

unsigned char readpot(void);
unsigned char nextSeg=0;

const unsigned char segTable[11]={
    0b11000000,
    0b11111001,
    0b10100100,
    0b10110000,
    0b10011001,
    0b10010010,
    0b10000010,
    0b11111000,
    0b10000000,
    0b10011000,
    0b11111111
};
void disp7seg() {//invoked when interrupt | displays dig1 and dig0, result from readpot()
    char dig1=((readpot()%100)/10);//tenth place
    char dig0=(readpot()%10);

    if(nextSeg==0){//led left
        PORTC=segTable[10];
        PORTAbits.RA5=0;
        PORTAbits.RA4=1;
        PORTC=segTable[dig0];
        nextSeg=1;
    }
    else if(nextSeg==1){
        PORTC=segTable[10];
        PORTAbits.RA5=1;
        PORTAbits.RA4=0;
        PORTC=segTable[dig1];
        nextSeg=0;
    }
}
