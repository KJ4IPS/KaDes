
#include <xc.h>

#include "lcd.h"
#include "hardware.c"


#define lcdBlinkE()\
LCD_E_PIN = 1;\
LCD_E_TRIS = 0;\
/*The datasheet for the part states a .45us time,
we only run at 1us an insturction so no delay is needed*/\
LCD_E_PIN = 0;\
LCD_E_TRIS = 1;



void sendByteToLCD(char byte, char isCommand){
	//check if the LCD is busy...
	LCD_RS_PIN = 0;
	LCD_RS_TRIS = 0;

	LCD_RW_PIN = 1;
	LCD_RW_TRIS = 0;

	lcdBlinkE();

	LCD_DBUS_TRIS = 0xFF;
	while((LCD_DBUS_BANK & 0x80) !=0); //Wait for the LCD to become ready.

        LCD_RW_PIN = 1;

	LCD_DBUS_BANK = byte;
	LCD_DBUS_TRIS = 0x00;

	LCD_RS_PIN = !isCommand;
	LCD_RS_TRIS = 0;

	lcdBlinkE();

	LCD_RS_TRIS = 1;
	LCD_RW_TRIS = 1;
	LCD_DBUS_TRIS = 0xFF;
	
}

void printStringLCD(const unsigned char * stringIn){
    for(int i = 0; stringIn[i] != 0x00; i++)
        printCharLCD(stringIn[i]);
}
