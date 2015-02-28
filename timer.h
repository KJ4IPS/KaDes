/* 
 * File:   timer.h
 * Author: KJ4IPS
 *
 * Created on February 28, 2015, 4:02 PM
 */

#ifndef TIMER_H
#define	TIMER_H

#ifdef	__cplusplus
extern "C" {
#endif


    extern char setEvery100ms;

    extern void clockTick();
    
    extern void clockSetup();


#ifdef	__cplusplus
}
#endif

#endif	/* TIMER_H */

