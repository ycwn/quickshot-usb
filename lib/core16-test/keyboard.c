

#include "core/algorithm.h"
#include "core/core.h"

#include "usb/usb.h"
#include "usb/descriptor.h"
#include "usb/request.h"
#include "usb/hid.h"


static int ep0_configure(byte ep, byte cfg);
static int ep1_configure(byte ep, byte cfg);

static int ep0_setup(byte ep, data byte *buf, word len);
static int ep1_in(byte ep, data byte *buf, word len);
static int ep1_out(byte ep, data byte *buf, word len);



#define DEVICE_VENDOR    0x666
#define DEVICE_PRODUCT   0x666
#define DEVICE_RELEASE   0x666

#define CONFIGURATION_ID  1

#define VENDOR_NAME_ID    1
#define PRODUCT_NAME_ID   2
#define SERIAL_NUMBER_ID  3
#define CONFIG_TEXT_ID    4
#define INTERFACE_ID      5

#define HID_REPORT0_SIZE  63


USB_DESCRIPTOR_TABLE_BEGIN

	USB_DEVICE(
		DEVICE_VENDOR,
		DEVICE_PRODUCT,
		DEVICE_RELEASE,
		VENDOR_NAME_ID,
		PRODUCT_NAME_ID,
		SERIAL_NUMBER_ID,
		1
	);


	USB_CONFIGURATION(0, CONFIGURATION_ID, 1, CONFIG_TEXT_ID, 0x80, 50,

		USB_INTERFACE(0, 0, 1, USB_CLASS_HID, 0x00, 0x00, INTERFACE_ID),
			USB_HID_INTERFACE(USB_HID_LOCALE_NONE, HID_REPORT0_SIZE),
			USB_ENDPOINT(0x81, USB_EP_ATTR_INTERRUPT, USB_BUFFER_SIZE, 8)

	);


	USB_HID(0,
		USB_HID_LOCALE_NONE,
		HID_REPORT0_SIZE
	);


	USB_HID_REPORT(0,

		USB_HID_USAGE_PAGE_GENERIC_DESKTOP
		USB_HID_USAGE_KEYBOARD

		USB_HID_COLLECTION_APPLICATION

			USB_HID_REPORT_SIZE8(1)
			USB_HID_REPORT_COUNT8(8)

			USB_HID_USAGE_PAGE_KEYBOARD

				USB_HID_USAGE_MIN8(USB_HID_KEY_NONE)
				USB_HID_USAGE_MAX8(USB_HID_KEY_RIGHTGUI)
				USB_HID_LOGICAL_MIN8(0)
				USB_HID_LOGICAL_MAX8(1)
				USB_HID_INPUT8(
					USB_HID_INPUT_DATA | USB_HID_INPUT_VARIABLE | USB_HID_INPUT_ABSOLUTE
				)

				// Modifier byte
				USB_HID_REPORT_COUNT8(1)
				USB_HID_REPORT_SIZE8(8)
				USB_HID_INPUT8(
					USB_HID_INPUT_CONST
				)

				// Reserved byte
				USB_HID_REPORT_COUNT8(5)
				USB_HID_REPORT_SIZE8(1)
				USB_HID_USAGE_PAGE_LEDS
					USB_HID_USAGE_MIN8(1)
					USB_HID_USAGE_MAX8(5)
					USB_HID_OUTPUT8(
						USB_HID_OUTPUT_DATA | USB_HID_OUTPUT_VARIABLE | USB_HID_OUTPUT_ABSOLUTE
					)

				// LED report
				USB_HID_REPORT_COUNT8(1)
				USB_HID_REPORT_SIZE8(3)
				USB_HID_OUTPUT8(
					USB_HID_OUTPUT_CONST | USB_HID_OUTPUT_VARIABLE | USB_HID_INPUT_ABSOLUTE
				)

				// padding
				USB_HID_REPORT_COUNT8(6)
				USB_HID_REPORT_SIZE8(8)
				USB_HID_LOGICAL_MIN8(USB_HID_KEY_NONE)
				USB_HID_LOGICAL_MAX8(USB_HID_KEY_RIGHTGUI)

				USB_HID_USAGE_PAGE_KEYBOARD
					USB_HID_USAGE_MIN8(USB_HID_KEY_NONE)
					USB_HID_USAGE_MAX8(USB_HID_KEY_RIGHTGUI)
					USB_HID_INPUT8(
						USB_HID_INPUT_DATA | USB_HID_INPUT_ARRAY | USB_HID_INPUT_ABSOLUTE
					)

		USB_HID_COLLECTION_END

	);


	USB_LANGUAGE(
		USB_LANG_EN_US,
		USB_LANG_EL_GR
	);


	USB_STRING(VENDOR_NAME_ID,
		'S','E','E',' ','Y','O','U',' ','A','T',' ','T','H','E',' ',
		'P','A','R','T','Y',' ','R','I','C','H','T','E','R'
	);


	USB_STRING(PRODUCT_NAME_ID,
		'P', 'U', 'T', ' ', 'T', 'H', 'E', ' ',
		'C', 'O', 'O', 'K', 'I', 'E', ' ', 'D', 'O', 'W', 'N'
	);


	USB_STRING(SERIAL_NUMBER_ID,
		'G', 'E', 'T', ' ', 'Y', 'O', 'U', 'R', ' ',
		'A', 'S', 'S', ' ', 'T', 'O', ' ', 'M', 'A', 'R', 'S'
	);


	USB_STRING(CONFIG_TEXT_ID,
		'C', 'O', 'N', 'S', 'I', 'D', 'E', 'R', ' ',
		'T', 'H', 'I', 'S', ' ', 'A', ' ', 'D', 'I', 'V', 'O', 'R', 'C', 'E'
	);


	USB_STRING(INTERFACE_ID,
		'I', 'C', 'E', ' ', 'T', 'O', ' ', 'S', 'E', 'E',' ', 'Y', 'O', 'U'
	);


