#ifdef __USE_CMSIS
#include "LPC17xx.h"
#include "timer.h"
#include "uart.h"
#include "extint.h"
#include "type.h"
#include <time.h>
#endif
#include <cr_section_macros.h>
#include <stdio.h>
#define IRC_OSC ( 4000000UL)
uint32_t i, j;
int x;
extern uint32_t timer0_m0_counter, timer1_m0_counter;
extern uint32_t timer0_m1_counter, timer1_m1_counter;
int startBuf1[6];

uint32_t milliseconds = 0;	//variable that stores the "time"
uint32_t startingTime[6];	//array that stores starting times
uint32_t endingTime[6];	//array that stores ending times
uint32_t totalTime[5];	//array that holds the difference of endingTime and startingTime
uint32_t SystemCoreClock;

int numberOfTests = 0;

int main(void)
{
	printf("Test Starting\n"); // Force the counter to be placed into memory
	LPC_GPIO2->FIODIR = 0x000000FF; /* P2.xx defined as Outputs */
	LPC_GPIO2->FIOCLR = 0x000000FF; /* turn off all the LEDs */ //2:33PM
	int a = 0;
	int i = 0;
	int c = 0;
	int average, average2;
	int sum1;
	int sum2;
	int standarddev;
		//int a = 0;
		LPC_GPIO2->FIOSET = 1 << 4;

		for(i = 0; i < 6; i++)
		{
			init_timer(0, 2000);
			reset_timer(0);
			enable_timer(0);
			//x= rand() % 5000;
			LPC_GPIO2->FIOSET = 1 << 0; //YELLOW LED
			x= rand() % 7500;
			delayMs(1, x);
			//x= rand() % 5000;
			LPC_GPIO2->FIOCLR = 1<< 0;  //YELLOW LED
			delayMs(1, x);
			if(i<=4)
			{
				printf("Press Button\n", x);
			}
			EINTInit();
		}
		meananddeviation();
		LPC_GPIO2->FIOCLR = 1 << 4;
		printf("Done!\n");
	return 0 ;
}
