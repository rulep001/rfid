#include <avr/io.h>
#include "bit.h" //keypad
#include "io.c" //LCD display
#include <avr/interrupt.h>
#include "timer.h"
#include <stdio.h>
#include "seven_seg.h"
#include "usart.h"

/* Global Functions */

//-------- GetKeypadKey function --------------------------------------------------

//-------- Find GCD function --------------------------------------------------
unsigned long int findGCD(unsigned long int a, unsigned long int b) {
	unsigned long int c;
	while(1){
		c = a%b;
		if(c==0){return b;}
		a = b;
		b = c;
	}
	return 0;
}

//-------- TransmitData function --------------------------------------------------
void transmit_data(unsigned char data) {
	int i;
	for (i = 0; i < 8; ++i) {
		// Sets SRCLR to 1 allowing data to be set
		// Also clears SRCLK in preparation of sending data
		PORTB = (PORTB & 0xF0) | 0x08;
		// set SER = next bit of data to be sent.
		PORTB |= ((data >> i) & 0x01);
		// set SRCLK = 1. Rising edge shifts next bit of data into the shift register
		PORTB |= 0x02;
	}
	// set RCLK = 1. Rising edge copies data from ?Shift? register to ?Storage? register
	PORTB |= 0x04;
	// clears all lines in preparation of a new transmission
	PORTB = (PORTB & 0xF0) | 0x00;
}

//--------Task scheduler data structure---------------------------------------
// Struct for Tasks represent a running process in our simple real-time operating system.
typedef struct _task {
	/*Tasks should have members that include: state, period,
		a measurement of elapsed time, and a function pointer.*/
	signed char state; //Task's current state
	unsigned long int period; //Task period
	unsigned long int elapsedTime; //Time elapsed since last task tick
	int (*TickFct)(int); //Task tick function
} task;

//--------Shared Variables----------------------------------------------------
unsigned char lock_bit = 0;
unsigned char count = 5;

//--------User defined FSMs---------------------------------------------------
//Enumeration of states.

enum LockingControl_States {Lock, Unlock_Failed, Unlock_Success};
enum RFID_States {RFID};
enum SevenSeg_States {Wait_SevenSeg, Countdown};

//State Machine Actions

int LockingControl_Tick(int state){

	//Local Variables
	static unsigned char lock_count = 0;

	switch(state){
		//transactions
		case Lock:
			if (lock_bit == 0) {
				state = Lock;
			}
			else if (lock_bit == 1) {
				state = Unlock_Success;
			}
			else if (lock_bit == 2) {
				state = Unlock_Failed;
			}
			break;
		case Unlock_Failed:
			if (lock_count < 3) {
				state = Unlock_Failed;
			}
			else if ( !(lock_count < 3) ) {
				state = Lock;
			}
			break;
		case Unlock_Success:
			if (lock_count < 5) {
				state = Unlock_Success;
			}
			else if ( !(lock_count < 5) ) {
				state = Lock;
			}
			break;
	}
	switch(state){
		//actions
		case Lock:
			LCD_DisplayString(1, "Locked");
			PORTB = (PORTB & 0x0F) | 0x20;
			lock_count = 0;
			lock_bit = 0;
		break;
		case Unlock_Failed:
			LCD_DisplayString(1, "Incorrect Key");
			PORTB = (PORTB & 0x0F) | 0x80;
			lock_count++;
		break;
		case Unlock_Success:
			LCD_DisplayString(1, "Unlocked!");
			PORTB = (PORTB & 0x0F) | 0x50;
			lock_count++;
		break;
	}
	return state;
}

int RFID_Tick(int state){

	//Local variables
    unsigned char* auth1[5];
	unsigned char* auth2[5];
	unsigned char rfid[5];
	strcpy(auth1, "DEDF");
	strcpy(auth2, "ADED");

	unsigned char tag = 0;
	unsigned char tag1[13];
	unsigned char cnt = 0;
	unsigned char c = 0;
	unsigned char check1 = 2;
	unsigned char check2 = 2;

	switch(state) {
		case RFID:

			while (cnt <= 12 && lock_bit == 0) {
				transmit_data(0xFF);
				if ( USART_HasReceived(0) ) {
					tag = USART_Receive(0);
					USART_Flush(0);
					tag1[c] = tag;
					c++;
					cnt++;
				}
			}

		    rfid[0] = tag1[8];
		    rfid[1] = tag1[9];
		    rfid[2] = tag1[10];
		    rfid[3] = tag1[11];
		    rfid[4] = '\0';

		    if (cnt == 13) {
			    check1 = strcmp(rfid, auth1);
				check2 = strcmp(rfid, auth2);
			    if(check1 == 0 || check2 == 0){
				    lock_bit = 1;
				    check1 = 2;
					check2 = 2;
					c = 0;
					cnt = 0;
			    }
			    else {
				    lock_bit = 2;
					check1 = 2;
					check2 = 2;
					c = 0;
					cnt = 0;
			    }
				//LCD_DisplayString(1,rfid);
				memset(tag1, 0, sizeof tag1);
		    }
		break;
	}
	return state;
}

