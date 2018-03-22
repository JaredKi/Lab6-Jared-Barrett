// Lab6.c
// Runs on LM4F120 or TM4C123
// Use SysTick interrupts to implement a 3-key digital piano
// MOOC lab 13 or EE319K lab6 starter
// Program written by: put your names here
// Date Created: 3/6/17 
// Last Modified: 3/5/18 
// Lab number: 6
// Hardware connections
// TO STUDENTS "REMOVE THIS LINE AND SPECIFY YOUR HARDWARE********


#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "Sound.h"
#include "Piano.h"
#include "TExaS.h"
#include "DAC.h"

// basic functions defined at end of startup.s
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts

int main(void){
	
	SYSCTL_RCGC2_R |= 0x31;
	while(SYSCTL_RCGC2_R == 0){}
  GPIO_PORTF_LOCK_R = 0x4C4F434B;   // 2) unlock GPIO Port F
	GPIO_PORTF_CR_R = 0x1F;						//unlock ports
  GPIO_PORTF_AMSEL_R &= ~0x0E;        // 3) disable analog on PF3-1
  GPIO_PORTF_PCTL_R &= ~0x0E;   // 4) PCTL GPIO on PF3-1
  GPIO_PORTF_DIR_R |= 0x0E;          // 5) PF3-1 out
  GPIO_PORTF_AFSEL_R &= ~0x0E;        // 6) disable alt funct on PF3-1
  GPIO_PORTF_DEN_R |= 0x0E;          // 7) enable digital I/O on PF3-1
	GPIO_PORTA_AMSEL_R &= ~0x1C;        // 8) disable analog on PA4-2
  GPIO_PORTA_DIR_R &= ~0x1C;          // 9) PA4-2 input
  GPIO_PORTA_AFSEL_R &= ~0x1C;        // 10) disable alt funct on PA4-2
  GPIO_PORTA_DEN_R |= 0x1C;          // 11) enable digital I/O on PA4-2
	GPIO_PORTE_AMSEL_R &= ~0x3F;        // 12) disable analog on PE5-0
  GPIO_PORTE_DIR_R |= 0x3F;          // 13) PE5-0 output
  GPIO_PORTE_AFSEL_R &= ~0x3F;        // 14) disable alt funct on PE5-0
  GPIO_PORTE_DEN_R |= 0x3F;          // 15) enable digital I/O on PE5-0
  TExaS_Init(SW_PIN_PE3210,DAC_PIN_PB3210,ScopeOn);    // bus clock at 80 MHz
  Piano_Init();
  Sound_Init();
  // other initialization
  EnableInterrupts();
	idx = 0;
  DAC_Init();

  while(1){ 
		GPIO_PORTF_DATA_R ^= 0x04;
	Piano_In();
		Sound_Play(3794);
  }    

}

