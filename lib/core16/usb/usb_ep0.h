

#ifndef __USB_EP0_H
#define __USB_EP0_H


#define USB_GET_DV_STATUS(ep)        USB_REQUEST(ep, 0x80, 0x00)
#define USB_GET_IF_STATUS(ep)        USB_REQUEST(ep, 0x81, 0x00)
#define USB_GET_EP_STATUS(ep)        USB_REQUEST(ep, 0x82, 0x00)
#define USB_CLR_DV_FEATURE(ep)       USB_REQUEST(ep, 0x00, 0x01)
#define USB_CLR_IF_FEATURE(ep)       USB_REQUEST(ep, 0x01, 0x01)
#define USB_CLR_EP_FEATURE(ep)       USB_REQUEST(ep, 0x02, 0x01)
#define USB_SET_DV_FEATURE(ep)       USB_REQUEST(ep, 0x00, 0x03)
#define USB_SET_IF_FEATURE(ep)       USB_REQUEST(ep, 0x01, 0x03)
#define USB_SET_EP_FEATURE(ep)       USB_REQUEST(ep, 0x02, 0x03)
#define USB_SET_ADDRESS(ep)          USB_REQUEST(ep, 0x00, 0x05)
#define USB_GET_DESCRIPTOR(ep)       USB_REQUEST(ep, 0x80, 0x06)
#define USB_SET_DESCRIPTOR(ep)       USB_REQUEST(ep, 0x00, 0x07)
#define USB_GET_CONFIGURATION(ep)    USB_REQUEST(ep, 0x80, 0x08)
#define USB_SET_CONFIGURATION(ep)    USB_REQUEST(ep, 0x00, 0x09)
#define USB_GET_INTF_DESCRIPTOR(ep)  USB_REQUEST(ep, 0x81, 0x06)
#define USB_GET_INTERFACE(ep)        USB_REQUEST(ep, 0x81, 0x0a)
#define USB_SET_INTERFACE(ep)        USB_REQUEST(ep, 0x01, 0x11)
#define USB_SYNCH_FRAME(ep)          USB_REQUEST(ep, 0x82, 0x12)

#define USB_REQUEST_DEVICE(ep)        (usb.buffer[ep].out[3] == 0x01)
#define USB_REQUEST_CONFIGURATION(ep) (usb.buffer[ep].out[3] == 0x02)
#define USB_REQUEST_STRING(ep)        (usb.buffer[ep].out[3] == 0x03)


void usb_ep0_reset();
void usb_ep0_configure();

void usb_ep0_setup();
void usb_ep0_in();
void usb_ep0_out();


#endif

