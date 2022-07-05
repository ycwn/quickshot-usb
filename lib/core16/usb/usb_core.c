

#include "core/core.h"
#include "core/gpio.h"

#include "usb/usb.h"
#include "usb/usb_ep0.h"
#include "usb/usb_ep1.h"



// Merge usb_ep0.c into this
// Add callbacks for device, configuration and endpoint events
// Implement a way to handle descriptors in a unified way

char usb_device_status; // This doesnt really do anything, could remove
byte usb_configuration;

//FIXME: This should indicate transfer state per endpoint
usb_endpoint_transfer usb_transfer; // This serves as intermediate state until the transfer finalization occurs

volatile usb_memory_space __at(0x0400) usb; // This should be split in two parts, the Buffer Descriptor SFRs at 0x400, and the USB memory aperture at 0x500



void usb_mode(int mode)
{

	UIE = 0x00;
	UIR = 0x00;

	UEIE = 0x00;
	UEIR = 0x00;

	PIE2bits.USBIE = 0;

	if (mode) {

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



void usb_process()
{

	if (PIR2bits.USBIF)  usb_handle_generic();
	if (UIRbits.UERRIF)  usb_handle_error();
	if (UIRbits.SOFIF)   usb_handle_start_of_frame();
	if (UIRbits.IDLEIF)  usb_handle_idle();
	if (UIRbits.ACTVIF)  usb_handle_active();
	if (UIRbits.STALLIF) usb_handle_stall();
	if (UIRbits.URSTIF)  usb_handle_reset();
	if (UIRbits.TRNIF)   usb_handle_transfer();

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
	UIRbits.IDLEIF  = 0;

}



void usb_handle_active()
{

	UCONbits.SUSPND = 0;

	while (UIRbits.ACTVIF)
		UIRbits.ACTVIF = 0;

}



void usb_handle_stall()
{

#if USB_ENDPOINTS >= 1
	UEP0bits.EPSTALL = 0;
	usb_ep0_reset();
#endif

#if USB_ENDPOINTS >= 2
	UEP1bits.EPSTALL = 0;
	usb_ep1_reset();
#endif

#if USB_ENDPOINTS >= 3
	UEP2bits.EPSTALL = 0;
	usb_ep2_reset();
#endif

#if USB_ENDPOINTS >= 4
	UEP3bits.EPSTALL = 0;
	usb_ep3_reset();
#endif

#if USB_ENDPOINTS >= 5
	UEP4bits.EPSTALL = 0;
	usb_ep4_reset();
#endif

#if USB_ENDPOINTS >= 6
	UEP5bits.EPSTALL = 0;
	usb_ep5_reset();
#endif

#if USB_ENDPOINTS >= 7
	UEP6bits.EPSTALL = 0;
	usb_ep6_reset();
#endif

#if USB_ENDPOINTS >= 8
	UEP7bits.EPSTALL = 0;
	usb_ep7_reset();
#endif

	usb_transfer.status = usb_transfer_status_idle;

	UIRbits.STALLIF = 0;

}



void usb_handle_reset()
{

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

	UIR  = 0x00;
	UEIR = 0x00;

	usb_set_address(0);
	usb_set_status(usb_device_powered);
	usb_configuration = 0;

	usb_transfer.source.rom = NULL;
	usb_transfer.length     = 0;
	usb_transfer.status     = usb_transfer_status_idle;

#if USB_ENDPOINTS >= 1
	usb_ep0_reset();
	usb_ep0_configure();
#endif

#if USB_ENDPOINTS >= 2
	usb_ep1_reset();
#endif

#if USB_ENDPOINTS >= 3
	usb_ep2_reset();
#endif

#if USB_ENDPOINTS >= 4
	usb_ep3_reset();
#endif

#if USB_ENDPOINTS >= 5
	usb_ep4_reset();
#endif

#if USB_ENDPOINTS >= 6
	usb_ep5_reset();
#endif

#if USB_ENDPOINTS >= 7
	usb_ep6_reset();
#endif

#if USB_ENDPOINTS >= 8
	usb_ep7_reset();
#endif

	while (UIRbits.TRNIF != 0)
		UIRbits.TRNIF = 0;

}



void usb_handle_transfer()
{

	if (USTATbits.ENDP == 0x00) {

		if (USB_SETUP(0)) {

			usb_transfer.status = usb_transfer_status_idle;

			usb_ep0_setup();
			usb_finalize_setup_transfer(0);

		} else if (USB_IN(0)) {

			usb_ep0_in();
			usb_finalize_in_transfer(0);

		} else if (USB_OUT(0)) {

			usb_ep0_out();
			usb_finalize_out_transfer(0);

		}

	} else if (USTATbits.ENDP == 0x01) {

		if (USB_SETUP(1)) {

			usb_transfer.status = usb_transfer_status_idle;

			usb_ep1_setup();
			usb_finalize_setup_transfer(1);

		} else if (USB_IN(1)) {

			usb_ep1_in();
			usb_finalize_in_transfer(1);

		} else if (USB_OUT(1)) {

			usb_ep1_out();
			usb_finalize_out_transfer(1);

		}

	}

	UIRbits.TRNIF = 0;

}



void usb_handle_configure(byte config)
{

	usb_configuration = config;

#if USB_ENDPOINTS >= 2
	usb_ep1_configure();
#endif

#if USB_ENDPOINTS >= 3
	usb_ep2_configure();
#endif

#if USB_ENDPOINTS >= 4
	usb_ep3_configure();
#endif

#if USB_ENDPOINTS >= 5
	usb_ep4_configure();
#endif

#if USB_ENDPOINTS >= 6
	usb_ep5_configure();
#endif

#if USB_ENDPOINTS >= 7
	usb_ep6_configure();
#endif

#if USB_ENDPOINTS >= 8
	usb_ep7_configure();
#endif

	usb_set_status(usb_device_configured);

}



void usb_finalize_setup_transfer(byte ep)
{

	if (usb_transfer.status == usb_transfer_status_out) {

		usb.endpoint[ep].out.count  = USB_BUFFER_SIZE;
		usb.endpoint[ep].out.status = 0x80;

		usb.endpoint[ep].in.count  = 0;
		usb.endpoint[ep].in.status = 0xc0;

	} else if (usb_transfer.status == usb_transfer_status_in_code ||
				usb_transfer.status == usb_transfer_status_in_data) {

		usb_finalize_in_transfer(ep);

	} else if (usb_transfer.status == usb_transfer_status_acknowledge) {

		usb.endpoint[ep].out.count  = USB_BUFFER_SIZE;
		usb.endpoint[ep].out.status = 0x80;

		usb.endpoint[ep].in.count  = 0;
		usb.endpoint[ep].in.status = 0xc0;

		usb_transfer.status = usb_transfer_status_idle;

	} else {

		usb.endpoint[ep].out.count  = USB_BUFFER_SIZE;
		usb.endpoint[ep].out.status = 0x84;
		usb.endpoint[ep].in.status  = 0x84;

	}

	UCONbits.PKTDIS = 0;

}



void usb_finalize_in_transfer(byte ep)
{

	byte n;

	if (usb_transfer.status != usb_transfer_status_in_code &&
		usb_transfer.status != usb_transfer_status_in_data)
		return;

	if (usb_transfer.length < USB_BUFFER_SIZE)
		usb.endpoint[ep].in.count = usb_transfer.length;

	else
		usb.endpoint[ep].in.count = USB_BUFFER_SIZE;

	usb_transfer.length -= usb.endpoint[ep].in.count;


	if (usb_transfer.status == usb_transfer_status_in_code)
		for (n=0; n < usb.endpoint[ep].in.count; n++)
			usb.buffer[ep].in[n] = *usb_transfer.source.rom++;

	else
		for (n=0; n < usb.endpoint[ep].in.count; n++)
			usb.buffer[ep].in[n] = *usb_transfer.source.ram++;

	usb.endpoint[ep].out.count  = USB_BUFFER_SIZE;
	usb.endpoint[ep].out.status = 0x80;
	usb.endpoint[ep].in.status  = (usb.endpoint[ep].in.status & 0x40)? 0x88: 0xc8;

}



void usb_finalize_out_transfer(byte ep)
{

	usb.endpoint[ep].out.count  = USB_BUFFER_SIZE;
	usb.endpoint[ep].out.status = (usb.endpoint[ep].out.status & 0x40)? 0x88: 0xc8;

}



void usb_transfer_acknowledge()
{

	usb_transfer.source.rom = NULL;
	usb_transfer.length     = 0;
	usb_transfer.status     = usb_transfer_status_acknowledge;

}



void usb_transfer_in_code(const code byte *buffer, word length)
{

	usb_transfer.source.rom = buffer;
	usb_transfer.length     = length;
	usb_transfer.status     = usb_transfer_status_in_code;

}



void usb_transfer_in_data(const data byte *buffer, word length)
{

	usb_transfer.source.ram = buffer;
	usb_transfer.length     = length;
	usb_transfer.status     = usb_transfer_status_in_data;

}



void usb_transfer_out(const data byte *buffer, word length)
{

	usb_transfer.source.ram = buffer;
	usb_transfer.length     = length;
	usb_transfer.status     = usb_transfer_status_out;

}

