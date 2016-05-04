/*
 * File:   main.c
 *
 * Created on August 16, 2010, 12:09 PM
 */

#include "p18f24k50.h"
#include <xc.h>
#include <timers.h>
#include <plib/usart.h>

#pragma config FOSC = INTOSCIO
#pragma config MCLRE = ON
#pragma config PBADEN = OFF
#pragma config LVP = OFF
#pragma config WDTEN = OFF, DEBUG = OFF

volatile int result = 0;

unsigned char Txdata[] = "HELLO";

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
    LATBbits.LATB4 = 0;
    LATBbits.LATB5 = 0;
}

static void initPortC() {
    TRISCbits.RC6 = 1;
    TRISCbits.RC7 = 1;
}

static void outputPWM() {
    TRISC1 = 0;  // set PORTC as output, RC1 is the pwm pin output
    PORTC = 0;   // clear PORTC
    //PR2 = 0b01100011;
    
    /* PWM registers configuration
    * Fosc = 16000000 Hz
    * Fpwm = 40000.00 Hz (Requested : 40000 Hz)
    * Duty Cycle = 50 %
    * Resolution is 8 bits
    * Prescaler is 4
    * Ensure that your PWM pin is configured as digital output
    * see more details on http://www.micro-examples.com/
    * this source code is provided 'as is',
    * use it at your own risks
    */
    PR2 = 0b00011000 ;
    CCP2CON = 0b00011100;
    CCPR2L = 0b00001100;
    T2CKPS1 = 0;    // Prescaler value - High bit
    T2CKPS0 = 1;    // Prescaler value - Low bit
    TMR2ON = 1;     // Activate timer 2
  
}

static void enableGlobalInterrupts() {
    GIEH = 1;
}

static void enablePeripheralInterrupts() {
    PEIE = 1;
}

void main(void){
//    initOscillator();
//    initADCON();
//    initPortB();
//    outputPWM();
//    OpenTimer0(TIMER_INT_ON     // Timer enabled
//                & T0_16BIT      // Timer counter on 16 bits
//                & T0_SOURCE_INT // Internal clock as source
//                & T0_PS_1_4);   // Timer divider 1:4
//
//    GIEH = 1; // Enable global Interrupt
//    PEIE = 1; // Enable peripheral interrupts
//    PIE1bits.ADIE = 1; // Enable interrupts for ADC
//    PIR1bits.ADIF = 0; // Reset A/D interrupt flag 
//    
//    // Main loop
//    int fetched_result = 0;
//    while(1){
//        PIE1bits.ADIE = 0; 
//        fetched_result = result;
//        PIE1bits.ADIE = 1;
//        
//        if (fetched_result > 512) {
//            LATB4 = 1;
//        } else {
//            LATB4 = 0;
//        }
//    }
    initOscillator();
    initPortC();
    
    enableGlobalInterrupts();
    enablePeripheralInterrupts();
    
    Close1USART();
    
    unsigned char configUSART = USART_TX_INT_OFF; // Deactivate interrupt transmitter
    configUSART |= USART_RX_INT_OFF; // Deactivate interrupt receiver
    configUSART |= USART_ASYNCH_MODE; // Asynchronous mode
    configUSART |= USART_EIGHT_BIT; //8-bit mode
    configUSART |= USART_CONT_RX;
    configUSART |= USART_BRGH_LOW;
    
    // This is the value that is written to the baud rate generator register which determines the baud rate at which the usart operates
    // For a baud rate of 9615 with Fosc = 16MHz -> spbrg = 25 (decimal)
    // See PIC datasheet, page 283
    unsigned char spbrg = 25;
    Open1USART(configUSART, spbrg);
    
    unsigned char baudConfig = BAUD_8_BIT_RATE | BAUD_AUTO_OFF;
    baud1USART(baudConfig);
    
    while(Busy1USART());
    puts1USART(Txdata);
    
    Close1USART();
    while(1);
}


