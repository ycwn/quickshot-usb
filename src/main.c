

#include "core/core.h"
#include "core/gpio.h"

#include "usb/usb.h"
#include "usb/hid.h"



USB_DEVICE(0x666, 0x666, 0x666, 1, 2, 0, 1);


USB_CONFIGURATION(1, 1, 2, 0x80, 50,

	USB_INTERFACE(0, 0, 1, USB_CLASS_HID, 0x00, 0x00, 1),
		USB_HID(1),
		USB_HID_REPORT(47),
		USB_ENDPOINT(0x81, USB_ENDPOINT_INTERRUPT, 8, 8)

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
	),

	USB_STRING(42,
		'Y', 'O', 'U', ' ', 'S', 'E', 'T', ' ', 'U', 'S', ' ', 'U', 'P'
	)
);

const code byte __usb_hid_report_descriptor[]={

	USB_HID(1),
	USB_HID_REPORT(47),

	0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)
	0x09, 0x04,                    // USAGE (Joystick)
	0xa1, 0x01,                    // COLLECTION (Application)
	0xa1, 0x00,                    //   COLLECTION (Physical)
	0x05, 0x09,                    //     USAGE_PAGE (Button)
	0x19, 0x01,                    //     USAGE_MINIMUM (Button 1)
	0x29, 0x08,                    //     USAGE_MAXIMUM (Button 8)
	0x15, 0x00,                    //     LOGICAL_MINIMUM (0)
	0x25, 0x01,                    //     LOGICAL_MAXIMUM (1)
	0x95, 0x08,                    //     REPORT_COUNT (8)
	0x75, 0x01,                    //     REPORT_SIZE (1)
	0x81, 0x02,                    //     INPUT (Data,Var,Abs)
	0x05, 0x01,                    //     USAGE_PAGE (Generic Desktop)
	0x09, 0x30,                    //     USAGE (X)
	0x09, 0x31,                    //     USAGE (Y)
	0x09, 0x32,                    //     USAGE (Z)
	0x09, 0x33,                    //     USAGE (Rx)
	0x15, 0x00,                    //     LOGICAL_MINIMUM (0)
	0x26, 0xff, 0x00,              //     LOGICAL_MAXIMUM (255)
	0x95, 0x04,                    //     REPORT_COUNT (4)
	0x75, 0x08,                    //     REPORT_SIZE (8)
	0x81, 0x02,                    //     INPUT (Data,Var,Abs)
	0xc0,                          //     END_COLLECTION
	0xc0                           // END_COLLECTION

};



void setup()
{

	TRIS_B(0) = 0;
	GPIO_B(0) = 1;

	usb_mode(usb_enable);

}



void loop()
{

	usb_process();

}

