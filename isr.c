#include "config.h"
#include <xc.h>

void func_water(void);
void key(void);
void disp7seg(void);
void checksleep(void);
void pwm(void);

extern char sleepcnt;
extern char SW1check;
extern char SW0check;

void __interrupt() isr(){
    if(PIR0bits.TMR0IF==1){
        TMR0H=0xC2;
        TMR0L=0xF7;
        TMR0IF=0;
        sleepcnt++;
        pwm();
        func_water();
    }
    if(IOCAF3==1){
        IOCAF3=0;
        SW0check=1;
    }
    if(IOCBF0==1){
        IOCBF0=0;
        SW1check=1;
    }
    if(IOCBF5==1){
        IOCBF5=0;
        key();
    }
    if(PIR4bits.TMR1IF==1){//interrupts every 5ms, acts as a multiplexor to select 7segment LED)
    PIR4bits.TMR1IF=0; 
    TMR1H=0xFD;
    TMR1L=0x8F;
    disp7seg();
    }
}
