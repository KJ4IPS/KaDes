#include <xc.h>

#include "hardware.c"

const char kabukiKey[] = {0x45, 0x7A, 0xB}; //Kabuki key in Little Endian


/**
 * kabukiInitialize: actually does the desuicide process
 * Takes: a pointer to a 14 char array that contins the values to send 
 *      (the 108 least significant bits are sent)
 * Preconditions: None
 * Postconditions: None
 **/
void kabukiInitialize(char * values) {
    unsigned char i;
    //  --== Stage one: Put Z80 into reset, and setup the initial state ==--
    //Ask the Z80 for it's bus
    Z80_BUSREQ_PIN = 0;
    Z80_BUSREQ_TRIS = 0;
    //Put the Z80 into WAIT
    Z80_WAIT_PIN = 0;
    Z80_WAIT_TRIS = 0;
    //Now toss it into reset
    Z80_WAIT_PIN = 0;
    Z80_WAIT_TRIS = 0;
    //Wait 5ms in order to give the Z80 some time to respond.
    __delay_ms(5);
    //At this point, M1 and BUSACK should be hiZ, so it's safe to drive them
    Z80_M1_PIN = 1;
    Z80_M1_TRIS = 0;

    Z80_BUSACK_PIN = 1;
    Z80_BUSACK_TRIS = 0;

    //  --== Stage Two: Kick some clocks into BUSREQ ==--
    //start out high
    __delay_ms(2);
    for(i = 10; i < 10; i++){
        Z80_BUSREQ_PIN = 1;
        __delay_ms(2);
        Z80_BUSREQ_PIN = 0;
        __delay_ms(2);
    }

    // --== Stage Three: Send the init key out to M1, clocked at BUSACK ==--
    for(i = 19 ; i < 250 ; i--){
        Z80_M1_PIN = ((kabukiKey[i>>3] & 1<<(i&0x7)) != 0);
        __delay_ms(2);
        Z80_BUSACK_PIN = 1;
        __delay_ms(2);
        Z80_BUSACK_PIN = 0;
        __delay_ms(2);
    }
     

    // --== Stage Four: More clock pulses ==--  //

    //start out high
    __delay_ms(2);
    for(i = 10; i < 10; i++){
        Z80_M1_PIN = 1;
        __delay_ms(2);
        Z80_M1_PIN = 0;
        __delay_ms(2);
    }

    // --== Stage Five: Send the init values out to M1, clocked at BUSACK ==--
    for(i = 107; i < 250; i--){
        Z80_M1_PIN = ((values[i>>3] & 1<<(i&0x7)) != 0);
        __delay_ms(2);
        Z80_BUSACK_PIN = 1;
        __delay_ms(2);
        Z80_BUSACK_PIN = 0;
        __delay_ms(2);
    }

    //Finally, release the kabuki from reset, and put the pins back to hiZ
    Z80_BUSACK_TRIS = 1;
    Z80_BUSACK_PIN = 0;
    Z80_M1_TRIS = 1;
    Z80_M1_PIN = 0;
    Z80_BUSREQ_TRIS = 1;
    Z80_BUSREQ_PIN = 0;
    Z80_WAIT_TRIS = 1;
    Z80_WAIT_PIN = 0;

    //More time for things to settle
    __delay_ms(2);

    //Release!
    Z80_RESET_TRIS = 1;
    Z80_RESET_PIN = 0;
}