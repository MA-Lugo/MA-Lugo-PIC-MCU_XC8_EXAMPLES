/* 
 * File:   main.c
 * Author: Mario Lugo
 * Description: TIMER0 interrupt every 1ms and the interrupt routine
 *              toggle the PinB7 value every 10ms.
 * 
 * Created on 11 de noviembre de 2020, 11:36 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "ConfigBits.h"

#define _XTAL_FREQ 32000000

unsigned char TMR0_value = 131; // load for 1ms at 1:64 prescaler
int i = 0;

void setup_TMR0_interrupt(){
    INTCON=0;               //Reset INTCON reg
    INTCONbits.GIE = 1;     //Global Interrupt Enable bit
    INTCONbits.PEIE = 1;    //Peripheral Interrupt Enable bit
    INTCONbits.TMR0IE = 1;  //TMR0IE: Timer0 Overflow Interrupt Enable bit
    INTCONbits.TMR0IF = 0;  //Timer0 Overflow Interrupt Flag bit
    
    OPTION_REGbits.TMR0CS = 0;  //Timer0 Clock Source Select bit: FOSC/4
    OPTION_REGbits.TMR0SE = 0;  //Timer0 Source Edge Select bit
    OPTION_REGbits.PSA = 0;     //Prescaler Assignment bit: enable
    OPTION_REGbits.PS = 0b101;  //Prescaler 1:64
    TMR0 = TMR0_value;          //Load for 1ms interrupt
}
 
void __interrupt() my_interrupt(void){
    
    if(INTCONbits.TMR0IF){      //Timer0 Overflow Interrupt Flag bit
        TMR0 = TMR0_value;      
        INTCONbits.TMR0IF = 0;  //Clear Flag
        if (i == 10){
           PORTB ^= (1 << 7); 
           i = 0;
        }
        i++;      
    }      
}
int main() {
    OSCCONbits.SPLLEN = 1;      //PLL Enable
    OSCCONbits.IRCF = 0b1110;   //8MHZ internal osc
    TRISBbits.TRISB7 = 0;       //PinB7 output 
    PORTBbits.RB7 = 0;          //clear PinB7
    setup_TMR0_interrupt();
    
    while(1){
        
    }
 
}

