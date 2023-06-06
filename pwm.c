#include "config.h"
#include <xc.h>
int dutycycle=0;
char tmrcnt=1;

void pwm()
{
     tmrcnt++;
    if(tmrcnt==12){
        tmrcnt=0;
    }
    else if(tmrcnt==1){
        dutycycle=500;
    }
    if(tmrcnt<=10){
        if(dutycycle!=0){
            dutycycle-=50;//10% of 500 is 50 | will take 10 counts for lightbulb to go from full brightness to completely dim
        }
    }
    PWM6DCH=dutycycle>>2;
    PWM6DCL=dutycycle<<6;
}