USB_DESCRIPTOR_TABLE_END


static const code struct usb_ep_control ep0ctrl = {
	&ep0_configure,
	&ep0_setup,
	0,
	0
};

static const code struct usb_ep_control ep1ctrl = {
	&ep1_configure,
	0,
	&ep1_in,
	&ep1_out
};


static const code byte party[]={
	USB_HID_KEY_S, USB_HID_KEY_E, USB_HID_KEY_E,
	USB_HID_KEY_SPACE,
	USB_HID_KEY_Y, USB_HID_KEY_O, USB_HID_KEY_U,
	USB_HID_KEY_SPACE,
	USB_HID_KEY_A, USB_HID_KEY_T,
	USB_HID_KEY_SPACE,
	USB_HID_KEY_T, USB_HID_KEY_H, USB_HID_KEY_E,
	USB_HID_KEY_SPACE,
	USB_HID_KEY_P, USB_HID_KEY_A, USB_HID_KEY_R, USB_HID_KEY_T, USB_HID_KEY_Y,
	USB_HID_KEY_SPACE,
	USB_HID_KEY_R, USB_HID_KEY_I, USB_HID_KEY_C, USB_HID_KEY_H, USB_HID_KEY_T, USB_HID_KEY_E, USB_HID_KEY_R,
	USB_HID_KEY_NONE
};

static byte key;
static byte dir;
static byte delay;



void setup()
{

	usb_init();

	key = 0;
	dir = 0; // 0 == keydown, 1 == keyup
	delay = 125;

	usb_set_endpoint_control(0, &ep0ctrl);
	usb_set_endpoint_control(1, &ep1ctrl);

	usb_mode(USB_ENABLE | USB_SPEED_FULL | USB_POLLING);

}



void loop()
{

	usb_process();

}



int ep0_configure(byte ep, byte cfg)
{

	if (cfg != 0)
		return 0;

	usb_configure_endpoint(0, USB_EP_DISABLED, 0);
	usb_configure_endpoint(0, USB_EP_IN | USB_EP_OUT | USB_EP_HANDSHAKE | USB_EP_CONTROL_ENABLE, USB_BUFFER_SIZE);

	return 0;

}



int ep1_configure(byte ep, byte cfg)
{

	if (cfg)
		usb_configure_endpoint(ep, USB_EP_IN | USB_EP_OUT | USB_EP_HANDSHAKE | USB_EP_CONTROL_DISABLE, USB_BUFFER_SIZE);

	else
		usb_configure_endpoint(ep, USB_EP_DISABLED, 0);

	return 0;

}



int ep0_setup(byte ep, data byte *buf, word len)
{

	if (USB_REQUEST_TYPE(buf) == USB_HID_REQUEST_GET_DESCRIPTOR) {

		if (usb_transfer_descriptor(
				USB_REQUEST_WVALUE_H(buf),
				USB_REQUEST_WVALUE_L(buf),
				USB_REQUEST_WLENGTH(buf)) < 0)

			return -1;

		return 0;

	}

	return -1;

}



int ep1_in(byte ep, data byte *buf, word len)
{

	static char scancode[8];

	if (party[key] == USB_HID_KEY_NONE)
		return 0;

	scancode[0] = 0;
	scancode[1] = 0;
	scancode[2] = 0;
	scancode[3] = 0;
	scancode[4] = 0;
	scancode[5] = 0;
	scancode[6] = 0;
	scancode[7] = 0;

	if (delay == 0) {

		if (dir == 0) {

			scancode[2] = USB_HID_KEY_LEFTSHIFT;
			scancode[3] = party[key];
			dir = 1;

		} else {

			key++;
			dir = 0;

		}

	} else
		delay--;

	usb_transfer_data(scancode, sizeof(scancode));
	return 0;

}



int ep1_out(byte ep, data byte *buf, word len)
{

	return 0;

}

