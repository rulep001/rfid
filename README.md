# RFID / Passcode Security System

## Introduction
The RFID security system will function similar to a gated entry for a private community. The system can be operated using an RFID tag or by typing in a passcode. The system will meet the following requirements:

* The system can be opened with an RFID chip or by typing in a four digit passcode followed by the (\*) key. A buzzer will beep for 500 ms every time a button is pressed.
* A preset password will be programmed into the array.
Once the first key of the passcode is entered on the keypad, the user has five seconds to enter the remaining characters and press the (\*) key or the system will not unlock.
* If the correct passcode is entered or an RFID tag is swiped, then the buzzer will beep.
* The system will stay unlocked for 5 s to allow an individual entry. After 5s it will automatically relock.
* On the status LED: Blue indicates powered on, red indicates invalid tag or code, green indicates successful unlock.

## Components
* Inputs
    * RFID reader and RFID tags
    * 16-key pad
* Outputs
    * Unlock trigger
    * RGB LED as a status indicator
    * LCD Screen
    * LED bar to output time remaining
    * Alert buzzer

## Complexities
1. Using the LED bar to show time remaining to enter passcode
2. Using the LCD to show the password progress and unlock status
3. Using a buzzer as a response to the user input and to signal an unlock
4. Incorporating an RFID reader and RFID tags
