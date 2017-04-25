/*
 * hardware_test_shiftreg.c
 *
 * Created: 3/11/17 2:15:19 PM
 * Author : Ryan
 */ 

#include <avr/io.h>
#include <seven_seg.h>
#include <timer.h>
#include <stdio.h>

void transmit_data(unsigned char data) {
	int i;
	for (i = 0; i < 8; ++i) {
		// Sets SRCLR to 1 allowing data to be set
		// Also clears SRCLK in preparation of sending data
		PORTB = 0x08;
		// set SER = next bit of data to be sent.
		PORTB |= ((data >> i) & 0x01);
		// set SRCLK = 1. Rising edge shifts next bit of data into the shift register
		PORTB |= 0x02;
	}
	// set RCLK = 1. Rising edge copies data from “Shift” register to “Storage” register
	PORTB |= 0x04;
	// clears all lines in preparation of a new transmission
	PORTB = 0xF0;
}

int main(void)
{
	DDRB = 0xFF; PORTB = 0x00;
	
    unsigned char cnt = 9;
	
	TimerSet(1000);
	TimerOn();
	
    while(1) {
	    // Scheduler code
		
		transmit_data( Write7Seg(cnt) );
	    
		if (cnt == 0) {
			cnt = 9;
		}
		else {
			cnt--;
		}
		
	    while(!TimerFlag);
	    TimerFlag = 0;
    }
}

