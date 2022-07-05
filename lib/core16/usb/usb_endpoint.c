

#include "core/core.h"

#include "usb/usb.h"



static const code struct usb_ep_control *epctrl[USB_ENDPOINTS];



const code struct usb_ep_control *usb_get_endpoint_control(byte ep)
{

	return (ep < USB_ENDPOINTS)? epctrl[ep]: NULL;

}



int usb_set_endpoint_control(byte ep, const code struct usb_ep_control *ec)
{

	if (ep >= USB_ENDPOINTS)
		return -1;

	epctrl[ep] = ec;

	return 0;

}



int usb_endpoint_configure(byte ep, byte cfg)
{

	const code struct usb_ep_control *ec;

	if (ep >= USB_ENDPOINTS)
		return -1;

	ec = epctrl[ep];

	if (ec == NULL || ec->config == NULL)
		return -1;

	return ec->config(ep, cfg);

}



int usb_endpoint_setup(byte ep, data byte *buf, word len)
{

	const code struct usb_ep_control *ec;

	if (ep >= USB_ENDPOINTS)
		return -1;

	ec = epctrl[ep];

	if (ec == NULL || ec->setup == NULL)
		return -1;

	return ec->setup(ep, buf, len);

}



int usb_endpoint_in(byte ep, data byte *buf, word len)
{

	const code struct usb_ep_control *ec;

	if (ep >= USB_ENDPOINTS)
		return -1;

	ec = epctrl[ep];

	if (ec == NULL || ec->in == NULL)
		return -1;

	return ec->in(ep, buf, len);

}



int usb_endpoint_out(byte ep, data byte *buf, word len)
{

	const code struct usb_ep_control *ec;

	if (ep >= USB_ENDPOINTS)
		return -1;

	ec = epctrl[ep];

	if (ec == NULL || ec->out == NULL)
		return -1;

	return ec->out(ep, buf, len);

}

