/* 
 * File:   lcd.h
 * Author: KJ4IPS
 *
 * Created on February 28, 2015, 1:37 PM
 */

#ifndef LCD_H
#define	LCD_H

#ifdef	__cplusplus
extern "C" {
#endif

    #define printCharLCD(x) sendByteToLCD(x,0)
    #define clearLCD() sendByteToLCD(1,1)
    #define homeLCD() sendByteToLCD(2,1)
    #define lcdGotoChar(x) sendByteToLCD(0x80|x,1);
    #define lcdGotoLine(x) sendByteToLCD(0x80|(x<<4),1)


    #define initLCD()\
    sendByteToLCD(0x39,1); /*8-bit, 2 lines, 5x10 font*/\
    sendByteToLCD(0x6,1); /*Increment on character, no shift*/\
    sendByteToLCD(0xC,1); /*Display On, no cursor or blinking*/\
    sendByteToLCD(1,1) /*Finally, clear the LCD*/


    extern void sendByteToLCD(char byte, char isCommand);
    extern void printStringLCD(const unsigned char * stringIn);

    
#ifdef	__cplusplus
}
#endif

#endif	/* LCD_H */

