

#include "core/core.h"

#include "usb/usb.h"
#include "usb/request.h"


enum {

	UADDR_PENDING = 0x80

};


static byte usb_address;
static byte usb_configuration;



void usb_init()
{

	byte n;

	for (n=0; n < USB_ENDPOINTS; n++)
		usb_set_endpoint_control(n, NULL);

}



void usb_mode(byte mode)
{

	UCONbits.USBEN = 0;
	PIR2bits.USBIF = 0;
	PIE2bits.USBIE = 0;

	UCFG = 0;

	UIE = 0;
	UIR = 0;

	UEIE = 0;
	UEIR = 0;

	if ((mode & USB_ENABLE) == 0)
		return;

	UIE  = 0x7f;
	UEIE = 0x9f;

	if ((mode & USB_PULLUP_EXT) == 0) UCFGbits.UPUEN = 1;
	if ((mode & USB_SPEED_FULL) != 0) UCFGbits.FSEN  = 1;

	UCONbits.USBEN = 1;

	if (mode & USB_INTERRUPT) {

		IPR2bits.USBIP = 1;
		PIE2bits.USBIE = 1;

	}

	while (UCONbits.SE0);

}



void usb_process()
{

	if (PIR2bits.USBIF) PIR2bits.USBIF = 0;
	if (UIRbits.SOFIF)  UIRbits.SOFIF = 0;


	if (UIRbits.UERRIF) {  // Bus error: Clear error

		UEIR = 0x00;
		UIRbits.UERRIF = 0;

	}


	if (UIRbits.IDLEIF) { // Bus is idle, suspend the SIE

		UCONbits.SUSPND = 1;
		UIRbits.IDLEIF  = 0;

	}


	if (UIRbits.ACTVIF) { // Bus is active, start up the SIE

		UCONbits.SUSPND = 0;

		while (UIRbits.ACTVIF)
			UIRbits.ACTVIF = 0;

	}


	if (UIRbits.STALLIF) { // An endpoint has stalled, clear it

		byte n;

		for (n=0; n < USB_ENDPOINTS; n++)
			if ((&UEP0)[n] & 1) {

				usb_transfer_preset(n);
				(&UEP0)[n] &= ~1;

			}

		UIRbits.STALLIF = 0;

	}


	if (UIRbits.URSTIF) { // Bus reset, clear everything

		UIR  = 0x00;
		UEIR = 0x00;

		usb_aperture_init();
		usb_transfer_init();

		usb_configure_address(0);
		usb_configure_device(0);

		while (UIRbits.TRNIF != 0)
			UIRbits.TRNIF = 0;

	}


	while (UIRbits.TRNIF) { // Transfer requested

		const byte token = usb_transfer_begin();

		switch (token) {

			case USB_TOKEN_SETUP:
				usb_transfer_setup();
				break;

			case USB_TOKEN_IN:

				if ((usb_address & UADDR_PENDING) != 0) {

					usb_address &= ~UADDR_PENDING;
					UADDR = usb_address;

				}

				usb_transfer_send();
				break;

			case USB_TOKEN_OUT:
				usb_transfer_recv();
				break;

		}

		usb_transfer_end();

	}

}



int usb_stdrequest(const data byte *rqst)
{

//
// Standard Device Requests
//
// bmRequestType   bRequest                       wValue                         wIndex        wLength        Data
//
//     0x80        GET_STATUS         0x00        Zero                           0             2              Device Status
//     0x00        CLEAR_FEATURE      0x01        Feature Selector               0             0              None
//     0x00        SET_FEATURE        0x03        Feature Selector               0             0              None
//     0x00        SET_ADDRESS        0x05        Device Address                 0             0              None
//     0x80        GET_DESCRIPTOR     0x06        DscrType/Index                 LangId        DscLen         Descriptor
//     0x00        SET_DESCRIPTOR     0x07        DscrType/Index                 LangId        DscLen         Descriptor
//     0x80        GET_CONFIGURATION  0x08        0                              0             1              Configuration Value
//     0x00        SET_CONFIGURATION  0x09        Configuration Value            0             0              None
//
// Standard Interface Requests
//
//     0x81        GET_STATUS         0x00         0                             Interface     2              Interface Status
//     0x01        CLEAR_FEATURE      0x01         Feature Selector              Interface     0              None
//     0x01        SET_FEATURE        0x03         Feature Selector              Interface     0              None
//     0x81        GET_INTERFACE      0x0A         0                             Interface     1              Alternate Interface
//     0x01        SET_INTERFACE      0x11         Alternative Setting           Interface     0              None
//
// Standard Endpoint Requests
//
//     0x82        GET_STATUS         0x00         0                             Endpoint      2              Endpoint Status
//     0x02        CLEAR_FEATURE      0x01         Feature Selector              Endpoint      0              None
//     0x02        SET_FEATURE        0x03         Feature Selector              Endpoint      0              None
//     0x82        SYNCH_FRAME        0x12         0                             Endpoint      2              FrameNumber
//
//

	switch (USB_REQUEST_TYPE(rqst)) {

		case USB_REQUEST_GET_DEVICE_DESCRIPTOR:
			return usb_transfer_descriptor(
				USB_REQUEST_WVALUE_H(rqst),
				USB_REQUEST_WVALUE_L(rqst),
				USB_REQUEST_WLENGTH(rqst));

		case USB_REQUEST_SET_DEVICE_ADDRESS:
			usb_configure_address(USB_REQUEST_WVALUE_L(rqst));
			break;

		case USB_REQUEST_SET_DEVICE_CONFIGURATION:
			usb_configure_device(USB_REQUEST_WVALUE_L(rqst));
			break;

		default:
			return -1;
	}

	usb_transfer_acknowledge();
	return 0;

}



void usb_configure_address(byte addr)
{

	if (addr == 0) {

		UADDR       = 0;
		usb_address = 0;

	} else
		usb_address = addr | UADDR_PENDING;

}



int usb_configure_endpoint(byte ep, byte flags, word size)
{

	data byte *buf = usb_aperture_alloc(size);

	if (buf == NULL)
		return -1;

	usb_transfer_alloc(ep, buf, size);
	usb_transfer_preset(ep);

	(&UEP0)[ep] = flags;

	return 0;

}



void usb_configure_device(byte cfg)
{

	byte n;

	usb_transfer_sync();

	for (n=0; n < USB_ENDPOINTS; n++)
		usb_endpoint_configure(n, cfg);

	usb_configuration = cfg;

}

