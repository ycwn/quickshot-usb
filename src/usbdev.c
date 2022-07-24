

#include "core/algorithm.h"
#include "core/core.h"

#include "usb/usb.h"
#include "usb/descriptor.h"
#include "usb/request.h"
#include "usb/hid.h"

#include "joystick.h"
#include "usbdev.h"


enum {

	DEVICE_VENDOR  =  0x666,
	DEVICE_PRODUCT =  0x666,
	DEVICE_RELEASE =  0x666,

	CONFIGURATION_ID = 1,

	VENDOR_NAME_ID   = 1,
	PRODUCT_NAME_ID  = 2,
	SERIAL_NUMBER_ID = 3

};


enum {

	HID_REPORT0_BASE_LEN     = 32,  // Size of HID report with no features enabled
	HID_REPORT0_AXES_LEN     = 13,  // Size of report if any axes are enabled
	HID_REPORT0_AXIS_LEN     = 2,   // Size of report for every axis enabled
	HID_REPORT0_THROTTLE_LEN = 15,  // Size of report if throttle is enabled
	HID_REPORT0_RUDDER_LEN   = 15,  // Size of report if rudder is enabled
	HID_REPORT0_POVHAT_LEN   = 15,  // Size of report if rudder is enabled

	HID_REPORT0_LEN =               // Total report size
		HID_REPORT0_BASE_LEN +
		((JOYSTICK_NUM_AXES > 0)? HID_REPORT0_AXES_LEN: 0) +
		JOYSTICK_NUM_AXES     * HID_REPORT0_AXIS_LEN +
		JOYSTICK_HAS_THROTTLE * HID_REPORT0_THROTTLE_LEN +
		JOYSTICK_HAS_RUDDER   * HID_REPORT0_RUDDER_LEN +
		JOYSTICK_HAS_POVHAT   * HID_REPORT0_POVHAT_LEN

};


static int ep0_configure(byte ep, byte cfg);
static int ep1_configure(byte ep, byte cfg);

