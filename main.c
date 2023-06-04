#include "config.h"
#include <xc.h>

void initLCD(void);
void checksleep(void);

extern char sleepcnt;
char SW0check=0;
char SW1check=0;
char waterTime=30;// counts per 1 sec, check func_water()


void initPWM(){
    CCPTMRS1=0b00000100;
    PWM6CON=0b00000000;
    PWM6DCH=0b00000000;
    PWM6DCL=0b00000000;
    RA2PPS=0x0E;
}
void initADC(){
    ADREF=0b00000000;
    ADCLK=0b00000001;
    ADACQ=0b00000101;//5us
    ADCON0=0b10000000;
}
void initIOC(){
    IOCAN=0b00001000;
    IOCBP=0b00100000;
    IOCBN=0b00000001;
}
void detSW0(){//turns on LED1
    if(SW0check==1){
        LED1=1;
        SW0check=0;
    }
}    
void detSW1(){//resets sleepcnt
    if(SW1check==1){
        sleepcnt=0;
        SW1check=0;
    }
}
void initSysPins(){//PORTE,LCD select | PORTA, LED | PORTD, LCD data line
    ANSELA=0b00000001;
    TRISA=0b11001001;//RA0 is pot trimmer(analog)| RA1 is LED1 | RA2 is lightbulb | RA3 is SW0 | RA4 and RA5 select 7 segment 
    
    ANSELB=0b00000000;
    TRISB=0b11111111;//RB0 SW1 |RB1-RB4 DCBA of keypad respectively| RB5 DA for keypad
    
    ANSELC=0b00000000;
    TRISC=0b00000000; //RC0-RC6 7 segment LED | RC7 for dp unused
    
    ANSELD=0b00000000;
    TRISD=0b00001111; //RD0 is keypad OE(ground this) | RD4-RD7 LCD inputs
    
    ANSELE=0b00000000;
    TRISE=0b11111100;// RE0 enable pin for LCD | RE1 register select for LCD | RE3 mcu reset switch
}

void initTMR0(){//1 sec period
    T0CON0=0b10010000;
    T0CON1=0b01000110;
    TMR0H=0xC2;
    TMR0L=0xF7;
}
void initTMR1(){//5ms period
    T1CON=0b00110011;
    T1CLK=0b00000001;
    TMR1H=0xFD;
    TMR1L=0x8F;
}
void initTMR2(){//16ms period
    T2PR=124;
    T2CON=0b11110000;
    T2CLKCON=0b00000001;
}
void initSysDevice(){
    CPUDOZE=0;
    INTCONbits.GIE=0;
    PIE0bits.IOCIE=0;
    INTCONbits.PEIE=0;
    initIOC();
    initTMR2();
    initTMR1();
    initTMR0();
    IOCAF3=0;
    IOCBF5=0;
    IOCBF0=0;
    PIR4bits.TMR1IF=0;
    PIE4bits.TMR1IE=1;
    PIR0bits.TMR0IF=0;
    PIE0bits.TMR0IE=1;
    INTCONbits.PEIE=1;
    PIE0bits.IOCIE=1;
    INTCONbits.GIE=1;
}

void main() {
    LED1=0;
    PORTDbits.RD0=0;//ground keypad OE 
    initSysPins();
    initSysDevice();
    initLCD();
    initADC();
    initPWM();
    PWM6CONbits.EN=1;
    while(1){
        detSW0();
        detSW1();
        checksleep();
    }

}
