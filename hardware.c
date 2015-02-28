/**
 * This contains the macros that are used for pins, as well as the xtal freq
 */

#ifndef HARDWARE_INC
#define HARDWARE_INC

#define _XTAL_FREQ 4000000

#define Z80_M1_PIN PORTAbits.RA0
#define Z80_M1_TRIS TRISAbits.TRISA0

#define Z80_RESET_PIN PORTAbits.RA1
#define Z80_RESET_TRIS TRISAbits.TRISA1

#define Z80_WAIT_PIN PORTAbits.RA2
#define Z80_WAIT_TRIS TRISAbits.TRISA2

#define Z80_BUSREQ_PIN PORTAbits.RA3
#define Z80_BUSREQ_TRIS TRISAbits.TRISA3

#define Z80_BUSACK_PIN PORTAbits.RA4
#define Z80_BUSACK_TRIS TRISAbits.TRISA4

#define LCD_RS_PIN PORTDbits.RD0
#define LCD_RS_TRIS TRISDbits.TRISD0

#define LCD_RW_PIN PORTDbits.RD1
#define LCD_RW_TRIS TRISDbits.TRISD1

#define LCD_DBUS_BANK PORTB
#define LCD_DBUS_TRIS TRISB

#define LCD_E_PIN PORTDbits.RD3
#define LCD_E_TRIS TRISDbits.TRISD3

#define BUTTON_NEXT_PIN PORTEbits.RE0
#define BUTTON_NEXT_TRIX TRISEbits.TRISE0

#define BUTTON_GO_PIN PORTEbits.RE1
#define BUTTON_GO_TRIS TRISEbits.TRISE1

 
#endif