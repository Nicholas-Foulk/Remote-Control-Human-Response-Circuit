/****************************************************************************
 *   $Id:: extint.c 5670 2010-11-19 01:33:16Z usb00423                      $
 *   Project: NXP LPC17xx EINT example
 *
 *   Description:
 *     This file contains EINT code example which include EINT 
 *     initialization, EINT interrupt handler, and APIs for EINT.
 *
 ****************************************************************************
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * products. This software is supplied "AS IS" without any warranties.
 * NXP Semiconductors assumes no responsibility or liability for the
 * use of the software, conveys no license or title under any patent,
 * copyright, or mask work right to the product. NXP Semiconductors
 * reserves the right to make changes in the software without
 * notification. NXP Semiconductors also make no representation or
 * warranty that such application will be suitable for the specified
 * use without further testing or modification.
****************************************************************************/
#include "lpc17xx.h"
#include "type.h"
#include "extint.h"
#include "timer.h"
#include "uart.h"
#include <time.h>
#include "math.h"
//#include "stdio.h"
volatile uint32_t eint0_counter;
extern uint32_t timer0_m0_counter, timer1_m0_counter;
extern uint32_t timer0_m1_counter, timer1_m1_counter;
int resultBuf[6];
int resultBuf2[6];
int i=0;
int numberOfTests1=0;
uint32_t endingTime[6];	//array that stores ending times
/*****************************************************************************
** Function name:		EINT0_Handler
**
** Descriptions:		external INT handler
**
** parameters:			None
** Returned value:		None
** 
*****************************************************************************/

void meananddeviation()
{
	int avg, sum, sum2, stddev;
	sum = 0;
	avg = 0;
	for(i = 0; i < 6; i++)
	{
		sum += resultBuf[i];
	}

	avg = sum/6;
	printf("The average is %d\n", avg);

	for(i = 0; i < 6; i++)
	{
		sum2 += ((resultBuf[i] - avg)*(resultBuf[i] - avg));
	}
	sum2=sum2/6;

	stddev = sqrt(sum2);
	printf("The standard Deviation is %d\n", stddev);

}

void EINT0_IRQHandler (void)
{
     LPC_SC->EXTINT = EINT0;		/* clear interrupt */

     eint0_counter++;
     if(eint0_counter & 0x01)
     {
    	 //LPC_GPIO2->FIOSET = 0x000000F0;	/* turn on P2.0*/
    	 LPC_GPIO2->FIOCLR = 0x000000F0;	/* turn off P2.4 */
    	 disable_timer(0);
     }
     else
     {
	 LPC_GPIO2->FIOCLR = 1 << 0;

	 //LPC_GPIO2->FIOSET = 0x000000F0;	/* turn on P2.0*/
	 //LPC_GPIO2->FIOCLR = 0x0000000F;	/* turn off P2.4 */

	 //printf("%d\n",timer0_m0_counter);
	// resultBuf[i] = timer0_m0_counter;  removed 11/24/15 10:54 PM

	 printf("%d\n",timer0_m0_counter++);
  	 resultBuf[i] = timer0_m0_counter++;
  	 i++;
  	 disable_timer(0);
     }
	// resultBuf2[i]=timer0_m0_counter;
//	 endingTime[numberOfTests1] = timer0_m0_counter;
//	 timer0_m0_counter++;
	 //i++;
	 //disable_timer(0);
 	 LPC_GPIOINT->IO2IntClr = 0xFFFFFFFF;
 	 LPC_GPIOINT->IO0IntClr = 0xFFFFFFFF;

//     eint0_counter++;
// if ( eint0_counter & 0x01 )	/* alternate the LED display */
// {
//	 LPC_GPIO2->FIOSET = 1 << 4;
//	 //LPC_GPIO2->FIOSET = 0x0000000F;	/* turn off P2.0~3 */
//	 //LPC_GPIO2->FIOCLR = 0x000000F0;	/* turn on P2.4~7 */
//	//printf("%d\n",timer0_m0_counter++);
//	disable_timer(0);
// }
// else
// {
//	 LPC_GPIO2->FIOCLR = 1 << 0;
//	//LPC_GPIO2->FIOSET = 0x000000F0;	/* turn on P2.0*/
//	//LPC_GPIO2->FIOCLR = 0x0000000F;	/* turn off P2.4 */
//	 printf("%d\n",timer0_m0_counter);
//	 resultBuf[i] = timer0_m0_counter;
////	printf("%d\n",timer0_m0_counter++);
////	resultBuf[i] = timer0_m0_counter++;
//	//i++;
//	disable_timer(0);
// }
// 	 LPC_GPIOINT->IO2IntClr = 0xFFFFFFFF;
// 	 LPC_GPIOINT->IO0IntClr = 0xFFFFFFFF;
// 	 i++;
}





/*****************************************************************************
** Function name:		EINTInit
**
** Descriptions:		Initialize external interrupt pin and
**						install interrupt handler
**
** parameters:			None
** Returned value:		true or false, return false if the interrupt
**						handler can't be installed to the VIC table.
** 
*****************************************************************************/
uint32_t EINTInit( void )
{
  LPC_PINCON->PINSEL4 = 0x00100000;	/* set P2.10 as EINT0 and P2.0~7 GPIO output */

  //LPC_GPIO2->FIODIR = 0x000000FF;	/* port 2, bit 0~7 only */
  //LPC_GPIO2->FIOCLR = 0x000000FF;	/* turn off LEDs */

  LPC_GPIO2->FIOCLR = 1 << 0;
  LPC_GPIOINT->IO2IntEnF = 0x200;	/* Port2.10 is falling edge. */
  LPC_SC->EXTMODE = EINT0_EDGE;		/* INT0 edge trigger */
  LPC_SC->EXTPOLAR = 0;				/* INT0 is falling edge by default */

  NVIC_EnableIRQ(EINT0_IRQn);
  return( TRUE );
}

/******************************************************************************
**                            End Of File
******************************************************************************/


