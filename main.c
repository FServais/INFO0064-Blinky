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
#define ADCON2_INIT_CONFIG 0b00111100 // Acquisition time of 8TAD and select clock of Fosc/4

#pragma config FOSC = INTOSCIO
#pragma config MCLRE = ON
#pragma config PBADEN = OFF
#pragma config LVP = OFF
#pragma config WDTEN = OFF, DEBUG = OFF

volatile int result = 0;

//interrupt vector
void interrupt MyIntVec(void) {
    if (TMR0IE == 1 && TMR0IF == 1) {
        TMR0IF = 0;
        ADCON0bits.GO = 1;
    }
    // ADC conversion finished
    if (PIE1bits.ADIE == 1 && PIR1bits.ADIF == 1 ) {
        PIR1bits.ADIF = 0; // reset end of conversion flag
        result = (ADRESH << 2) | (ADRESL >> 6);
    }
}

 static void initADCON() {
    // Init ADCON0
    ADCON0bits.ADON = 1; // Enable ADC module
    ADCON0bits.GO_nDONE = 0; // Reset GO to 0
    ADCON0bits.CHS = 0b00001; // Use RA1 as input channel
    TRISAbits.TRISA1 = 1; // Set RA1 pin as input
    ANSELAbits.ANSA1 = 1; // Set RA1 as analog input
    // Init ADCON1
    ADCON1bits.TRIGSEL = 0; // special trigger from CCP2
    ADCON1bits.PVCFG = 0; // connect reference Vref+ to internal Vdd
    ADCON1bits.NVCFG = 0; // connect reference Vref- to external Vdd
    // Init ADCON2
    ADCON2bits.ADFM = 0; // result format is left justified
    ADCON2bits.ACQT = 0b100; // 8 TAD
    ADCON2bits.ADCS = 0b101; // Fosc / 16
 }

static void initOscillator() {
    OSCCONbits.IDLEN = 1; // Device enters in sleep mode
    OSCCONbits.IRCF = 0b111; // Internal oscillator set to 16MHz
    OSCCONbits.OSTS = 0; // Running from internal oscillator
    OSCCONbits.HFIOFS = 0; // Frequency not stable
    OSCCONbits.SCS = 0b00; // Primary clock defined by FOSC<3:0>
}

static void initPortB() {
    TRISB = 0; // PORTB = output
    LATB = 1; // Clear B outputs (set 0V)
    // Turn off the LED outputs
    LATBbits.LATB3 = 0;
    LATBbits.LATB5 = 0;
}


void main(void){
    initOscillator();
    initADCON();
    initPortB();
    OpenTimer0(TIMER_INT_ON     // Timer enabled
                & T0_16BIT      // Timer counter on 16 bits
                & T0_SOURCE_INT // Internal clock as source
                & T0_PS_1_4);   // Timer divider 1:4

    GIEH = 1; // Enable global Interrupt
    PEIE = 1; // Enable peripheral interrupts
    PIE1bits.ADIE = 1; // Enable interrupts for ADC
    PIR1bits.ADIF = 0; // Reset A/D interrupt flag 
    
    // Main loop
    int fetched_result = 0;
    while(1){
        PIE1bits.ADIE = 0; 
        fetched_result = result;
        PIE1bits.ADIE = 1;
        
        if (fetched_result > 512) {
            LATB3 = 1;
        } else {
            LATB3 = 0;
        }
    }
}


