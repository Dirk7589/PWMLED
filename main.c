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
#define INTOSC_CLOCK_4_MHZ 0x6C
#define INTOSC_CLOCK_8_MHZ 0x7C
#define OSC INTOSCCLK /**<Sets the oscilator config bit FOSC*/
#define _XTAL_FREQ 4000000

#define PERIOD 255

//Config bits
#pragma config BOREN = OFF, CPD = OFF, CCPMX = RB3, DEBUG = OFF, WRT = OFF
#pragma config FOSC = OSC, MCLRE = OFF, WDTE = OFF, CP = OFF
#pragma config LVP = OFF, PWRTE = OFF, IESO = OFF, FCMEN = OFF


int init(void){

    OSCCON = INTOSC_CLOCK_4_MHZ;
    TRISA = 0; //Set PORTA as outputs
    TRISAbits.TRISA0 = 1; //Set RA0 as input
    TRISB = 0; //Set PORTB as outputs
    ANSEL = 0; //Turn analog ports off

    PORTA = 0; //Clear the ports
    PORTB = 0; //Clear the ports
    return EXIT_SUCCESS;
}

int adjustBrightness(unsigned int brightness){
    
    unsigned int period = PERIOD;
    unsigned int dutyCycle = 50;

    if(brightness == 0)
    {
        closePWM();
    }
    else
    {
        openPWM(period);
        setDCPWM(dutyCycle);
    }
    return EXIT_SUCCESS;
}


/**
 * @brief The main function
 * @return Returns 0 if exit successful 
 */
int main(void) {

    init();
    openPWM(255);
    unsigned int dutyCycle = 255;
    while(1)
   {
        setDCPWM(dutyCycle);
        if(RA0 == 0)
        {
           dutyCycle = dutyCycle - 64;

        }

    }
    return (EXIT_SUCCESS);
}

