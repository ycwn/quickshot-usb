

#ifndef USB_USB_H
#define USB_USB_H


#define USB_BUFFER_SIZE      64
#define USB_ENDPOINTS         2
#define USB_APERTURE_SIZE   512

typedef int (usb_ep_config_t)(byte ep, byte cfg);
typedef int (usb_ep_xfer_t)(byte ep, data byte *buf, word len);


struct usb_ep_control {

	usb_ep_config_t *config;

	usb_ep_xfer_t *setup;
	usb_ep_xfer_t *in;
	usb_ep_xfer_t *out;

};


enum {
	USB_TOKEN_OUT   = 0x04,
	USB_TOKEN_ACK   = 0x08,
	USB_TOKEN_DATA0 = 0x0c,
	USB_TOKEN_PING  = 0x10,
	USB_TOKEN_SOF   = 0x14,
	USB_TOKEN_NYET  = 0x18,
	USB_TOKEN_DATA2 = 0x1c,
	USB_TOKEN_SPLIT = 0x20,
	USB_TOKEN_IN    = 0x24,
	USB_TOKEN_NAK   = 0x28,
	USB_TOKEN_DATA1 = 0x2c,
	USB_TOKEN_PRE   = 0x30,
	USB_TOKEN_ERR   = 0x30,
	USB_TOKEN_SETUP = 0x34,
	USB_TOKEN_STALL = 0x38,
	USB_TOKEN_MDATA = 0x3c,
	USB_TOKEN_MASK  = 0x3c
};


enum {

	USB_DISABLE = 0 << 0,
	USB_ENABLE  = 1 << 0,

	USB_SPEED_LOW  = 0 << 1,
	USB_SPEED_FULL = 1 << 1,

	USB_PULLUP_INT = 0 << 2,
	USB_PULLUP_EXT = 1 << 2,

	USB_POLLING   = 0 << 3,
	USB_INTERRUPT = 1 << 3

};

enum {

	USB_EP_DISABLED = 0,

	USB_EP_IN        = 1 << 1,
	USB_EP_OUT       = 1 << 2,
	USB_EP_HANDSHAKE = 1 << 4,

	USB_EP_CONTROL_ENABLE  = 0 << 3,
	USB_EP_CONTROL_DISABLE = 1 << 3

};


void usb_init();
void usb_mode(byte mode);
void usb_process();
int  usb_stdrequest(const data byte *rqst);

const code struct usb_ep_control *usb_get_endpoint_control(byte ep);
int                               usb_set_endpoint_control(byte ep, const code struct usb_ep_control *ec);

void usb_configure_address(byte addr);
int  usb_configure_endpoint(byte ep, byte flags, word size);
void usb_configure_device(byte cfg);

void       usb_aperture_init();
data byte *usb_aperture_alloc(word size);
word       usb_aperture_allocated();
word       usb_aperture_free();

int usb_endpoint_configure(byte ep, byte cfg);
int usb_endpoint_setup(byte ep, data byte *buf, word len);
int usb_endpoint_in(   byte ep, data byte *buf, word len);
int usb_endpoint_out(  byte ep, data byte *buf, word len);

void usb_transfer_init();
void usb_transfer_sync();
int  usb_transfer_begin();
void usb_transfer_end();
void usb_transfer_setup();
void usb_transfer_recv();
void usb_transfer_send();
int  usb_transfer_alloc(byte ep, data byte *buf, word len);
int  usb_transfer_preset(byte ep);
int  usb_transfer_descriptor(byte type, byte id, word maxlen);
int  usb_transfer_acknowledge();
int  usb_transfer_stall();
int  usb_transfer_code(const code byte *buf, word len);
int  usb_transfer_data(const data byte *buf, word len);


#endif
