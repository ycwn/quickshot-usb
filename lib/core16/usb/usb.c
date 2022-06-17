

#include "core/core.h"
#include "core/signal.h"
#include "core/thunk.h"

#include "usb/usb.h"
#include "usb/usb_ep0.h"


USB_MODULE


char                  usb_device_status;
usb_endpoint_transfer usb_transfer;

volatile usb_memory_space __at(0x0400) usb;



void usb_mode(byte mode)
{

	UIE  = 0x00;
	UEIE = 0x00;
	UIR  = 0x00;
	UEIR = 0x00;

	PIE2bits.USBIE = 0;

	if (mode) {

//		memset(&usb, 0, sizeof(usb_memory_space));

		UCFG = 0x14;
		UCON = 0x08;

		UIE  = 0x7f;
		UEIE = 0x9f;

		IPR2bits.USBIP = 1;
		PIR2bits.USBIF = 0;
		PIE2bits.USBIE = 1;

	} else {

		UCON = 0x0;
		UCFG = 0x0;

	}

	while (UCONbits.SE0);

}



void usb_handle_generic()
{

	PIR2bits.USBIF = 0;

}



void usb_handle_error()
{

	UEIR = 0x00;
	UIRbits.UERRIF = 0;

}



void usb_handle_start_of_frame()
{

	UIRbits.SOFIF = 0;

}



void usb_handle_idle()
{

	UCONbits.SUSPND = 1;
	UIRbits.IDLEIF = 0;

}



void usb_handle_active()
{

	UCONbits.SUSPND = 0;
	UIRbits.ACTVIF = 0;

}



void usb_handle_stall()
{

#if USB_ENDPOINTS >= 1

	usb_ep0_reset();

#elif USB_ENDPOINTS >= 2

	usb_ep1_reset();

#elif USB_ENDPOINTS >= 3

	usb_ep2_reset();

#elif USB_ENDPOINTS >= 4

	usb_ep3_reset();

#elif USB_ENDPOINTS >= 5

	usb_ep4_reset();

#elif USB_ENDPOINTS >= 6

	usb_ep5_reset();

#elif USB_ENDPOINTS >= 7

	usb_ep6_reset();

#elif USB_ENDPOINTS >= 8

	usb_ep7_reset();

#endif

	usb_transfer.status = usb_transfer_status_idle;

	UIRbits.STALLIF = 0;

}



void usb_handle_reset()
{

	while (UIRbits.TRNIF != 0)
		UIRbits.TRNIF = 0;

	UEP0 = 0;
	UEP1 = 0;
	UEP2 = 0;
	UEP3 = 0;
	UEP4 = 0;
	UEP5 = 0;
	UEP6 = 0;
	UEP7 = 0;
	UEP8 = 0;
	UEP9 = 0;
	UEP10 = 0;
	UEP11 = 0;
	UEP12 = 0;
	UEP13 = 0;
	UEP14 = 0;
	UEP15 = 0;

	usb_set_address(0);
	usb_set_status(usb_device_powered);

	UIR  = 0x00;
	UEIR = 0x00;

	usb_transfer.source.rom  = NULL;
	usb_transfer.length      = 0;
	usb_transfer.status      = usb_transfer_status_idle;

	usb_ep0_reset();

}



void usb_handle_transfer()
{

//	byte bd_number = (USTAT >> 2) & 0x1f;

	if ((USTAT & 0x78) == 0x00)
		if (USB_SETUP(0)) {

			usb_transfer.status = usb_transfer_status_idle;

			usb_ep0_setup();
			usb_finalize_setup_transfer();

		} else if (USB_IN(0)) {

			usb_ep0_in();
			usb_finalize_in_transfer();

		} else if (USB_OUT(0)) {

			usb_ep0_out();
			usb_finalize_out_transfer();

		}

	UIRbits.TRNIF = 0;

}



void usb_finalize_setup_transfer()
{

	UCONbits.PKTDIS = 0;

	if (usb_transfer.status == usb_transfer_status_out) {

		usb.endpoint[0].out.count  = USB_BUFFER_SIZE;
		usb.endpoint[0].out.status = 0x80;

		usb.endpoint[0].in.count  = 0;
		usb.endpoint[0].in.status = 0xc8;

	} else if (usb_transfer.status == usb_transfer_status_in_code ||
				usb_transfer.status == usb_transfer_status_in_data) {

		usb.endpoint[0].out.count  = USB_BUFFER_SIZE;
		usb.endpoint[0].out.status = 0x80;

		usb.endpoint[0].in.status &= ~0x40;

		usb_finalize_in_transfer();

	} else if (usb_transfer.status == usb_transfer_status_acknowledge) {

		usb.endpoint[0].out.count  = USB_BUFFER_SIZE;
		usb.endpoint[0].out.status = 0x80;

		usb.endpoint[0].in.count  = 0;
		usb.endpoint[0].in.status = 0xc8;

		usb_transfer.status = usb_transfer_status_idle;

	} else {

		usb.endpoint[0].out.count  = USB_BUFFER_SIZE;
		usb.endpoint[0].out.status = 0x84;

		usb.endpoint[0].in.status = 0x84;

	}

}



void usb_finalize_in_transfer()
{

	byte n;


	if (usb_transfer.status != usb_transfer_status_in_code &&
		usb_transfer.status != usb_transfer_status_in_data)
		return;

	if (usb_transfer.length < USB_BUFFER_SIZE)
		usb.endpoint[0].in.count = usb_transfer.length;

	else
		usb.endpoint[0].in.count = USB_BUFFER_SIZE;

	usb_transfer.length -= usb.endpoint[0].in.count;


	if (usb_transfer.status == usb_transfer_status_in_code)
		for (n=0; n < usb.endpoint[0].in.count; n++)
			usb.buffer[0].in[n] = *usb_transfer.source.rom++;

	else
		for (n=0; n < usb.endpoint[0].in.count; n++)
			usb.buffer[0].in[n] = *usb_transfer.source.ram++;

	usb.endpoint[0].out.count  = USB_BUFFER_SIZE;
	usb.endpoint[0].out.status = 0x80;

	usb.endpoint[0].in.buffer = usb.buffer[0].in;
	usb.endpoint[0].in.status = (usb.endpoint[0].in.status & 0x40)? 0x88: 0xc8;

}



void usb_finalize_out_transfer()
{

	usb.endpoint[0].out.count  = USB_BUFFER_SIZE;
	usb.endpoint[0].out.buffer = usb.buffer[0].out;
	usb.endpoint[0].out.status = (usb.endpoint[0].out.status & 0x40)? 0x88: 0xc8;

}




void usb_transfer_acknowledge()
{

	usb_transfer.source.rom = NULL;
	usb_transfer.length     = 0;
	usb_transfer.status     = usb_transfer_status_acknowledge;

}



void usb_transfer_in_code(code byte *buffer, word length)
{

	usb_transfer.source.rom = buffer;
	usb_transfer.length     = length;
	usb_transfer.status     = usb_transfer_status_in_code;

}



void usb_transfer_in_data(data byte *buffer, word length)
{

	usb_transfer.source.ram = buffer;
	usb_transfer.length     = length;
	usb_transfer.status     = usb_transfer_status_in_data;

}



void usb_transfer_out(data byte *buffer, word length)
{

	usb_transfer.source.ram = buffer;
	usb_transfer.length     = length;
	usb_transfer.status     = usb_transfer_status_out;

}

