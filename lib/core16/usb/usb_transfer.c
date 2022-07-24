

#include <string.h>

#include "core/core.h"

#include "usb/usb.h"


enum {

	TRANSFER_IDLE  = 0,
	TRANSFER_ACK   = 1,
	TRANSFER_STALL = 2,
	TRANSFER_CODE  = 3,
	TRANSFER_DATA  = 4

};

enum {

	POLARITY_DATA0 = 0,
	POLARITY_DATA1 = 1

};

enum {

	BDSTAT_COUNT8 = 1 << 0,
	BDSTAT_COUNT9 = 1 << 1,
	BDSTAT_STALL  = 1 << 2,
	BDSTAT_DTSEN  = 1 << 3,
	BDSTAT_INCDIS = 1 << 4,
	BDSTAT_KEN    = 1 << 5,
	BDSTAT_DTS    = 1 << 6,
	BDSTAT_UOWN   = 1 << 7

};


struct epiobd {

	volatile struct {

		byte status;
		byte count;
		word buffer;

	} out, in;

};


struct epxfer {

	word capacity;
	word length;

	union {
		const code byte *rom;
		const data byte *ram;
	} source;

	unsigned status: 4;

	unsigned ipolarity: 1;
	unsigned opolarity: 1;
	unsigned polarity:  1;

};


extern const code byte *__usb_descriptor_table(data word *len, byte type, byte id);

static void transfer_ack();
static void transfer_prefetch();
static void transfer_stall();
static void transfer_preset(data struct epiobd *bd, word rxlen);
static void transfer_commit(word txlen);


static struct epxfer              epxfer[USB_ENDPOINTS];
static struct epiobd __at(0x0400) epbdt[32];

static data struct epxfer *curr_xf;
static data struct epiobd *curr_bd;
static byte                curr_ep;
static data byte          *curr_buf;
static word                curr_len;



void usb_transfer_init()
{

	byte n;

	for (n=0; n < USB_ENDPOINTS; n++) {

		data struct epxfer *xfer = &epxfer[n];

		xfer->capacity   = 0;
		xfer->length     = 0;
		xfer->source.rom = NULL;
		xfer->status     = TRANSFER_IDLE;

	}

	curr_xf = NULL;
	curr_bd = NULL;

}



void usb_transfer_sync()
{

	byte n;

	for (n=0; n < USB_ENDPOINTS; n++) {

		data struct epxfer *xfer = &epxfer[n];

		xfer->ipolarity = POLARITY_DATA0;
		xfer->opolarity = POLARITY_DATA0;
		xfer->polarity  = POLARITY_DATA0;

	}

}



int usb_transfer_begin()
{

	byte status = 0;

	curr_ep = USTATbits.ENDP;
	curr_bd = &epbdt[curr_ep];
	curr_xf = &epxfer[curr_ep];

	if (USTATbits.DIR) {

		status = curr_bd->in.status;

		curr_buf = (data byte*)curr_bd->in.buffer;
		curr_len  = WORD2(curr_bd->in.count, status & 3);

	} else {

		status = curr_bd->out.status;

		curr_buf = (data byte*)curr_bd->out.buffer;
		curr_len = WORD2(curr_bd->out.count, status & 3);

	}

	return status & USB_TOKEN_MASK;

}



void usb_transfer_end()
{

	switch (curr_xf->status) {

		case TRANSFER_ACK:
			transfer_ack();
			break;

		case TRANSFER_STALL:
			transfer_stall();
			break;

		case TRANSFER_CODE:
		case TRANSFER_DATA:
			transfer_prefetch();
			break;

	}

	curr_xf = NULL;
	curr_bd = NULL;

	UIRbits.TRNIF   = 0;
	UCONbits.PKTDIS = 0;

}



void usb_transfer_setup()
{

	int ret;

	curr_xf->ipolarity = POLARITY_DATA1;
	curr_xf->opolarity = POLARITY_DATA1;
	curr_xf->polarity  = POLARITY_DATA1;

	ret = usb_endpoint_setup(curr_ep, curr_buf, curr_len);

	if (ret < 0)
		ret = usb_stdrequest(curr_buf);

	if (ret < 0)
		usb_transfer_acknowledge();

}



