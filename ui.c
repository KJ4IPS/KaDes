
#include <xc.h>

#include "games.h"
#include "lcd.h"
#include "gamedb.h"
#include "desuicide.h"

typedef enum {
    UI_STATE_INIT,
    UI_STATE_WELCOME,
    UI_STATE_WELCOME_WAIT,
    UI_STATE_THANKS,
    UI_STATE_THANKS_WAIT,
    UI_STATE_MENU,
    UI_STATE_PROGRAMMING,
    UI_STATE_DONE,
    UI_STATE_BAD_DB,
    UI_STATE_WAITFORKEYPRESS
} UI_STATE;

UI_STATE uistate = UI_STATE_WELCOME;

char uitimer;
char gameindex;
char buffer[14];

void printGameCount(){
    char gamecount=0;
    unsigned const char * game;
    do{
        game = gameTitles[gamecount];
        gamecount++;
    }while(game!=0x00);
    char tens = '0';
    
    while(gamecount > 10){
        tens++;
        gamecount -= 10;
    }

    printCharLCD(tens);
    printCharLCD(gamecount + '0');
}

void uiTick(){
    switch(uistate){
        case UI_STATE_INIT:
            initLCD();    /*1234567890123456*/
            uistate=UI_STATE_WELCOME;
            break;
        case UI_STATE_WELCOME:
            printStringLCD(" KaDes by KJ4IPS");
            printGameCount(); //Prints 2 characters
            printStringLCD(  " games located");
            uistate= UI_STATE_WELCOME_WAIT;
            uitimer = 0;
            break;
        case UI_STATE_WELCOME_WAIT:
            if (uitimer > 20) uistate=UI_STATE_THANKS;
            break;
        case UI_STATE_THANKS:
            homeLCD();
            printStringLCD(" Made possible  ");
            printStringLCD("by ArcadeHacker!");
            uistate=UI_STATE_THANKS_WAIT;
            uitimer = 0;
            break;
        case UI_STATE_THANKS_WAIT:
            if (uitimer > 20) uistate=UI_STATE_MENU;
            break;
        case UI_STATE_MENU:
            homeLCD();
            printStringLCD(" Select Game :  ");
            lcdGotoLine(1);
            printStringLCD("                ");
            printStringLCD(gameTitles[gameindex]);
        case UI_STATE_PROGRAMMING:
            homeLCD();
            printStringLCD("Programming.....");
            printStringLCD("  Please Wait   ");
            if(loadGameFromDB(gameindex)){
                gameToBitstream(buffer);
                kabukiInitialize(buffer);
                uistate=UI_STATE_DONE;
            }else{
                uistate=UI_STATE_BAD_DB;
            }
        case UI_STATE_DONE:
            homeLCD();
            printStringLCD("  -*Complete*-  ");
            printStringLCD(" Reset: Any key ");
            uistate = UI_STATE_WAITFORKEYPRESS;
        case UI_STATE_BAD_DB:
            homeLCD();
            printStringLCD("!Bad game entry!");
            printStringLCD("!Reset: Any key!");
            uistate = UI_STATE_WAITFORKEYPRESS;
        default:
            uistate = UI_STATE_WELCOME;
    }
}

//This should get called about every 100ms
void incrementUITimer(){
    uitimer++;
}