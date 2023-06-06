#include <xc.h>
#include "config.h"

void lcdWriteCtrl(char x);
void lcdWriteData(char x);
void lcdSetPos(unsigned char row, unsigned char col);

extern char waterTime;
extern char ePressed;
char dig0;
char dig1;
char watercnt=0;
char i;
char message[] ="Irrigation in: ";
char message2[]="process";

void updateLCD(){//display countdown
    lcdSetPos(1,1);
    for(i=0;message[i]!=0;i++){//what if message contains 0, hmm
        lcdWriteData(message[i]);
    }
    lcdSetPos(2,1);
    lcdWriteData(dig1+0x30);
    lcdWriteData(dig0+0x30);
    lcdWriteData(0x73);   
}
void updateLCD2(){//display irrigation message
    lcdSetPos(1,1);
    for(i=0;message[i]!=0;i++){//what if message contains 0, hmm
        lcdWriteData(message[i]);
    }
    lcdSetPos(2,1);
    for(i=0;message2[i]!=0;i++){
        lcdWriteData(message2[i]);
    }
}
void func_water(){
    dig1=((waterTime%100)/10);
    dig0=(waterTime%10);
    if(ePressed==0){
        if(PORTAbits.RA1==1){
            watercnt++;
            waterTime=30;
            if(watercnt==3){
                LED1=0;
                watercnt=0;
                lcdWriteCtrl(0b00000001);//blank LCD
            }
        }
        if(LED1==0){
            waterTime--;
            updateLCD();
        }
        if(waterTime==0){
            updateLCD2();
            LED1=1;
        }
    }
}