

#include "core/core.h"


extern void setup();
extern void loop();


static isr_callback_t isr_hi;
static isr_callback_t isr_lo;



void vector_hi() interrupt(1)
{

	if (isr_hi)
		isr_hi();

}



void vector_lo() interrupt(2)
{

	if (isr_lo)
		isr_lo();

}



void main()
{

	isr_hi = NULL;
	isr_lo = NULL;

	setup();

	while (1)
		loop();

}



isr_callback_t isr_attach(i8 priority, isr_callback_t isrcb)
{

	isr_callback_t oldisr = 0;


	if (priority == ISR_LOW) {

		oldisr = isr_lo;
		isr_lo = isrcb;

	} else if (priority == ISR_HIGH) {

		oldisr = isr_hi;
		isr_hi = isrcb;

	}


	return oldisr;

}

