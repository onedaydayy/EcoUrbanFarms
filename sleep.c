#include "config.h"
#include <xc.h>

void lcdWriteCtrl(char x);
void lcdWriteData(char x);
void lcdSetPos(unsigned char row, unsigned char col);
void clearEverything();

char sleepcnt=0;
char sleeptxt[]="Sleep mode";

void checksleep(){
    if(sleepcnt==5){
        sleepcnt=0;
        clearEverything();
        PORTC=0xFF;
        SLEEP();
        PWM6CONbits.EN=1;
    }
}
void clearEverything(){
    LED1=0;//off irrigation LED
    PWM6CONbits.EN=0;//off lightbulb
    lcdWriteCtrl(0b00000001);//clear lcd
    lcdSetPos(1,1);
    for(char i=0;sleeptxt[i]!=0;i++){//sets LCD to display message[] before entering sleep mode
        lcdWriteData(sleeptxt[i]);
    }
}


