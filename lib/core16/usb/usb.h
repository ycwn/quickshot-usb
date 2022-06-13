

#ifndef __USB_H
#define __USB_H


#define USB_BUFFER_SIZE       64
#define USB_ENDPOINTS          1
#define USB_VECTOR_PRIORITY  100


#define USB_MODULE \
	_vector(USB_VECTOR_PRIORITY, usb_handle_generic,        VECTOR_USB) \
	_vector(USB_VECTOR_PRIORITY, usb_handle_error,          VECTOR_USB_ERROR) \
	_vector(USB_VECTOR_PRIORITY, usb_handle_start_of_frame, VECTOR_USB_FRAME_START) \
	_vector(USB_VECTOR_PRIORITY, usb_handle_idle,           VECTOR_USB_IDLE) \
	_vector(USB_VECTOR_PRIORITY, usb_handle_active,         VECTOR_USB_ACTIVE) \
	_vector(USB_VECTOR_PRIORITY, usb_handle_stall,          VECTOR_USB_STALL) \
	_vector(USB_VECTOR_PRIORITY, usb_handle_reset,          VECTOR_USB_RESET) \
	_vector(USB_VECTOR_PRIORITY, usb_handle_transfer,       VECTOR_USB_TRANSFER)


#define USB_ENDPOINT_CONFIG(ep, flags)					\
	{								\
		usb.endpoint[(ep)].out.count  = USB_BUFFER_SIZE;	\
		usb.endpoint[(ep)].out.buffer = usb.buffer[0].out;	\
		usb.endpoint[(ep)].out.status = 0x80;			\
		usb.endpoint[(ep)].in.count   = 0;			\
		usb.endpoint[(ep)].in.buffer  = usb.buffer[0].in;	\
		usb.endpoint[(ep)].in.status  = 0x00;			\
		UEP##ep = (flags);					\
	}



#define USB_ENDPOINT_CONTROL      0x00
#define USB_ENDPOINT_ISOCHRONOUS  0x01
#define USB_ENDPOINT_BULK         0x02
#define USB_ENDPOINT_INTERRUPT    0x03

#define USB_CLASS_NONE       0x00
#define USB_CLASS_VENDOR     0xff

#define USB_SUBCLASS_NONE    0x00
#define USB_SUBCLASS_VENDOR  0xff

#define USB_PROTOCOL_NONE    0x00
#define USB_PROTOCOL_VENDOR  0xff


#define USB_LOW_BYTE(value)  ((value) & 255)
#define USB_HIGH_BYTE(value) USB_LOW_BYTE((value) >> 8)

#define USB_REQUEST(endpoint, bmRequestType, bRequest)   \
	(usb.buffer[(endpoint)].out[0] == (bmRequestType) && \
	 usb.buffer[(endpoint)].out[1] == (bRequest))


#define USB_DEVICE( \
	vendor, product, release, vendor_str, product_str, serial_str, configurations) \
		const code byte __usb_device_descriptor[] = {\
			18, 0x01, 0x00, 0x02, 0x00, 0x00, 0x00, USB_BUFFER_SIZE,	\
			USB_LOW_BYTE(vendor),  USB_HIGH_BYTE(vendor),				\
			USB_LOW_BYTE(product), USB_HIGH_BYTE(product),				\
			USB_LOW_BYTE(release), USB_HIGH_BYTE(release),				\
			(vendor_str), (product_str), (serial_str), (configurations) \
		}


#define USB_CONFIGURATION(config_no, interfaces, config_str, attributes, power, config...) \
		const byte __usb_config_descriptor[] = { \
			9, 0x02, USB_LOW_BYTE(sizeof(__usb_config_descriptor)), \
			USB_HIGH_BYTE(sizeof(__usb_config_descriptor)), (interfaces), \
			(config_no), (config_str), (attributes), (power), \
			config \
		}


//
// This is a hack, but unfortunately there seems
// no clean way to do this. We (hopefully) assume
// that the compiler will put the string data after the
// table in code space... For some reason the
// assumption is corect.
//

