/* 
 * File:   main.c
 * Author: Dirk
 *
 * Created on June 26, 2013, 7:49 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "pwm.h"

//Defines
#define DEBUG 0
#define INTOSC_CLOCK_4_MHZ 0x6C
#define INTOSC_CLOCK_8_MHZ 0x7C
#define OSC INTOSCCLK /**<Sets the oscilator config bit FOSC*/
#define _XTAL_FREQ 4000000

#define PERIOD 255
#define STEP 32

//Config bits
#pragma config BOREN = OFF, CPD = OFF, CCPMX = RB3, WRT = OFF
#pragma config FOSC = OSC, MCLRE = OFF, WDTE = OFF, CP = OFF, 
#pragma config LVP = OFF, PWRTE = OFF, IESO = OFF, FCMEN = OFF


int init(void){

    OSCCON = INTOSC_CLOCK_4_MHZ;
    TRISA = 0; //Set PORTA as outputs
    TRISB = 0; //Set PORTB as outputs

    TRISBbits.TRISB1 = 1;
    TRISBbits.TRISB2 = 1;
    nRBPU = 0; //Turn on weak pull ups

    ANSEL = 0; //Turn analog ports off

    PORTA = 0; //Clear the ports
    PORTB = 0; //Clear the ports
    return EXIT_SUCCESS;
}

/**
 * @brief The main function
 * @return Returns 0 if exit successful 
 */
int main(void) {

    
    init();

    #if !DEBUG
    openPWM(255);
    int dutyCycle = 255;
    while(1)
    {
        setDCPWM(dutyCycle);
        if(!RB2)
        {
            dutyCycle = dutyCycle - STEP;
            if(dutyCycle  < 0)
            {
                dutyCycle = 0;
            }
            __delay_ms(250);
        }
        if(!RB1)
        {
            dutyCycle = dutyCycle + STEP;
            if(dutyCycle > 255)
            {
                dutyCycle = 255;
            }
            __delay_ms(250);
        }
    }
    #endif

    #if DEBUG
    unsigned int ledState = 1;
    while(1)
    {
        if(PORTAbits.RA0 == 0)
        {
            //PORTBbits.RB3 = 0;
            ledState = 1 - ledState;
        }
        PORTBbits.RB3 = ledState;
    }
    #endif

    return (EXIT_SUCCESS);
}

