

#include "core/core.h"

#include "usb/usb.h"


static byte __at(0x0500) usb_memory_aperture[USB_APERTURE_SIZE];
static word              aperture_alloc;



void usb_aperture_init()
{

	aperture_alloc = 0;

}



data byte *usb_aperture_alloc(word size)
{

	data byte *ptr = NULL;

	if (aperture_alloc + size <= USB_APERTURE_SIZE) {

		ptr = usb_memory_aperture + aperture_alloc;
		aperture_alloc += size;

	}

	return ptr;

}



word usb_aperture_allocated()
{

	return aperture_alloc;

}



word usb_aperture_free()
{

	return USB_APERTURE_SIZE - aperture_alloc;

}

