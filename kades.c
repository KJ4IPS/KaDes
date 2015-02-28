/**
 * KaDes: A Kabuki desuicide.
 */
#include <xc.h>

#include "config_words.c"
#include "hardware.c"
#include "games.h"
#include "desuicide.h"

void main (void) {
    unsigned char progbits[14];
    if(loadGameFromDB(1)){
        gameToBitstream(progbits);
        kabukiInitialize(progbits);
    }else{
        /*Game does not exist as a valid gamedb entry!*/
        NOP(); //BREAK HERE!!!
    }
    NOP();
}