/*
 * File:   main.c
 *
 * Created on August 16, 2010, 12:09 PM
 */

#include "p18f24k50.h"
#include <xc.h>
#include <timers.h>

#pragma config FOSC = INTOSCIO
#pragma config MCLRE = ON
#pragma config PBADEN = OFF
#pragma config LVP = OFF
#pragma config WDTEN = OFF, DEBUG = OFF

//interrupt vector
void interrupt MyIntVec(void) {
    if (TMR0IE && TMR0IF) {
        TMR0IF = 0;
        if (PORTAbits.RA3) { // 
            LATB3 = !LATB3;
        } else {
            LATB3 = 1;
        }
        return;
    }
}

void main(void){
    TRISB = 0; // PORTB = output
    LATB = 1; // PORTB = 0V
    TRISA3 = 1; // PORTA = input
    ANSA3 = 0; // disable analog input on RA3 
    OSCCON = 0x78; // 4MHz 
    OpenTimer0(TIMER_INT_ON & T0_16BIT & T0_SOURCE_INT & T0_PS_1_4);
    GIEH = 1; // Enable global Interrupt
    while(1){
        // wait for interrupts
    }
}


