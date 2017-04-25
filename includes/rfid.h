// ---------------------------------
// This file was created by Ryan Ulep to interface and retrieve RFID tag IDs
//      from an ID-12LA tag reader. This file interfaces to the ATMega1284
//      through USART port 0.
// ---------------------------------

#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>
#include "usart.h"

unsigned char RFID_Read() {

    unsigned char* auth[5];
    strcpy(auth, "DEDF");

    unsigned char data = 0;
    unsigned char tag[13];
    unsigned char rfid[5];
    unsigned char cnt = 0;
    unsigned char check = 1;

    if ( USART_HasReceived(0) ) {
    	data = USART_Receive(0);
    	USART_Flush(0);
    	tag[cnt] = data;
    	cnt++;

    	if (cnt == 13) {
    		rfid[0] = tag[8];
    		rfid[1] = tag[9];
    		rfid[2] = tag[10];
    		rfid[3] = tag[11];
    		rfid[4] = '\0';

    		check = strcmp(rfid, auth);

    		if (check == 0) {
    			return 'Y';
    		}
    		else if (check != 0) {
    			return 'N';
    		}
    	}
    }
    return 'F';
}
