

#include "core/core.h"
#include "net/net.h"
#include "net/slip.h"
#include "net/ip.h"


byte            ip_offset;
word            ip_length;
word            ip_ident;
ip_address      ip;
data ip_header *ip_packet;



void ip_reset()
{

	ip_ident  = 0;
	ip_packet = NULL;

}



byte ip_process()
{

	ip_packet = (data ip_header*)net_get_packet();

	if (ip_packet->dst.a != ip.a || ip_packet->dst.b != ip.b ||
		ip_packet->dst.c != ip.c || ip_packet->dst.d != ip.d) {

		return 1;

	}

	if (ip_checksum((data word*)ip_packet) != 0x0000)
		return 1;

	ntohs(ip_packet->total);

	ip_offset = (ip_packet->length & 0x0f) << 2;
	ip_length = ip_packet->total.value - ip_offset;

	net_buffer_advance(ip_offset);
	net_set_proto(ip_packet->protocol);
	net_proto_relay();
	net_buffer_retract(ip_offset);

	ip_packet = NULL;
	return 1;

}



word ip_checksum(data word *header)
{

	unsigned long cksum;
	byte length;

	length = (((data ip_header*)header)->length & 0x0f) << 1;

	for (cksum=0; length > 0; length--)
		cksum += *header++;

	cksum += (cksum >> 16) & 0xffff;

	return ~cksum;

}



void ip_begin(data ip_address *dst, byte ttl, byte proto, word length)
{

	ip_header header;

	header.version     = 0x45;
	header.tos         = 0x00;
	header.total.value = sizeof(ip_header) + length;
	header.ident.value = ip_ident++;
	header.frag        = 0x00;
	header.ttl         = ttl;
	header.protocol    = proto;
	header.checksum    = 0;
	header.src.a       = ip.a;
	header.src.b       = ip.b;
	header.src.c       = ip.c;
	header.src.d       = ip.d;
	header.dst.a       = dst->a;
	header.dst.b       = dst->b;
	header.dst.c       = dst->c;
	header.dst.d       = dst->d;

	htons(header.total);
	htons(header.ident);

	header.checksum = ip_checksum((data word*)&header);

	slip_begin();
	slip_send((data byte*)&header, sizeof(ip_header));

}



void ip_send(data byte *packet, word length)
{

	slip_send(packet, length);

}



void ip_end()
{

	slip_end();

}