#define USB_STRING_TABLE(strings...)\
	const word __usb_string_descriptor_table[] = {\
		768 + sizeof(__usb_string_descriptor_table), 0x0409\
	}, strings


#define USB_STRING(number, string...)\
	__usb_string_##number##_descriptor[] = {\
		768 + sizeof(__usb_string_##number##_descriptor),\
		string\
	}


#define USB_INTERFACE(iface_no, alternate, endpoints, class, subclass, protocol, iface_str) \
		9, 0x04, (iface_no), (alternate), (endpoints), \
		(class), (subclass), (protocol), (iface_str)


#define USB_ENDPOINT(address, attributes, packet_size, interval) \
		7, 0x05, (address), (attributes), \
		USB_LOW_BYTE(packet_size), USB_HIGH_BYTE(packet_size), \
		(interval)


#define USB_OUT(ep)   ((USTAT & 0x04) == 0x00 && (usb.endpoint[(ep)].out.status & 0x3c) == 0x04)
#define USB_IN(ep)    ((USTAT & 0x04) != 0x00 && (usb.endpoint[(ep)].in.status  & 0x3c) == 0x24)
#define USB_SETUP(ep) ((USTAT & 0x04) == 0x00 && (usb.endpoint[(ep)].out.status & 0x3c) == 0x34)


enum usb_mode {

	usb_disable = 0,
	usb_enable  = 1

};


enum usb_endpoint_mode {

	usb_ep_disabled = 0,

	usb_ep_stall     =  1,
	usb_ep_in        =  2,
	usb_ep_out       =  4,
	usb_ep_handshake = 16,

	usb_ep_control_enable  = 0,
	usb_ep_control_disable = 8

};


enum usb_device_status {

	usb_device_detached   = 0,
	usb_device_attached   = 1,
	usb_device_powered    = 2,
	usb_device_address    = 3,
	usb_device_configured = 4

};


enum usb_transfer_status {

	usb_transfer_status_idle        = 0,
	usb_transfer_status_out         = 1,
	usb_transfer_status_in_code     = 2,
	usb_transfer_status_in_data     = 3,
	usb_transfer_status_acknowledge = 4

};


typedef struct {

	byte status;
	byte count;

	data byte *buffer;

} usb_buffer_descriptor;


typedef byte usb_buffer[USB_BUFFER_SIZE];


typedef struct {

	word length;
	byte status;

	union {

		code byte *rom;
		data byte *ram;

	} source;

} usb_endpoint_transfer;


typedef struct {

	struct {

		usb_buffer_descriptor out;
		usb_buffer_descriptor in;

	} endpoint[USB_ENDPOINTS];

	struct {

		usb_buffer out;
		usb_buffer in;

	} buffer[USB_ENDPOINTS];

} usb_memory_space;


extern char                  usb_device_status;
extern usb_endpoint_transfer usb_transfer;

extern volatile usb_memory_space __at(0x0400) usb;


void usb_mode(byte mode);

void usb_handle_generic();
void usb_handle_error();
void usb_handle_start_of_frame();
void usb_handle_idle();
void usb_handle_active();
void usb_handle_stall();
void usb_handle_reset();
void usb_handle_transfer();

void usb_finalize_setup_transfer();
void usb_finalize_in_transfer();
void usb_finalize_out_transfer();

void usb_transfer_acknowledge();
void usb_transfer_in_code(code byte *buffer, word length);
void usb_transfer_in_data(data byte *buffer, word length);
void usb_transfer_out(data byte *buffer, word length);

#define usb_get_status()               (usb_device_status)
#define usb_set_status(value)          usb_device_status = (value)
#define usb_get_address()              (UADDR)
#define usb_set_address(value)         UADDR = (value)
#define usb_has_pending_address()      (usb_device_status < 0)
#define usb_get_pending_address()      (-usb_device_status)
#define usb_set_pending_address(value) usb_device_status = -(char)(value)


#endif

