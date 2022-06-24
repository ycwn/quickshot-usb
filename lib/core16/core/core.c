

#include "core/core.h"


extern void setup();
extern void loop();



void isr_vector_hi() shadowregs interrupt(1)
{
}



void isr_vector_lo() interrupt(2)
{
}



void main()
{

	setup();

	while (1)
		loop();

}

