#include"config.h"
#include <xc.h>

void lcdWriteCtrl(char x);
void lcdWriteData(char x);
void lcdSetPos(unsigned char row, unsigned char col);

const unsigned char keycode[]="123F456E789DA0BC"; 
char enter[]="Enter Value:";

extern char waterTime;
char ePressed=0;//when 1, E was pressed(when 1 allow input for user)
char nextinput=0;//when 1, input for row 2 column 1 | when 0, input for row 2 column 2
char dig_0=0x30;//tenth place
char dig_1=0x30;
char i;


unsigned char getkey(){//returns 4 bit val of DCBA
    unsigned char shiftthis;
    shiftthis=keycode[(PORTB>>1)&0x0F];
    return shiftthis;//note, this returns value in ascii
}

void displayLCD(){// displays "Enter Value" on the first line, second line displays dig0 and dig1
    lcdSetPos(1,1);
    for(i=0;enter[i]!=0;i++){
        lcdWriteData(enter[i]);
    }
    lcdSetPos(2,1);
    lcdWriteData(dig_0);
    lcdWriteData(dig_1);
}

void checkinput(){//everytime this is called, it toggles between 1st column and 2nd of the 2nd row
    if(nextinput==0){
        lcdSetPos(2,1);
        dig_0=getkey();
        nextinput=1;
    }
    else if(nextinput==1){
        lcdSetPos(2,2);
        dig_1=getkey();
        nextinput=0;
    }
    displayLCD();
}

void key(){
    if(getkey()=='E'){
        LED1=0;
        lcdWriteCtrl(0b00000001);
        ePressed=!ePressed;
        lcdWriteCtrl(0b00000001);
        displayLCD();
        if(ePressed==0){
                waterTime=((dig_0-0x30)*10)+(dig_1-0x30);
                lcdWriteCtrl(0b00000001);
            }
    }
    if(ePressed==1){
        if(getkey()!='E'){
            checkinput();
            displayLCD();
        }
    }
    
}

/*
 * Some limitations,
 * the previous dig0 and dig1 values are not set back to 0 (fix by setting dig0/1 to 0 when ePressed set back to 0?)| waterTime is still 30 after input(fix is to add a flag when input entered for the first time)
 * Expects a value ranging from 0-9 as an input, anything else will give an error | easy fix just reject any value that is not 0-9 
 * 
 */