#include <msp430.h>

int main(void)
{
  WDTCTL = WDTPW | WDTHOLD;                 // Stop watchdog timer
  P1DIR |= 0xff;
  P1OUT = 0x00;
  P1REN = 0X00;
  P1DIR |= BIT0;                       		// Set  P1.0 to output direction
  P1DIR &= ~ BIT3;							// set p1.3 as input
  P1REN |= BIT3;								// enabling pull up/pull down
  P1OUT |=BIT3;								// set pull up for p1.3
  P1IE |= BIT3;                             // P1.3 interrupt enabled
  P1IES |= BIT3;                            // P1.3 Hi/lo edge
  P1IFG &= ~BIT3;                           // P1.3 IFG cleared

   __bis_SR_register(LPM4_bits | GIE);       // Enter LPM4 w/interrupt

}

// Port 1 interrupt service routine
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
	if(P1IFG & BIT3)
  {
		volatile int i =10;
		while(i>0)
		{
		P1OUT ^= BIT0;                            // P1.0 = toggle
		__delay_cycles(100000);
		i-- ;
		}
  }
  P1IFG &= ~BIT3;                           // P1.2 IFG cleared
}
