/*
 * hardware_test_rfid.c
 *
 * Created: 3/7/17 8:14:41 PM
 * Author : Ryan
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>
#include "io.c"
#include "usart.h"

int main(void)
{
	DDRD = 0xFE; PORTD = 0x01; // LCD data lines
	DDRC = 0xFF; PORTC = 0x00;

	unsigned char* auth[5];
	strcpy(auth, "DEDF");

	unsigned char tag = 0;
	unsigned char tag1[13];
	unsigned char rfid[5];
	unsigned char cnt = 0;
	unsigned char c = 0;
	unsigned char check = 2;

	initUSART(0);
	LCD_init();

    while (1)
    {
		if ( USART_HasReceived(0) ) {
			data = USART_Receive(0);
			USART_Flush(0);
			tag1[c] = tag;
			c++;
			cnt++;

			if (cnt > 13) {
				cnt = 0;
				c = 0;
			}

			rfid[0] = tag1[8];
			rfid[1] = tag1[9];
			rfid[2] = tag1[10];
			rfid[3] = tag1[11];
			rfid[4] = '\0';

			if (cnt == 13) {
				check = strcmp(rfid, auth);
				if(check == 0){
					LCD_DisplayString(1, "Correct");
					check = 2;
				}
				else if (check != 0){
					LCD_DisplayString(1, "Incorrect");
					check = 2;
				}
			}
		}
    }
}
