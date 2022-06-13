

#include "core/core.h"
#include "net/net.h"
#include "net/ip.h"
#include "net/udp.h"


data udp_header *udp_packet;



void udp_reset()
{

	udp_packet = NULL;

}



byte udp_process()
{

	udp_packet = (data udp_header*)net_get_packet();

	ntohs(udp_packet->dst);
	ntohs(udp_packet->src);
	ntohs(udp_packet->length);

	net_buffer_advance(sizeof(udp_header));
	net_set_socket(udp_packet->dst.value);
	net_socket_relay();
	net_buffer_retract(sizeof(udp_header));

	udp_packet = NULL;

	return 1;
}



void udp_reply(data byte *packet, word length)
{

	udp_socket sock;


	if (!ip_is_valid() || !udp_is_valid() || udp_get_src() == 0)
		return;

	sock.ip.a = ip_get_source().a;
	sock.ip.b = ip_get_source().b;
	sock.ip.c = ip_get_source().c;
	sock.ip.d = ip_get_source().d;
	sock.port = udp_packet->src.value;

	udp_send(&sock, udp_packet->src.value, packet, length);

}



void udp_send(data udp_socket *dst, word source, data byte *packet, word length)
{

	udp_header header;


	header.dst.value      = dst->port;
	header.src.value      = source;
	header.length.value   = length + sizeof(udp_header);
	header.checksum.value = 0;

	ip_begin((data ip_address*)dst, IP_DEFAULT_TTL, UDP_PROTOCOL_NUMBER, header.length.value);

	htons(header.dst);
	htons(header.src);
	htons(header.length);

	ip_send((data byte*)&header, sizeof(udp_header));
	ip_send(packet, length);

	ip_end();

}

