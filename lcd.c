#include "config.h"
#include <xc.h>

void lcdWriteCtrl(char x){// some times causes errors during build
    LCD_RS=0;
    LCD_DATA=x;
    LCD_E=1;
    __delay_ms(1);
    LCD_E=0;
    __delay_ms(1);
    LCD_DATA=x<<4;
    LCD_E=1;
    __delay_ms(1);
    LCD_E=0;
    __delay_ms(1);
}
void lcdWriteData(char x){
    LCD_RS=1;
    LCD_DATA=x;
    LCD_E=1;
    __delay_ms(1);
    LCD_E=0;
    __delay_ms(1);
    LCD_DATA=x<<4;
    LCD_E=1;
    __delay_ms(1);
    LCD_E=0;
    __delay_ms(1);
    
}
void lcdSetPos(unsigned char row, unsigned char col){
    unsigned char ramAddr;
    if(row==1){
        ramAddr = col-1; 
    }
    else{
        ramAddr=col+0x40-1;
    }
    lcdWriteCtrl(ramAddr+0x80);
}
void initLCD(void){
    __delay_ms(15);
    lcdWriteCtrl(0b00000011);
    __delay_ms(5);
    lcdWriteCtrl(0b00000010);
    lcdWriteCtrl(0b00101000);
    lcdWriteCtrl(0b00001100);
    lcdWriteCtrl(0b00000110);
    lcdWriteCtrl(0b00000001);
}