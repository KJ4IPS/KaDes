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

#endif