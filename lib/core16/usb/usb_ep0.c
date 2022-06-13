

#include "core/core.h"
#include "core/signal.h"

#include "usb/usb.h"
#include "usb/usb_ep0.h"


extern const code byte __usb_device_descriptor[];
extern const code byte __usb_config_descriptor[];
extern const code byte __usb_string_descriptor_table[];


byte usb_configuration;



void usb_ep0_reset()
{

	USB_ENDPOINT_CONFIG(0, usb_ep_in | usb_ep_out | usb_ep_handshake | usb_ep_control_enable);

}



void usb_ep0_configure()
{
}



void usb_ep0_setup()
{

	code byte *descriptor = NULL;
	byte length           = 0;
	byte n;

//
// TODO: Implement rest of standard request handling
//

	if (USB_GET_DESCRIPTOR(0)) {

		if (USB_REQUEST_DEVICE(0)) {

			descriptor = (code byte*)&__usb_device_descriptor;
			length     = descriptor[0];

		} else if (USB_REQUEST_CONFIGURATION(0)) {

			descriptor = (code byte*)&__usb_config_descriptor;
			length     = descriptor[2];

		} else if (USB_REQUEST_STRING(0)) {

			descriptor = (code byte*)&__usb_string_descriptor_table;
			length     = descriptor[0];

			for (n=usb.buffer[0].out[2]; n > 0; --n) {

				descriptor += length;
				length = descriptor[0];

			}

		}

		if (descriptor != NULL) {

			if (length > usb.buffer[0].out[6])
				length = usb.buffer[0].out[6];

			usb_transfer_in_code(descriptor, length);

		}

	} else if (USB_SET_ADDRESS(0)) {

		usb_set_pending_address(usb.buffer[0].out[2]);
		usb_transfer_acknowledge();

	} else if (USB_SET_CONFIGURATION(0)) {

		usb_set_status(usb_device_configured);
		usb_configuration = usb.buffer[0].out[2];

// _signal_raise(USB_SIGNAL_SET_CONFIGURATION);

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

