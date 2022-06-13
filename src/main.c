

#include "core/core.h"
#include "core/gpio.h"

#include "usb/usb.h"
#include "usb/hid.h"




_constructor(100, app_main)
_thread(0, app)


void app_main()
{

	TRIS_B(0) = 0;
	GPIO_B(0) = 1;

	//usb_mode(usb_enable);

}



void app()
{

//	word n;

//	for (n=65535; n > 0; n--);
	msleep(250);
	msleep(250);

	GPIO_B(0) ^= 1;

}