void usb_transfer_send()
{

	int ret;

	curr_xf->ipolarity ^= 1;
	curr_xf->polarity   = curr_xf->ipolarity;

	// A transfer is already in progress
	if (curr_xf->status != TRANSFER_IDLE)
		return;

	ret = usb_endpoint_in(curr_ep, curr_buf, curr_len);

	if (ret < 0)
		usb_transfer_acknowledge();

}



void usb_transfer_recv()
{

	int ret;

	curr_xf->opolarity ^= 1;
	curr_xf->polarity   = curr_xf->opolarity;

	// A transfer is already in progress
	if (curr_xf->status != TRANSFER_IDLE)
		return;

	ret = usb_endpoint_out(curr_ep, curr_buf, curr_len);

	if (ret < 0)
		usb_transfer_acknowledge();

}



int usb_transfer_alloc(byte ep, data byte *buf, word len)
{

	data struct epiobd *bd;

	if (ep >= USB_ENDPOINTS)
		return -1;

	epxfer[ep].capacity = len;

	bd = &epbdt[ep];

	bd->out.buffer = (word)buf;
	bd->in.buffer  = (word)buf;

	return 0;

}



int usb_transfer_preset(byte ep)
{

	if (ep >= USB_ENDPOINTS)
		return -1;

	transfer_preset(&epbdt[ep], epxfer[ep].capacity);

	curr_xf->ipolarity = POLARITY_DATA0;
	curr_xf->opolarity = POLARITY_DATA0;

	return 0;

}


int usb_transfer_descriptor(byte type, byte id, word maxlen)
{

	word length                 = 0;
	const code byte *descriptor = __usb_descriptor_table(&length, type, id);

	if (descriptor == NULL)
		return -1;

	if (length > maxlen)
		length = maxlen;

	return usb_transfer_code(descriptor, length);

}



int usb_transfer_acknowledge()
{

	if (curr_xf == NULL)
		return -1;

	curr_xf->status = TRANSFER_ACK;

	return 0;

}



int usb_transfer_stall()
{

	if (curr_xf == NULL)
		return -1;

	curr_xf->status = TRANSFER_STALL;

	return 0;


}



int usb_transfer_code(const code byte *buf, word len)
{

	if (curr_xf == NULL)
		return -1;

	curr_xf->source.rom = buf;
	curr_xf->length     = len;
	curr_xf->status     = TRANSFER_CODE;

	return 0;

}



int usb_transfer_data(const data byte *buf, word len)
{

	if (curr_xf == NULL)
		return -1;

	curr_xf->source.ram = buf;
	curr_xf->length     = len;
	curr_xf->status     = TRANSFER_DATA;

	return 0;

}



void transfer_ack()
{

	transfer_commit(0);

	curr_xf->status = TRANSFER_IDLE;

}



void transfer_prefetch()
{

	const word size = MIN(curr_xf->length, curr_xf->capacity);

	if (curr_xf->status == TRANSFER_CODE) {

		memcpypgm2ram((data byte*)curr_bd->in.buffer, curr_xf->source.rom, size);
		curr_xf->source.rom += size;

	} else {

		memcpyram2ram((data byte*)curr_bd->in.buffer, curr_xf->source.ram, size);
		curr_xf->source.ram += size;

	}

	transfer_commit(size);

	curr_xf->length -= size;

	if (curr_xf->length == 0)
		curr_xf->status = TRANSFER_IDLE;

}




void transfer_stall()
{

	curr_bd->out.count  = 0;
	curr_bd->out.status = BDSTAT_UOWN | BDSTAT_STALL;

	curr_bd->in.count  = 0;
	curr_bd->in.status = BDSTAT_UOWN | BDSTAT_STALL;

	curr_xf->status = TRANSFER_IDLE;

}



void transfer_preset(data struct epiobd *bd, word rxlen)
{

	bd->out.count  = rxlen;
	bd->out.status = BDSTAT_UOWN;

	bd->in.count  = 0;
	bd->in.status = BDSTAT_UOWN;

}



void transfer_commit(word txlen)
{

	curr_bd->out.count  = curr_xf->capacity;
	curr_bd->out.status = BDSTAT_UOWN;

	curr_bd->in.count  = txlen;
	curr_bd->in.status = curr_xf->polarity?
		BDSTAT_UOWN | BDSTAT_DTSEN | BDSTAT_DTS:
		BDSTAT_UOWN | BDSTAT_DTSEN;

}

