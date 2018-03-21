// dac.c
// This software configures DAC output
// Lab 6 requires a minimum of 4 bits for the DAC, but you could have 5 or 6 bits
// Runs on LM4F120 or TM4C123
// Program written by: put your names here
// Date Created: 3/6/17 
// Last Modified: 3/5/18 
// Lab number: 6
// Hardware connections
// TO STUDENTS "REMOVE THIS LINE AND SPECIFY YOUR HARDWARE********

#include <stdint.h>
#include "tm4c123gh6pm.h"
// Code files contain the actual implemenation for public functions
// this file also contains an private functions and private data

// **************DAC_Init*********************
// Initialize 4-bit DAC, called once 
// Input: none
// Output: none
void DAC_Init(void){volatile unsigned long delay;
  	SYSCTL_RCGC2_R |= 0x02;
	delay = SYSCTL_RCGC2_R;
  GPIO_PORTB_LOCK_R = 0x4C4F434B;   // 2) unlock GPIO Port F
	GPIO_PORTB_CR_R = 0x1F;						//unlock ports
  GPIO_PORTB_AMSEL_R &= ~0x0E;        // 3) disable analog on PF3-1
  GPIO_PORTB_PCTL_R &= ~0x0E;   // 4) PCTL GPIO on PF3-1
  GPIO_PORTB_DIR_R |= 0x0E;          // 5) PF3-1 out
  GPIO_PORTB_AFSEL_R &= ~0x0E;        // 6) disable alt funct on PF3-1
  GPIO_PORTB_DEN_R |= 0x0E;          // 7) enable digital I/O on PF3-1
}

// **************DAC_Out*********************
// output to DAC
// Input: 4-bit data, 0 to 15 
// Input=n is converted to n*3.3V/15
// Output: none
void DAC_Out(uint32_t data){
	GPIO_PORTB_DATA_R = data;
}

