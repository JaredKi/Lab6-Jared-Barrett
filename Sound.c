// Sound.c
// This module contains the SysTick ISR that plays sound
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
#include "dac.h"
#include "tm4c123gh6pm.h"
#include "Sound.h"
	uint8_t idx;
	uint8_t sine[32] = {8, 9, 11, 12, 13, 13, 14, 14, 15, 14, 14, 13, 13, 12, 11, 9, 8, 7, 5, 4, 3, 3,  2, 2, 1, 2, 2, 3, 3, 4, 5, 7};
	
	
// **************Sound_Init*********************
// Initialize digital outputs and SysTick timer
// Called once, with sound/interrupts initially off
// Input: none
// Output: none
void Sound_Init(void){
	DAC_Init();
	NVIC_ST_CTRL_R = 0;               // disable SysTick during setup
	NVIC_ST_RELOAD_R = 0x0000FFFF;
	NVIC_ST_CURRENT_R = 0;
	NVIC_SYS_PRI3_R = (NVIC_SYS_PRI3_R&0x00FFFFFF) | 0x40000000; //PRIORITY 2
	NVIC_ST_CTRL_R = 0x00000007;      // enable SysTick with core clock
}

void SysTick_Handler(){
	DAC_Out(sine[idx]);
	idx=(idx+1)%32;
}
// **************Sound_Play*********************
// Start sound output, and set Systick interrupt period 
// Sound continues until Sound_Play called again
// This function returns right away and sound is produced using a periodic interrupt
// Input: interrupt period
//           Units of period to be determined by YOU
//           Maximum period to be determined by YOU
//           Minimum period to be determined by YOU
//         if period equals zero, disable sound output
// Output: none
void Sound_Play(uint32_t period){
	NVIC_ST_RELOAD_R=period;
}