int SevenSeg_Tick(int state){

	//Local Variables

	switch(state){
		//transactions
		case Wait_SevenSeg:
			if (lock_bit == 1) {
				state = Countdown;
			}
			else if ( !(lock_bit == 1) ) {
				state = Wait_SevenSeg;
			}
		break;
		case Countdown:
			if (count > 0) {
				state = Countdown;
			}
			else if ( count <= 0 ) {
				transmit_data(0xFF);
				count = 5;
				state = Wait_SevenSeg;
			}
		break;
	}
	switch(state){
		//actions
		case Wait_SevenSeg:
			transmit_data(0xFF);
		break;
		case Countdown:
			if (count >= 0) {
				transmit_data(Write7Seg(count--));
			}
		break;
	}
	return state;
}

// --------END User defined FSMs-----------------------------------------------

// Implement scheduler code from PES.

int main(void)
{
	//Declare inputs and outputs
	DDRB = 0xFF; PORTB = 0x00; // PORTB set to output, outputs init 0s
	DDRC = 0xFF; PORTC = 0x00; // PORTC set to output, outputs init 0s
	DDRD = 0xFE; PORTD = 0x01; // PORTD set to output, outputs init 0s

	//Period for the tasks
	unsigned long int LockingControl_calc = 1000;
	unsigned long int RFID_calc = 200;
	unsigned long int SevenSeg_calc = 1000;

	//Calculating GCD
	unsigned long int tmpGCD = 1;
	tmpGCD = findGCD(LockingControl_calc, tmpGCD);
	tmpGCD = findGCD(RFID_calc, tmpGCD);
	tmpGCD = findGCD(SevenSeg_calc, tmpGCD);

	//Greatest common divisor for all tasks or smallest time unit for tasks.
	unsigned long int GCD = tmpGCD;

	//Recalculate GCD periods for scheduler
	unsigned long int LockingControl_period = LockingControl_calc/GCD;
	unsigned long int RFID_period = RFID_calc/GCD;
	unsigned long int SevenSeg_period = SevenSeg_calc/GCD;

	//Declare an array of tasks
	static task task1;
	static task task2;
	static task task3;
	task *tasks[] = { &task1, &task2, &task3 };
	const unsigned short numTasks = sizeof(tasks)/sizeof(task*);

	// Task 1
	task1.state = Lock;//Task initial state.
	task1.period = LockingControl_period;//Task Period.
	task1.elapsedTime = LockingControl_period;//Task current elapsed time.
	task1.TickFct = &LockingControl_Tick;//Function pointer for the tick.

	// Task 2
	task2.state = Wait_SevenSeg;//Task initial state.
	task2.period = SevenSeg_period;//Task Period.
	task2.elapsedTime = SevenSeg_period;//Task current elapsed time.
	task2.TickFct = &SevenSeg_Tick;//Function pointer for the tick.

	// Task 3
	task3.state = RFID;//Task initial state.
	task3.period = RFID_period;//Task Period.
	task3.elapsedTime = RFID_period;//Task current elapsed time.
	task3.TickFct = &RFID_Tick;//Function pointer for the tick.

	// Initialize USART
	initUSART(0);
	LCD_init();

	// Set the timer and turn it on
	TimerSet(GCD);
	TimerOn();

	unsigned short i; // Scheduler for-loop iterator

	while(1) {

		// Scheduler code
		for ( i = 0; i < numTasks; i++ ) {
			// Task is ready to tick
			if ( tasks[i]->elapsedTime == tasks[i]->period ) {
				// Setting next state for task
				tasks[i]->state = tasks[i]->TickFct(tasks[i]->state);
				// Reset the elapsed time for next tick.
				tasks[i]->elapsedTime = 0;
			}
			tasks[i]->elapsedTime += 1;
		}
		while(!TimerFlag);
		TimerFlag = 0;
	}

	// Error: Program should not exit!
	return 0;
}
