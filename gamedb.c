const char GAMEDB_ENTRY_LENGTH = 14;
const char GAMEDB_BASE[] = {0x00, 0x50, 0x0};

/*
 * This is a list of game titles, in the same order as they exist in storage
 * maximum 16 characters */
const unsigned char * gameTitles[] = { //Pointerception!
    "Block Block",
    "Super Pang>World",
    "Super Pang>Japan",
    (void*) 0 //NULL
};

/*
 * This is a block of program memory (starting at 0x5000) that contains the keys
 * for games to be desuicided. Accessed by program memory reads.
 */
const unsigned char gamedb[] @ 0x5000 = {
    /*
    //GAME NAME
    0x27, 0x42,         // - Just to identify this as a valid gamedb entry
    0xaa, 0xaa,         // - Address Key [Little Endian]
    0xss, 0xss, 0xss,   // - Swap Key One [Little Endian]
    0xSS, 0xSS, 0xSS,   // - Swap Key Two [Little Endian]
    0x01,               // - xor key
    0x00, 0xC0,         // - Encryption area mask [Little Endian]
    0x57                // - Checksum (add all, excepting magic)
     */
    //Block Block
    0x27, 0x42,
    0x02, 0x00,
    0xEF, 0x62, 0x0A,
    0x59, 0x0F, 0xD1,
    0x01,
    0x00, 0xC0,
    0x57,
    //Super Pang (World)
    0x27, 0x42,
    0x52, 0x58,
    0x53, 0x70, 0x97,
    0x53, 0x70, 0x97,
    0x43,
    0x00, 0xC0,
    0x61,
    //Super Pang (Japan)
    0x27, 0x42,
    0xAA, 0x55,
    0xB8, 0xA7, 0x94,
    0xE5, 0x14, 0xDC,
    0x5A,
    0x00, 0xC0,
    0x61
};


