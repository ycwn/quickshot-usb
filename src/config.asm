

#include <p18cxxx.inc>

	NOLIST
	RADIX DEC


	CONFIG WDT   = OFF
	CONFIG MCLRE = ON
	CONFIG DEBUG = OFF
	CONFIG LVP   = OFF
	CONFIG PLLDIV = 5
	CONFIG CPUDIV = OSC1_PLL2
	CONFIG USBDIV = 2
	CONFIG FOSC   = HSPLL_HS
	CONFIG STVREN = OFF
	CONFIG VREGEN = ON


	END

