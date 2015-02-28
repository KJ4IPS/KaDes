/**
 * Game Format:
 *  2 magic bytes - 0x27 0x42
 *  2 bytes - address key (little endian)
 *  3 bytes - swap key 1 (little endian)
 *  3 bytes - swap key 2 (little endian)
 *  1 byte - swap key XOR key
 *  2 bytes - memory mask (little endian)
 *  1 byte - checksum, sum of all other bytes, excepting magic
 */
#include <xc.h>

#include "gamedb.h"

unsigned char addrKey[2];
unsigned char swapKey1[3];
unsigned char swapKey2[3];
unsigned char xorKey;
unsigned char addrRange[2];

#define tblrd_post_inc() asm("TBLRD*+")
//There may already be a macro for this, I just don't know

char loadGame(unsigned char * offset){

    //First, load the offset into the table pointer
    TBLPTRL = offset[0];
    TBLPTRH = offset[1];
    TBLPTRU = offset[2];

    //read the table now
    tblrd_post_inc();
    if(TABLAT != 0x27) return 0; //check the magic bytes
    tblrd_post_inc();
    if(TABLAT != 0x42) return 0;


    tblrd_post_inc(); //Address Key
    addrKey[0] = TABLAT;

    tblrd_post_inc();
    addrKey[1] = TABLAT;

    tblrd_post_inc(); //Swap Key One
    swapKey1[0] = TABLAT;

    tblrd_post_inc();
    swapKey1[1] = TABLAT;

    tblrd_post_inc();
    swapKey1[2] = TABLAT;

    tblrd_post_inc(); //Swap Key Two
    swapKey2[0] = TABLAT;

    tblrd_post_inc();
    swapKey2[1] = TABLAT;

    tblrd_post_inc();
    swapKey2[2] = TABLAT;

    tblrd_post_inc(); //XOR Key
    xorKey = TABLAT;

    tblrd_post_inc(); //Address Range
    addrRange[0] = TABLAT;

    tblrd_post_inc();
    addrRange[1] = TABLAT;

    tblrd_post_inc(); //verify checksum
    char expectedCheck = addrKey[0] + addrKey[1]
    + swapKey1[0] + swapKey1[1] + swapKey1[2]
    + swapKey2[0] + swapKey2[1] + swapKey2[2]
    + xorKey + addrRange[0] + addrRange[1];
    return TABLAT == expectedCheck;

}

char loadGameFromDB(unsigned char index){
    unsigned char targetAddress[3];
    targetAddress[0] = GAMEDB_BASE[0];
    targetAddress[1] = GAMEDB_BASE[1];
    targetAddress[2] = GAMEDB_BASE[2];

    //multiplication through iterative addition, with carrys
    for(unsigned char i = index; i > 0; i--){
        unsigned char w = targetAddress[0] + GAMEDB_ENTRY_LENGTH;
        if(w < targetAddress[0]){
            unsigned char x = targetAddress[1]+1;
            if(x < targetAddress[1]){
                targetAddress[2] = (targetAddress[2]+1) & 0x3F;
            }
            targetAddress[1] = x;
        }
        targetAddress[0] = w;
    }

    return loadGame(targetAddress);


}


void gameToBitstream(unsigned char * out){
    /* char = nybble
     *  ?0 00 00 aa aa ss ss ss SS SS SS xx mm mm
     * ? = padding for byte alignment
     * 0 = zero
     * a = address
     * s = swap two
     * S = swap one
     * x = xor
     * m = mask
     */

    unsigned char i;
    i = 0;
    //Initialize the array to zero
    for(i = 0; i < 14 ; i++ ){
        out[i] = 0x00;
    }

    //bits 0-19 are working bits, that get left at zero

    //address key
    out[3] = addrKey[1];
    out[4] = addrKey[0];

    //swap key two
    out[5] = swapKey2[2];
    out[6] = swapKey2[1];
    out[7] = swapKey2[0];

    //swap key one
    out[8] = swapKey1[2];
    out[9] = swapKey1[1];
    out[10] = swapKey1[0];

    //xor key
    out[11] = xorKey;

    //address encryption range
    out[12] = addrRange[1];
    out[13] = addrRange[0];


}