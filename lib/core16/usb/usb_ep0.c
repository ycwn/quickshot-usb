

#include "core/core.h"
#include "core/gpio.h"
#include "core/signal.h"

#include "bus/sci.h"

#include "usb/usb.h"
#include "usb/usb_ep0.h"

extern const code byte __usb_device_descriptor[];
extern const code byte __usb_config_descriptor[];
extern const code byte __usb_string_descriptor_table[];
extern const code byte __usb_hid_report_descriptor[];


//FIXME: Merge this with usb.c
// Unify code to be endpoint independant


void usb_ep0_reset()
{
}



void usb_ep0_configure()
{

	USB_ENDPOINT_CONFIG(0, usb_ep_in | usb_ep_out | usb_ep_handshake | usb_ep_control_enable);

}



void usb_ep0_setup()
{

	const code byte *descriptor = NULL;
	byte length                 = 0;
	byte n;

//
// TODO: Implement rest of standard request handling
//
/*
Standard Device Requests

    There are currently eight Standard Device requests, all of which are detailed in the table below.

    bmRequestType 	bRequest 	wValue 	wIndex 	wLength 	Data
    1000 0000b 	GET_STATUS (0x00) 	Zero 	Zero 	Two 	Device Status
    0000 0000b 	CLEAR_FEATURE (0x01) 	Feature Selector 	Zero 	Zero 	None
    0000 0000b 	SET_FEATURE (0x03) 	Feature Selector 	Zero 	Zero 	None
    0000 0000b 	SET_ADDRESS (0x05) 	Device Address 	Zero 	Zero 	None
    1000 0000b 	GET_DESCRIPTOR (0x06) 	Descriptor Type & Index 	Zero or Language ID 	Descriptor Length 	Descriptor
    0000 0000b 	SET_DESCRIPTOR (0x07) 	Descriptor Type & Index 	Zero or Language ID 	Descriptor Length 	Descriptor
    1000 0000b 	GET_CONFIGURATION (0x08) 	Zero 	Zero 	1 	Configuration Value
    0000 0000b 	SET_CONFIGURATION (0x09) 	Configuration Value 	Zero 	Zero 	None

Standard Endpoint Requests

    Standard Endpoint requests come in the four varieties listed below.

    bmRequestType 	bRequest 	wValue 	Windex 	wLength 	Data
    1000 0010b 	GET_STATUS (0x00) 	Zero 	Endpoint 	Two 	Endpoint Status
    0000 0010b 	CLEAR_FEATURE (0x01) 	Feature Selector 	Endpoint 	Zero 	None
    0000 0010b 	SET_FEATURE (0x03) 	Feature Selector 	Endpoint 	Zero 	None
    1000 0010b 	SYNCH_FRAME (0x12) 	Zero 	Endpoint 	Two 	FrameNumber

*/

	if (USB_GET_DESCRIPTOR(0) || USB_GET_INTF_DESCRIPTOR(0)) {

		if (USB_REQUEST_DEVICE(0)) {

			descriptor = __usb_device_descriptor;
			length     = descriptor[0];

		} else if (USB_REQUEST_CONFIGURATION(0)) {

			descriptor = __usb_config_descriptor;
			length     = descriptor[2];

		} else if (USB_REQUEST_STRING(0)) {

			descriptor = __usb_string_descriptor_table;
			length     = descriptor[0];

			for (n=usb.buffer[0].out[2]; n > 0; --n) {

				descriptor += length;
				length = descriptor[0];

			}

		} else if (usb.buffer[0].out[3] == 0x21) { // HID Device descriptor

			descriptor = __usb_hid_report_descriptor;
			length     = descriptor[0];

		} else if (usb.buffer[0].out[3] == 0x22) { // HID Report descriptor

			descriptor  = __usb_hid_report_descriptor;
			descriptor += descriptor[0];
			length      = 47;

		}

		if (descriptor != NULL) {

			if (length > usb.buffer[0].out[6])
				length = usb.buffer[0].out[6];

			usb_transfer_in_code(descriptor, length);

		} else
			usb_transfer_in_code("", 0);

	} else if (USB_SET_ADDRESS(0)) {

		usb_set_pending_address(usb.buffer[0].out[2]);
		usb_transfer_acknowledge();

	} else if (USB_SET_CONFIGURATION(0)) {

		usb_handle_configure(usb.buffer[0].out[2]);
		usb_transfer_acknowledge();

	}

}



void usb_ep0_in()
{

	if (usb_has_pending_address()) {

		usb_set_address(usb_get_pending_address());
		usb_set_status(usb_device_address);

	}

}



void usb_ep0_out()
{
}

