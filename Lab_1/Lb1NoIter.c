#include <msp430.h>

const long int SMALL_DELAY = 1000;
const long int BIG_DELAY = 1000;
int flag = 1;

void delay(long int num_of_ops);
void buttonPressHandler();
int getS1State();
int getS2State();
/*
 * main.c
 */
int main(void)
{
  WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

  P1DIR &= ~BIT7; // s1 dir for reading
  P2DIR &= ~BIT2; // s2 dir for reading

  P1DIR |= BIT0; // led 1 dir for write

  P1OUT |= BIT7; // set inactive signal level for button s1
  P2OUT |= BIT2; // set inactive signal level for button s2

  P1REN |= BIT7;
  P2REN |= BIT2;

  P1OUT &= ~BIT0; // led 1 shut down


  while(1)
  {
    buttonPressHandler();
  }

  return 0;
}

void buttonPressHandler()
{
	if (getS2State())
		{
			delay(SMALL_DELAY);
			if(getS2State())
			{
				if (getS1State())
					{
						P1OUT^= BIT0; // turn on led
					}
				 delay(BIG_DELAY);

				while(1)
				{
					if(!getS2State())
						return;
				}
			}
		}
}

void delay(long int num_of_ops)
{
	volatile long int a = 0;
	volatile long int i = 0;
	for(; i < num_of_ops; i++)
	{
		a += i;
	}
}

// 0 - off / 1 - on
int getS1State()
{
	return (P1IN & BIT7) ? 0 : 1;
}

// 0 - off / 1 - on
int getS2State()
{
	return (P2IN & BIT2) ? 0 : 1;
}
