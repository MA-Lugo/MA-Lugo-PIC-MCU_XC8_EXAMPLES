/* 
 * File:   main.c
 * Author: Mario
   Brief:  UART RX interrupt @ 115200
 *         set high the pinB5  if receives the 'a' character
 *         and clear the PinB5 if receives any other 
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "Configbits.h"

#define _XTAL_XTAL_FREQ 32000000

void init_UART_RX(void);
void set_interrupts(void);

int main() {
    OSCCONbits.SPLLEN = 1;      //PLL Enable
    OSCCONbits.IRCF = 0b1110;   //8MHZ internal clock
    set_interrupts();
    init_UART_RX();
    
    TRISBbits.TRISB5 = 0;       //output PB5
    PORTBbits.RB5 = 0 ;         //clear PB5
    
    while(1){
        
    }
    
}

void set_interrupts(void){
    INTCON=0;               //Reset INTCON reg
    INTCONbits.GIE = 1;     //Global Interrupt Enable bit
    INTCONbits.PEIE = 1;    //Peripheral Interrupt Enable bit
    
    PIR1bits.RCIF = 0;      //USART Receive Interrupt Flag bit
    PIE1bits.RCIE = 1;      //USART Receive Interrupt Enable bit
}

void init_UART_RX(void){
    WPUBbits.WPUB6      = 0;    //PinB6 pullup disable  
    TRISBbits.TRISB6    = 1;    //PinB6 as output RX
    RXPPSbits.RXPPS     = 0b01110; // Peripheral Pin Selector RX at PINB6
    
    BAUD1CONbits.BRG16  = 0; // 16-bit Baud Rate Generator bit: 8Bit
   
    RC1STAbits.RX9  = 0;     //RX9: 9-Bit Receive Enable bit: 8Bit
    RC1STAbits.SPEN = 1;     //SPEN: Serial Port Enable bit
    RC1STAbits.CREN = 1;     //CREN: Continuous Receive Enable bit
    
    SPBRG = 16;             //115200 @ 32MHz
}

void __interrupt() my_interrupt(void){
     
    if (PIR1bits.RCIF){         //USART Receive Interrupt Flag bit      
        unsigned char RXdata;    
        PIR1bits.RCIF = 0;       //Clear Flag 
        RXdata = RCREG;
        
        if (RXdata == 'a'){
            PORTB |= ( 1 << 5 );    //On PB5
        }
        else{                       //Diferent chr clean PB5
            PORTB &= ~( 1 << 5 );   //clear PB5
        }
    } 
}