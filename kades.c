/**
 * KaDes: A Kabuki desuicide.
 */
#include <xc.h>

#include "config_words.c"
#include "ui.h"
#include "timer.h"


void main (void) {
    clockSetup();
    while(1){
        clockTick();
        uiTick();
        if(setEvery100ms){
            setEvery100ms = 0;
            incrementUITimer();
        }
    }
}