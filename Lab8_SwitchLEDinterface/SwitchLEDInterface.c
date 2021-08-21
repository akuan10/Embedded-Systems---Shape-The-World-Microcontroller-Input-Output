// ***** 0. Documentation Section *****
// SwitchLEDInterface.c for Lab 8
// Runs on LM4F120/TM4C123
// Use simple programming structures in C to toggle an LED
// while a button is pressed and turn the LED on when the
// button is released.  This lab requires external hardware
// to be wired to the LaunchPad using the prototyping board.
// January 15, 2016
//      Jon Valvano and Ramesh Yerraballi

// ***** 1. Pre-processor Directives Section *****
#include "TExaS.h"
#include "tm4c123gh6pm.h"
//not need define PortE because tm4c123gh6pm already defined
#define PE0 (*((volatile unsigned long *)0x40024004))
#define PE1 (*((volatile unsigned long *)0x40024008))
// ***** 2. Global Declarations Section *****
unsigned long In;
// FUNCTION PROTOTYPES: Each subroutine defined
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
void PortE_Init(void);
void PortB_Init(void);
void PortA_Init(void);
void Delay(void);
// ***** 3. Subroutines Section *****

// PE0, PB0, or PA2 connected to positive logic momentary switch using 10k ohm pull down resistor
// PE1, PB1, or PA3 connected to positive logic LED through 470 ohm current limiting resistor
// To avoid damaging your hardware, ensure that your circuits match the schematic
// shown in Lab8_artist.sch (PCB Artist schematic file) or 
// Lab8_artist.pdf (compatible with many various readers like Adobe Acrobat).
int main(void){ 
//**********************************************************************
// The following version tests input on PE0 and output on PE1
//**********************************************************************
  TExaS_Init(SW_PIN_PE0, LED_PIN_PE1, ScopeOn);  // activate grader and set system clock to 80 MHz

	//PortA_Init();
	//PortB_Init();
	PortE_Init();
  
	EnableInterrupts();           // enable interrupts for the grader
	//input PE0, output PE1
	//input PB0, output PB1 
	//input PA2, output PA3
	
	GPIO_PORTE_DATA_R = 0x02;	
	
  while(1){
		Delay();
		//In = GPIO_PORTA_DATA_R&0x04;
		//In = GPIO_PORTB_DATA_R&0x01;
		In = GPIO_PORTE_DATA_R&0x01;
		if (In)
		{
			//GPIO_PORTA_DATA_R ^= 0x08;
			//GPIO_PORTB_DATA_R ^= 0x02; 
			GPIO_PORTE_DATA_R ^= 0x02;	
			Delay();	
		}
		else
		{
			//GPIO_PORTA_DATA_R |= 0x08;
			//GPIO_PORTB_DATA_R |= 0x02;
			GPIO_PORTE_DATA_R |= 0x02;
		}
  }
  
}
void PortE_Init(void)
{
	volatile unsigned long delay;
	SYSCTL_RCGC2_R |= 0x00000010; //chart on notion
	delay = SYSCTL_RCGC2_R;
	GPIO_PORTE_AMSEL_R &= 0x00;        // 2) disable analog function
  GPIO_PORTE_PCTL_R &= 0x00000000;   // 3) GPIO clear bit PCTL  
	GPIO_PORTE_DIR_R &= ~0x01;         // PE0 input 1111 1110 ! = 0000 0001
  GPIO_PORTE_DIR_R |= 0x02;          // PE1 output 0000 0010
  GPIO_PORTE_AFSEL_R &= 0x00;        // 5) no alternate function
	GPIO_PORTE_DEN_R |= 0x03;          // 7) 0000 0011 
}
void PortB_Init(void)
{
	volatile unsigned long delay;
	SYSCTL_RCGC2_R |= 0x00000002; //chart on notion
	delay = SYSCTL_RCGC2_R;
	GPIO_PORTB_AMSEL_R &= 0x00;        // 2) disable analog function
  GPIO_PORTB_PCTL_R &= 0x00000000;   // 3) GPIO clear bit PCTL  
	GPIO_PORTB_DIR_R = 0x02;
  GPIO_PORTB_AFSEL_R &= 0x00;        // 5) no alternate function
	GPIO_PORTB_DEN_R |= 0x03;          // 7) 0000 0011 
}
void PortA_Init(void)
{
	volatile unsigned long delay;
	SYSCTL_RCGC2_R |= 0x00000001; //chart on notion
	delay = SYSCTL_RCGC2_R;
	GPIO_PORTA_AMSEL_R &= 0x00;        // 2) disable analog function
  GPIO_PORTA_PCTL_R &= 0x00000000;   // 3) GPIO clear bit PCTL  
	GPIO_PORTA_DIR_R = 0x08;          // 0000 "10"00 -> 2 input 3 output
  GPIO_PORTA_AFSEL_R &= 0x00;        // 5) no alternate function
	GPIO_PORTA_DEN_R |= 0x0C;          // 7) 0000 1100 
}
void Delay(void){
	unsigned long volatile time;
	time = 375000; //0.1s
  while(time){
		time--;
  }
}
