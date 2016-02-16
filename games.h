//#if !defined(GAME_H)  
//#define GAME_H

//ifdef guards removed (for some reason they kill the preprocessor...)

#ifdef	__cplusplus
extern "C" {
#endif

extern unsigned char addrKey[2];
extern unsigned char swapKey1[3];
extern unsigned char swapKey2[3];
extern unsigned char xorKey;
extern unsigned char addrRange[2];

extern char loadGame(char * offset);
extern char loadGameFromDB(unsigned char index);
extern void gameToBitstream(unsigned char * out);

#ifdef	__cplusplus
}
#endif


//#endif	/* GAME_H */
