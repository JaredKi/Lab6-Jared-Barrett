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
int keysVal2;
//	uint32_t note, notearray[29] = {A,B,C,D,E,F,G};
//	uint32_t time, timearray[29] = {500,500,500,500,500,500};
// basic functions defined at end of startup.s
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts

int main(void){volatile unsigned long delay;
	
	SYSCTL_RCGC2_R |= 0x31;
	delay = SYSCTL_RCGC2_R;
  GPIO_PORTF_LOCK_R = 0x4C4F434B;   // 2) unlock GPIO Port F
	GPIO_PORTF_CR_R = 0x1F;						//unlock ports
  GPIO_PORTF_AMSEL_R &= ~0x0E;        // 3) disable analog on PF3-1
  GPIO_PORTF_PCTL_R &= ~0x0E;   // 4) PCTL GPIO on PF3-1
  GPIO_PORTF_DIR_R |= 0x0E;          // 5) PF3-1 out
  GPIO_PORTF_AFSEL_R &= ~0x0E;        // 6) disable alt funct on PF3-1
  GPIO_PORTF_DEN_R |= 0x0E;          // 7) enable digital I/O on PF3-1
	
  TExaS_Init(SW_PIN_PE3210,DAC_PIN_PB3210,ScopeOn);    // bus clock at 80 MHz
  Piano_Init();
  Sound_Init();
  // other initialization
  EnableInterrupts();
  while(1){ 
	GPIO_PORTF_DATA_R ^= 0x04;
	keysVal2=Piano_In();
		if(keysVal2 == 0x01)
			Sound_Play(B);
		if(keysVal2 == 0x02)
			Sound_Play(2129);
		if(keysVal2 == 0x04)
			Sound_Play(A);
		if(keysVal2 == 0x08)
			Sound_Play(F);
//		if(keysVal2 == 0x08){
//			for(int i=0;i<29;i++){
//				Timer5A_Init(timearray[i]);
//			}
//  }  
	}
}  


void Timer5A_Init(unsigned short period){ volatile unsigned long Delay;
  SYSCTL_RCGCTIMER_R |= 0x20;      // 0) activate timer5
  Delay = 0;                       // wait for completion
  TIMER5_CTL_R &= ~0x00000001;     // 1) disable timer5A during setup
  TIMER5_CFG_R = 0x00000004;       // 2) configure for 16-bit timer mode
  TIMER5_TAMR_R = 0x00000002;      // 3) configure for periodic mode, default down-count settings
  TIMER5_TAILR_R = period-1;       // 4) reload value
  TIMER5_TAPR_R = 49;              // 5) 1us timer5A
  TIMER5_ICR_R = 0x00000001;       // 6) clear timer5A timeout flag
  TIMER5_IMR_R |= 0x00000001;      // 7) arm timeout interrupt
  NVIC_PRI23_R = (NVIC_PRI23_R&0xFFFFFF00)|0x00000040; // 8) priority 2
  NVIC_EN2_R = 0x10000000;         // 9) enable interrupt 19 in NVIC
  // vector number 108, interrupt number 92
  TIMER5_CTL_R |= 0x00000001;      // 10) enable timer5A
// interrupts enabled in the main program after all devices initialized
}

//				unsigned long Count2=0;
//				void Timer5A_Handler(void){ // interrupts after each block is transferred
//				TIMER5_ICR_R = TIMER_ICR_TATOCINT; // acknowledge timer5A timeout
//				Count2++;
//				}
				
				

