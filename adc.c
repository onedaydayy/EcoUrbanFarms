#include "config.h"
#include <xc.h>

unsigned char readpot(void){// invoked when disp7seg 
    unsigned char result;
    ADPCH=0b00000000;
    ADCON0bits.ADGO=1;
    while(ADCON0bits.ADGO==1);
    result=(ADRESH/5)-1;//value ranging from 50-0
    return result;
}
