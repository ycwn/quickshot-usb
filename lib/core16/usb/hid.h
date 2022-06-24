

#ifndef __USB_HID_H
#define __USB_HID_H


#define USB_CLASS_HID              0x03
#define USB_SUBCLASS_HID_BOOT      0x01
#define USB_PROTOCOL_HID_KEYBOARD  0x01
#define USB_PROTOCOL_HID_MOUSE     0x02

#define USB_HID_GET_REPORT(ep)     USB_REQUEST(ep, 0xa1, 0x01)
#define USB_HID_GET_IDLE(ep)       USB_REQUEST(ep, 0xa1, 0x02)
#define USB_HID_GET_PROTOCOL(ep)   USB_REQUEST(ep, 0xa1, 0x03)
#define USB_HID_SET_REPORT(ep)     USB_REQUEST(ep, 0x21, 0x09)
#define USB_HID_SET_IDLE(ep)       USB_REQUEST(ep, 0x21, 0x0a)
#define USB_HID_SET_PROTOCOL(ep)   USB_REQUEST(ep, 0x21, 0x0b)


#define USB_HID(reports) \
	6 + 3 * (reports), 0x21, 0x11, 0x01, 0x00, (reports)


#define USB_HID_REPORT(report) \
	0x22, USB_LOW_BYTE(report), USB_HIGH_BYTE(report)


#endif

