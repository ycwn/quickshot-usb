

#include "core/core.h"
#include "core/gpio.h"

#include "usb/usb.h"
#include "usb/hid.h"


USB_DEVICE(0x04d8, 0x0033, 0x0001, 1, 2, 0, 1);


USB_CONFIGURATION(1, 1, 2, 0x80, 50,

	USB_INTERFACE(0, 0, 2, USB_CLASS_HID, 0x00, 0x00, 1),
		USB_HID(1),
		USB_HID_REPORT(0),
		USB_ENDPOINT(0x80, USB_ENDPOINT_INTERRUPT, USB_BUFFER_SIZE, 1),
		USB_ENDPOINT(0x00, USB_ENDPOINT_INTERRUPT, USB_BUFFER_SIZE, 1)

);


USB_STRING_TABLE(

	USB_STRING(1,
		'S', 'E', 'E', ' ', 'Y', 'O', 'U', ' ', 'A', 'T', ' ',
		'T', 'H', 'E', ' ',  'P', 'A', 'R', 'T', 'Y', ' ',
		'R', 'I', 'C', 'H', 'T', 'E', 'R'
	),

	USB_STRING(2,
		'P', 'U', 'T', ' ', 'T', 'H', 'E', ' ',
		'C', 'O', 'O', 'K', 'I', 'E', ' ', 'D', 'O', 'W', 'N'
	)

);


_constructor(100, app_main)
_thread(0, app)



void app_main()
{


	RCONbits.IPEN   = 1;
	INTCONbits.GIEL = 1;
	INTCONbits.GIEH = 1;

	TRIS_B(0) = 0;
	GPIO_B(0) = 1;

	usb_mode(usb_enable);

}



void app()
{

//	word n;

//	for (n=65535; n > 0; n--);
	msleep(250);
	msleep(250);

	GPIO_B(0) ^= 1;

}

