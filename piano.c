// Piano.c
// This software configures the off-board piano keys
// Lab 6 requires a minimum of 3 keys, but you could have more
// Runs on LM4F120 or TM4C123
// Program written by: put your names here
// Date Created: 3/6/17 
// Last Modified: 3/5/18 
// Lab number: 6
// Hardware connections
// TO STUDENTS "REMOVE THIS LINE AND SPECIFY YOUR HARDWARE********

// Code files contain the actual implemenation for public functions
// this file also contains an private functions and private data
#include <stdint.h>
#include "tm4c123gh6pm.h"
int keysVal;
// **************Piano_Init*********************
// Initialize piano key inputs, called once to initialize the digital ports
// Input: none 
// Output: none
void Piano_Init(void){ volatile unsigned long delay;
	SYSCTL_RCGC2_R |= 0x10;
	delay = SYSCTL_RCGC2_R;
  GPIO_PORTE_AMSEL_R &= ~0x07;        // 3) disable analog on PE2-0
  GPIO_PORTE_DIR_R |= 0x07;          // 5) PE2-0 out
  GPIO_PORTE_AFSEL_R &= ~0x07;        // 6) disable alt funct on PE2-0
  GPIO_PORTE_DEN_R |= 0x07;          // 7) enable digital I/O on PE2-0

}

// **************Piano_In*********************
// Input from piano key inputs 
// Input: none 
// Output: 0 to 7 depending on keys
//   0x01 is just Key0, 0x02 is just Key1, 0x04 is just Key2
//   bit n is set if key n is pressed
uint32_t Piano_In(void){
	keysVal=GPIO_PORTE_DATA_R;
  return keysVal; // Replace with your code
}
