

#include "core/algorithm.h"
#include "core/core.h"

#include "usb/usb.h"
#include "usb/descriptor.h"
#include "usb/request.h"
#include "usb/cdc.h"


static int ep0_configure(byte ep, byte cfg);
static int ep1_configure(byte ep, byte cfg);
static int ep2_configure(byte ep, byte cfg);

static int ep1_in(byte ep, data byte *buf, word len);
static int ep2_in(byte ep, data byte *buf, word len);
static int ep2_out(byte ep, data byte *buf, word len);



#define DEVICE_VENDOR    0x666
#define DEVICE_PRODUCT   0x666
#define DEVICE_RELEASE   0x666

#define CONFIGURATION_ID  1

#define VENDOR_NAME_ID    1
#define PRODUCT_NAME_ID   2
#define SERIAL_NUMBER_ID  3
#define CONFIG_TEXT_ID    4
#define INTERFACE_ID      5


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


	USB_CONFIGURATION(0, CONFIGURATION_ID, 2, CONFIG_TEXT_ID, 0x80, 50,

		USB_INTERFACE(0, 0, 1, USB_CLASS_CDC, USB_SUBCLASS_CDC_ABSTRACT_CONTROL, USB_PROTOCOL_CDC_ITU_T_V250, INTERFACE_ID),
			USB_CDC(
				USB_CDC_FUNC_ABSTRACT_CONTROL_MGMT(
					USB_CDC_CAPS_DEFAULT
				),
				USB_CDC_FUNC_UNION(0, 1)
			),
			USB_ENDPOINT(0x81, USB_EP_ATTR_INTERRUPT, USB_BUFFER_SIZE, 255),

		USB_INTERFACE(1, 0, 2, USB_CLASS_CDC_DATA, 0x00, 0x00, INTERFACE_ID),
			USB_ENDPOINT(0x82, USB_EP_ATTR_BULK, USB_BUFFER_SIZE, 0),
			USB_ENDPOINT(0x02, USB_EP_ATTR_BULK, USB_BUFFER_SIZE, 0)

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
	0,
	0,
	0
};

static const code struct usb_ep_control ep1ctrl = {
	&ep1_configure,
	0,
	&ep1_in,
	0
};

static const code struct usb_ep_control ep2ctrl = {
	&ep2_configure,
	0,
	&ep2_in,
	&ep2_out
};



void setup()
{

	usb_init();

	usb_set_endpoint_control(0, &ep0ctrl);
	usb_set_endpoint_control(1, &ep1ctrl);
	usb_set_endpoint_control(2, &ep2ctrl);

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
		usb_configure_endpoint(ep, USB_EP_IN | USB_EP_OUT | USB_EP_HANDSHAKE | USB_EP_CONTROL_ENABLE, USB_BUFFER_SIZE);

	else
		usb_configure_endpoint(ep, USB_EP_DISABLED, 0);

	return 0;

}



int ep2_configure(byte ep, byte cfg)
{

	if (cfg)
		usb_configure_endpoint(ep, USB_EP_IN | USB_EP_OUT | USB_EP_HANDSHAKE | USB_EP_CONTROL_DISABLE, USB_BUFFER_SIZE);

	else
		usb_configure_endpoint(ep, USB_EP_DISABLED, 0);

	return 0;

}



int ep1_in(byte ep, data byte *buf, word len)
{

	return 0;

}



int ep2_in(byte ep, data byte *buf, word len)
{

	usb_transfer_code("SEE YOU AT THE PARTY RICHTER\r\n", 30);
	return 0;

}



int ep2_out(byte ep, data byte *buf, word len)
{

	return -1;

}

