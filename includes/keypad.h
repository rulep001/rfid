
// Permission to copy is granted provided that this header remains intact.
// This software is provided with no warranties.

////////////////////////////////////////////////////////////////////////////////

// Returns '\0' if no key pressed, else returns char '1', '2', ... '9', 'A', ...
// If multiple keys pressed, returns leftmost-topmost one
// Keypad must be connected to port A
// Keypad arrangement
//        Px4 Px5 Px6 Px7
//	  col 1   2   3   4
//  row  ______________
//Px0 1	| 1 | 2 | 3 | A
//Px1 2	| 4 | 5 | 6 | B
//Px2 3	| 7 | 8 | 9 | C
//Px3 4	| * | 0 | # | D

#ifndef KEYPAD_H
#define KEYPAD_H

#include <bit.h>

////////////////////////////////////////////////////////////////////////////////
//Functionality - Gets input from a keypad via time-multiplexing
//Parameter: None
//Returns: A keypad button press else '\0'

//--------GetKeypadKey function --------------------------------------------------

unsigned char GetKeypadKey() {

	//had to change the return values
	//of the last two GetBit() cases in each column
	//because of the type of keypad

	PORTA = 0xEF; // Enable col 4 with 0, disable others with 1�s
	asm("nop"); // add a delay to allow PORTC to stabilize before checking
	if (GetBit(PINA,0)==0) { return('1'); }
	if (GetBit(PINA,1)==0) { return('4'); }
	if (GetBit(PINA,2)==0) { return('*'); }
	if (GetBit(PINA,3)==0) { return('7'); }

	// Check keys in col 2
	PORTA = 0xDF; // Enable col 5 with 0, disable others with 1�s
	asm("nop"); // add a delay to allow PORTC to stabilize before checking
	if (GetBit(PINA,0)==0) { return('2'); }
	if (GetBit(PINA,1)==0) { return('5'); }
	if (GetBit(PINA,2)==0) { return('0'); }
	if (GetBit(PINA,3)==0) { return('8'); }

	// Check keys in col 3
	PORTA = 0xBF; // Enable col 6 with 0, disable others with 1�s
	asm("nop"); // add a delay to allow PORTC to stabilize before checking
	if (GetBit(PINA,0)==0) { return('3'); }
	if (GetBit(PINA,1)==0) { return('6'); }
	if (GetBit(PINA,2)==0) { return('#'); }
	if (GetBit(PINA,3)==0) { return('9'); }

	// Check keys in col 4
	PORTA = 0x7F;
	asm("nop");
	if (GetBit(PINA,0)==0) { return('A'); }
	if (GetBit(PINA,1)==0) { return('B'); }
	if (GetBit(PINA,2)==0) { return('D'); }
	if (GetBit(PINA,3)==0) { return('C'); }

	return('\0'); // default value

}

#endif //KEYPAD_H
