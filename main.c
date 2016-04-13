/*
 * File:   main.c
 *
 * Created on August 16, 2010, 12:09 PM
 */

#include "p18f24k50.h"
#include <xc.h>
#include <timers.h>

#define ADCON0_INIT_CONFIG 0b00000101 // Enable ADC, reset GO bit and select analog channel for RA1
#define ADCON1_INIT_CONFIG 0b00000000 // Select Vdd and Vss as references
#define ADCON2_INIT_CONFIG 0b00001100 // Acquisition time of 2TAD and select clock of Fosc/4

#pragma config FOSC = INTOSCIO
#pragma config MCLRE = ON
#pragma config PBADEN = OFF
#pragma config LVP = OFF
#pragma config WDTEN = OFF, DEBUG = OFF

static volatile int result;

//interrupt vector
void interrupt MyIntVec(void) {
//    if (TMR0IE && TMR0IF) {
//        TMR0IF = 0;
//        if (PORTAbits.RA3) { // 
//            LATB3 = !LATB3;
//        } else {
//            LATB3 = 1;
//        }
//        return;
//    }
    
    // ADC conversion finished
    if (ADIF) {
        ADIF = 0;
        result = (ADRESH << 2) | (ADRESL >> 6);
        
        GO = 1;
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
    
    // Turn off the LED
    LATB3 = 0;
    
    // Configure ADC pin (RA1)
    ANSA1 = 1;
    TRISA1 = 1;
    
    // Configure ADC
    ADCON0 = ADCON0_INIT_CONFIG;
    ADCON1 = ADCON1_INIT_CONFIG;
    ADCON2 = ADCON2_INIT_CONFIG;
    
    // Configure ADC interrupt
    ADIF = 0; // A/D interrupt flag (clearing at init)
    ADIE = 1; // Enable interrupts for ADC
    
    // Launch the conversion
    GO = 1;
    
    while(1){
        // wait for interrupts
        ADIE = 0;
        int fetch_result = result;
        ADIE = 1;
        if(fetch_result > 0b1000000000){
            LATB3 = 1;
        }
        else{
            LATB3 = 0;
        }
    }
}


