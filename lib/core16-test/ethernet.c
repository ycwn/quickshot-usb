

#include <string.h>

#include "core/algorithm.h"
#include "core/core.h"

#include "usb/usb.h"
#include "usb/descriptor.h"
#include "usb/request.h"
#include "usb/cdc.h"


static int ep0_configure(byte ep, byte cfg);
static int ep1_configure(byte ep, byte cfg);
static int ep2_configure(byte ep, byte cfg);

static int ep0_setup(byte ep, data byte *buf, word len);
static int ep1_in(byte ep, data byte *buf, word len);
static int ep2_in(byte ep, data byte *buf, word len);
static int ep2_out(byte ep, data byte *buf, word len);

static int  ipv4_ping(dword addr);
static word ipv4_checksum(data byte *buf, byte start, byte end);

static int ether_send_data(data byte *buf, word len);
static int ether_process(byte ep);


#define DEVICE_VENDOR    0x666
#define DEVICE_PRODUCT   0x666
#define DEVICE_RELEASE   0x666

#define CONFIGURATION_ID  1

#define VENDOR_NAME_ID    1
#define PRODUCT_NAME_ID   2
#define SERIAL_NUMBER_ID  3
#define CONFIG_TEXT_ID    4
#define INTERFACE_ID      5
#define MACADDR_ID        6


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

		USB_INTERFACE(0, 0, 1, USB_CLASS_CDC, USB_SUBCLASS_CDC_ETHERNET_CONTROL, USB_PROTOCOL_CDC_NONE, INTERFACE_ID),
			USB_CDC(
				USB_CDC_FUNC_UNION(0, 1),
				USB_CDC_FUNC_ETHERNET_NETWORKING(MACADDR_ID, 0, 64, 0, 0)
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
		'P','A','R','T','Y',' ','R','I','C','H','T','E','R',
		' ',
		'S','E','E',' ','Y','O','U',' ','A','T',' ','T','H','E',' ',
		'P','A','R','T','Y',' ','R','I','C','H','T','E','R',
		' ',
		'S','E','E',' ','Y','O','U',' ','A','T',' ','T','H','E',' ',
		'P','A','R','T','Y',' ','R','I','C','H','T','E','R',
		' ',
		'S','E','E',' ','Y','O','U',' ','A','T',' ','T','H','E',' ',
		'P','A','R','T','Y',' ','R','I','C','H','T','E','R',
		' ',
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


	USB_STRING(MACADDR_ID,
		'7', '0', '8', 'B', 'C', 'D', '0', '1', '2', '3', '4', '0'
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
	0
};

static const code struct usb_ep_control ep2ctrl = {
	&ep2_configure,
	0,
	&ep2_in,
	&ep2_out
};



byte ether_buf[64];
data byte *ether_src;
word       ether_len;

word delay;
byte send_report;
byte report[8];

byte ipv4_icmp_buf[48];




void setup()
{

	delay = 0;
	send_report = 0;

	ether_src = NULL;
	ether_len = 0;

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



int ep0_setup(byte ep, data byte *buf, word len)
{

	if (USB_REQUEST_TYPE(buf) == USB_REQUEST_CDC_SET_ETHERNET_PACKET_FILTER) {

		send_report = 1;
		usb_transfer_acknowledge();

		return 0;

	}

	return -1;

}



int ep0_in(byte ep, data byte *buf, word len)
{

	return -1;

}



int ep1_in(byte ep, data byte *buf, word len)
{

	if (send_report) {

		report[0] = USB_REQUEST_TYPE_CDC_INTERFACE_IN;
		report[1] = 0x00;
		report[2] = 0x01;
		report[3] = 0x00;
		report[4] = 0x00;
		report[5] = 0x00;
		report[6] = 0x00;
		report[7] = 0x00;

		usb_transfer_data(report, sizeof(report));
		send_report = 0;
		return 0;

	}

	return -1;

}



int ep2_in(byte ep, data byte *buf, word len)
{

	if (ether_process(ep) >= 0)     // Check if we're done transmitting
		return 0;

	if (++delay > 15000) {          // Delay a few seconds

		ipv4_ping(0x97650285);  // Ping Elon Musk with this important message
		delay = 0;

	}

	return -1;

}



int ep2_out(byte ep, data byte *buf, word len)
{

	return -1;

}



int ipv4_ping(dword addr)
{

	word checksum;

//
// IPv4 header
//
	ipv4_icmp_buf[0]  = 0x45;           // IPv4, 20 bytes in header
	ipv4_icmp_buf[1]  = 0x00;           // DiffServ:0, ECN:0
	ipv4_icmp_buf[2]  = 0x00;
	ipv4_icmp_buf[3]  = 20 + 8 + 20;    // 16bit Length
	ipv4_icmp_buf[4]  = 0;
	ipv4_icmp_buf[5]  = 0;              // 16bit ID
	ipv4_icmp_buf[6]  = 0;              // Flags, FragmentOffset
	ipv4_icmp_buf[7]  = 0;              // FragmentOffset
	ipv4_icmp_buf[8]  = 30;             // TTL
	ipv4_icmp_buf[9]  = 0x01;           // Protocol: ICMP
	ipv4_icmp_buf[10] = 0;
	ipv4_icmp_buf[11] = 0;              // Checksum, will be calculated later on
	ipv4_icmp_buf[12] = 20;
	ipv4_icmp_buf[13] = 0;
	ipv4_icmp_buf[14] = 0;
	ipv4_icmp_buf[15] = 4;              // Source address
	ipv4_icmp_buf[16] = BYTE(addr, 3);
	ipv4_icmp_buf[17] = BYTE(addr, 1);
	ipv4_icmp_buf[18] = BYTE(addr, 2);
	ipv4_icmp_buf[19] = BYTE(addr, 0);  // Destination

	//FIXME: No idea why this is off by one here. The code
	// seems to work ok in other compilers, so probably its
	// a bug in SDCC.
	checksum = ipv4_checksum(ipv4_icmp_buf, 0, 20) - 1;

	ipv4_icmp_buf[10] = BYTE(checksum, 1);
	ipv4_icmp_buf[11] = BYTE(checksum, 0);

//
// ICMP header
//
	ipv4_icmp_buf[20] = 0x08;    // ICMP echo
	ipv4_icmp_buf[21] = 0x00;    // Code: 0
	ipv4_icmp_buf[22] = 0x00;
	ipv4_icmp_buf[23] = 0x00;    // Checksum
	ipv4_icmp_buf[24] = 0xde;
	ipv4_icmp_buf[25] = 0xad;    // Identifier
	ipv4_icmp_buf[26] = 0xbe;
	ipv4_icmp_buf[27] = 0xef;    // Sequence

//
// Very important message
//
	ipv4_icmp_buf[28] = 'G';
	ipv4_icmp_buf[29] = 'E';
	ipv4_icmp_buf[30] = 'T';
	ipv4_icmp_buf[31] = ' ';
	ipv4_icmp_buf[32] = 'Y';
	ipv4_icmp_buf[33] = 'O';
	ipv4_icmp_buf[34] = 'U';
	ipv4_icmp_buf[35] = 'R';
	ipv4_icmp_buf[36] = ' ';
	ipv4_icmp_buf[37] = 'A';
	ipv4_icmp_buf[38] = 'S';
	ipv4_icmp_buf[39] = 'S';
	ipv4_icmp_buf[40] = ' ';
	ipv4_icmp_buf[41] = 'T';
	ipv4_icmp_buf[42] = 'O';
	ipv4_icmp_buf[43] = ' ';
	ipv4_icmp_buf[44] = 'M';
	ipv4_icmp_buf[45] = 'A';
	ipv4_icmp_buf[46] = 'R';
	ipv4_icmp_buf[47] = 'S';

	checksum = ipv4_checksum(ipv4_icmp_buf, 20, sizeof(ipv4_icmp_buf));

	ipv4_icmp_buf[22] = BYTE(checksum, 1);
	ipv4_icmp_buf[23] = BYTE(checksum, 0);

	return ether_send_data(ipv4_icmp_buf, sizeof(ipv4_icmp_buf));

}



word ipv4_checksum(data byte *buf, byte start, byte end)
{

	dword sum = 0;

	while (start < end) {

		sum += buf[start++] << 8;
		sum += buf[start++] << 0;

	}

	while (sum > 65535)
		sum  = (sum & 65535) + (sum >> 16);

	return ~sum;

}



int ether_send_data(data byte *buf, word len)
{

	if (ether_src != NULL)
		return -1;

	ether_src = buf;
	ether_len = len;

	return 0;

}



int ether_process(byte ep)
{

	char len;

	if (ether_src == NULL)
		return -1;

	ether_buf[0] = 0xff; // Destination MAC address
	ether_buf[1] = 0xff;
	ether_buf[2] = 0xff;
	ether_buf[3] = 0xff;
	ether_buf[4] = 0xff;
	ether_buf[5] = 0xff;

	ether_buf[6]  = 0x70; // Source MAC address, same as the one in the descriptor
	ether_buf[7]  = 0x8b;
	ether_buf[8]  = 0xcd;
	ether_buf[9]  = 0x01;
	ether_buf[10] = 0x23;
	ether_buf[11] = 0x40;

	ether_buf[12] = 0x08; // EtherType: IPv4
	ether_buf[13] = 0x00;

	len = mini8(ether_len, 50);

	memcpyram2ram(&ether_buf[14], ether_src, len);

	ether_src += len;
	ether_len -= len;

	usb_transfer_data(ether_buf, len + 14);

	if (ether_len == 0)
		ether_src = NULL;

	return 0;

}

