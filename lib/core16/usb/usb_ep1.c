

#include "core/core.h"
#include "core/gpio.h"
#include "core/signal.h"

#include "usb/usb.h"
#include "usb/usb_ep1.h"



void usb_ep1_reset()
{
}



void usb_ep1_configure()
{

	USB_ENDPOINT_CONFIG(1, usb_ep_in | usb_ep_out | usb_ep_handshake | usb_ep_control_disable);

}



void usb_ep1_setup()
{
}



void usb_ep1_in()
{
	static char k;
	char tmp[5];

	tmp[0] = 0xaa;
	tmp[1] = k++;
	tmp[2] = k / 3;
	tmp[3] = 42;
	tmp[4] = 69;

	usb_transfer_in_data(tmp, sizeof(tmp));

}



void usb_ep1_out()
{
}