static int ep0_setup(byte ep, data byte *buf, word len);
static int ep1_in(byte ep, data byte *buf, word len);
static int ep1_out(byte ep, data byte *buf, word len);



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


	USB_CONFIGURATION(0, CONFIGURATION_ID, 1, 0, 0x80, 50,

		USB_INTERFACE(0, 0, 1, USB_CLASS_HID, USB_SUBCLASS_NONE, USB_PROTOCOL_NONE, 0),
			USB_HID_INTERFACE(USB_HID_LOCALE_NONE, HID_REPORT0_LEN),
			USB_ENDPOINT(0x81, USB_EP_ATTR_INTERRUPT, USB_BUFFER_SIZE, 8)

	);


	USB_HID(0,
		USB_HID_LOCALE_NONE,
		HID_REPORT0_LEN
	);


	USB_HID_REPORT(0,

		USB_HID_USAGE_PAGE_GENERIC_DESKTOP
		USB_HID_USAGE_JOYSTICK

		USB_HID_COLLECTION_APPLICATION
			USB_HID_COLLECTION_PHYSICAL

				USB_HID_USAGE_PAGE_BUTTON
					USB_HID_USAGE_MIN8(1)
					USB_HID_USAGE_MAX8(JOYSTICK_NUM_BUTTONS)
					USB_HID_LOGICAL_MIN8(0)
					USB_HID_LOGICAL_MAX8(1)
					USB_HID_REPORT_COUNT8(JOYSTICK_NUM_BUTTONS)
					USB_HID_REPORT_SIZE8(1)
					USB_HID_INPUT8(
						USB_HID_INPUT_DATA | USB_HID_INPUT_VARIABLE | USB_HID_INPUT_ABSOLUTE
					)
					USB_HID_REPORT_COUNT8(1)
					USB_HID_REPORT_SIZE8(16 - JOYSTICK_NUM_BUTTONS)
					USB_HID_INPUT8(
						USB_HID_INPUT_CONST | USB_HID_INPUT_VARIABLE | USB_HID_INPUT_ABSOLUTE
					)

#if JOYSTICK_NUM_AXES > 0
				USB_HID_USAGE_PAGE_GENERIC_DESKTOP

					JOYSTICK_IF_ENABLED(JOYSTICK_AXIS_X,  USB_HID_USAGE_X)
					JOYSTICK_IF_ENABLED(JOYSTICK_AXIS_Y,  USB_HID_USAGE_Y)
					JOYSTICK_IF_ENABLED(JOYSTICK_AXIS_Z,  USB_HID_USAGE_Z)
					JOYSTICK_IF_ENABLED(JOYSTICK_AXIS_RX, USB_HID_USAGE_RX)
					JOYSTICK_IF_ENABLED(JOYSTICK_AXIS_RY, USB_HID_USAGE_RY)
					JOYSTICK_IF_ENABLED(JOYSTICK_AXIS_RZ, USB_HID_USAGE_RZ)
					JOYSTICK_IF_ENABLED(JOYSTICK_AXIS_VX, USB_HID_USAGE_VX)
					JOYSTICK_IF_ENABLED(JOYSTICK_AXIS_VY, USB_HID_USAGE_VY)
					JOYSTICK_IF_ENABLED(JOYSTICK_AXIS_VZ, USB_HID_USAGE_VZ)

					USB_HID_LOGICAL_MIN8(0)
					USB_HID_LOGICAL_MAX16(65535)
					USB_HID_REPORT_COUNT8(JOYSTICK_NUM_AXES)
					USB_HID_REPORT_SIZE8(16)
					USB_HID_INPUT8(
						USB_HID_INPUT_DATA | USB_HID_INPUT_VARIABLE | USB_HID_INPUT_ABSOLUTE
					)
#endif

#if JOYSTICK_HAS_THROTTLE
				USB_HID_USAGE_PAGE_SIMULATION
					USB_HID_USAGE_THROTTLE
					USB_HID_LOGICAL_MIN8(0)
					USB_HID_LOGICAL_MAX16(65535)
					USB_HID_REPORT_COUNT8(1)
					USB_HID_REPORT_SIZE8(16)
					USB_HID_INPUT8(
						USB_HID_INPUT_DATA | USB_HID_INPUT_VARIABLE | USB_HID_INPUT_ABSOLUTE
					)
#endif

#if JOYSTICK_HAS_RUDDER
				USB_HID_USAGE_PAGE_SIMULATION
					USB_HID_USAGE_RUDDER
					USB_HID_LOGICAL_MIN8(0)
					USB_HID_LOGICAL_MAX16(65535)
					USB_HID_REPORT_COUNT8(1)
					USB_HID_REPORT_SIZE8(16)
					USB_HID_INPUT8(
						USB_HID_INPUT_DATA | USB_HID_INPUT_VARIABLE | USB_HID_INPUT_ABSOLUTE
					)
#endif

#if JOYSTICK_HAS_POVHAT
				USB_HID_USAGE_PAGE_GENERIC_DESKTOP
					USB_HID_USAGE_HAT_SWITCH
					USB_HID_LOGICAL_MIN8(0)
					USB_HID_LOGICAL_MAX16(65535)
					USB_HID_REPORT_COUNT8(1)
					USB_HID_REPORT_SIZE8(16)
					USB_HID_INPUT8(
						USB_HID_INPUT_DATA | USB_HID_INPUT_VARIABLE | USB_HID_INPUT_ABSOLUTE
					)
#endif

			USB_HID_COLLECTION_END
		USB_HID_COLLECTION_END

	);


	USB_LANGUAGE(
		USB_LANG_EN_US
	);


	USB_STRING(VENDOR_NAME_ID,   JOYSTICK_VENDOR);
	USB_STRING(PRODUCT_NAME_ID,  JOYSTICK_NAME);
	USB_STRING(SERIAL_NUMBER_ID, JOYSTICK_SERIAL);

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


static word report[JOYSTICK_STATE_MAX];



void usbdev_init()
{

	usb_init();

	usb_set_endpoint_control(0, &ep0ctrl);
	usb_set_endpoint_control(1, &ep1ctrl);

	usb_mode(USB_ENABLE | USB_SPEED_FULL | USB_INTERRUPT);

}



void usbdev_process()
{

	usb_process();

}



void usbdev_set_axis(i8 n, word value)
{

	if (n > 0 && n < JOYSTICK_STATE_MAX)
		report[n] = value;

}



void usbdev_set_buttons(word mask)
{

	report[JOYSTICK_STATE_BUTTONS] = mask;

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

		const u8  type = USB_REQUEST_WVALUE_H(buf);
		const u8  id   = USB_REQUEST_WVALUE_L(buf);
		const u16 len  = USB_REQUEST_WLENGTH(buf);

		if (usb_transfer_descriptor(type, id, len) < 0)
			return -1;

		return 0;

	}

	return -1;

}



int ep1_in(byte ep, data byte *buf, word len)
{

	usb_transfer_data((const data byte*)report, sizeof(report));
	return 0;

}



int ep1_out(byte ep, data byte *buf, word len)
{

	return 0;

}

