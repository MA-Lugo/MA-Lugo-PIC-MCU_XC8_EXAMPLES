/* 
 * File:   main.c
 * Author: Mario
 * 
 * Brief:  UART char transmission  example @ 115200
 *          
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "Configbits.h"

#define _XTAL_FREQ 32000000

unsigned char my_string [10] = {"Hello!\n\r"};

void init_UART_TX(void);
void UART_Write(unsigned char data);

int main() {
OSCCONbits.SPLLEN = 1;      //PLL Enable
OSCCONbits.IRCF = 0b1110;   //8MHZ internal clock

PORTBbits.RB7 = 0;          //clear PINB7

init_UART_TX();

while(1){
    for(int i =0; i<=7;i++){
        UART_Write(my_string[i]);
    }
    
    __delay_ms(2000);
}
   
}

void init_UART_TX(void){
    WPUBbits.WPUB7  = 0;    //B7 pullup disable    
    TRISBbits.TRISB7= 0;    //PinB7 as output TX
    RB7PPSbits.RB7PPS = 0x14; // Peripheral Pin Selector output TX
    
    BAUD1CONbits.BRG16 = 0; // 16-bit Baud Rate Generator bit: 8Bit
   
    TX1STAbits.SYNC = 0;    //SYNC: EUSART Mode Select bit :Asynchronous mode
    TX1STAbits.TXEN = 1;    //Transmit Enable bit
    TX1STAbits.BRGH = 1;    //High Baud Rate Select bit
    
    SPBRG = 16;             //115200 @ 32MHz
    
}

void UART_Write(unsigned char data){
    
    while(!TXSTAbits.TRMT); //Transmit Shift Register Status bit 0:EMPTY
    TXREG = data;    

}

