#include <xc.h>
#include "timer.h"

unsigned char milliseconds; //ranges from 0-99
unsigned char twoHundredMicroSeconds; //ranges from 0-4
char setEvery100ms;

void clockSetup(){
    T0CON = 0x48; //8-bit, instuction clock, 1:2 prescaler (2us/tick)
    TMR0L = 0x00; //reset timer
    TMR0ON = 1; //start the timer
    twoHundredMicroSeconds = 0;
    milliseconds = 0;
}

void clockTick(){
    if(TMR0L > 100 || TMR0IF){
        TMR0IF = 0;
        TMR0L = 0x00;
        twoHundredMicroSeconds++;
    }
    if(twoHundredMicroSeconds >=5){
        twoHundredMicroSeconds = 0;
        milliseconds++;
    }
    if(milliseconds >= 100) {
        milliseconds = 0;
        setEvery100ms = 1;
    }
}
