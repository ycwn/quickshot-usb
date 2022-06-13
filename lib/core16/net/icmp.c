

#include "core/core.h"
#include "net/net.h"
#include "net/ip.h"
#include "net/icmp.h"



void icmp_reset()
{
}



byte icmp_process()
{

	data icmp_header *icmp_packet = (data icmp_header*)net_get_packet();

	if (icmp_packet->type == ICMP_ECHO_REQUEST) {

		icmp_header reply;

		reply.type     = ICMP_ECHO_REPLY;
		reply.ident    = icmp_packet->ident;
		reply.sequence = icmp_packet->sequence;

		reply.checksum = icmp_checksum(&reply,
							(data word*)(net_get_packet() + sizeof(icmp_header)),
							ip_get_length()  - sizeof(icmp_header));

		ip_begin(&ip_packet->src,
			IP_DEFAULT_TTL, ICMP_PROTOCOL_NUMBER,
			sizeof(icmp_header) + ip_get_length());

		ip_send((data byte*)&reply, sizeof(icmp_header));

		if (ip_get_length() > sizeof(icmp_header))
			ip_send(
				net_get_packet() + sizeof(icmp_header),
				ip_get_length()  - sizeof(icmp_header));

		ip_end();

	}

	return 1;

}



void icmp_send(data ip_address *dst, word message, data byte *packet, word length)
{

	icmp_header header;

	header.type     = message;
	header.ident    = 0;
	header.sequence = 0;
	header.checksum = icmp_checksum(&header, (data word*)packet, length);

	ip_begin(dst, IP_DEFAULT_TTL, ICMP_PROTOCOL_NUMBER, sizeof(icmp_header) + length);

	ip_send((data byte*)&header, sizeof(icmp_header));

	if (length > 0)
		ip_send(packet, length);

	ip_end();

}



word icmp_checksum(data icmp_header *header, data word *packet, word length)
{

	unsigned long cksum;

	cksum = header->type + header->ident + header->sequence;

	for (; length >= 2; length -= 2)
		cksum += *packet++;

	if (length > 0)
		cksum += (*packet) & 0xff;

	cksum += (cksum >> 16) & 0xffff;

	return ~cksum;

}

