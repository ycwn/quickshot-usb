

#ifndef __UDP_H
#define __UDP_H


typedef struct {

	netword src;
	netword dst;
	netword length;
	netword checksum;

} udp_header;


typedef struct {

	ip_address ip;
	word       port;

} udp_socket;


#define UDP_PROTOCOL_NUMBER 0x11
#define UDP_PROTOCOL \
			_constructor(NET_CONSTRUCTOR_PRIORITY, udp_reset) \
			_protocol(UDP_PROTOCOL_NUMBER,         udp_process)


extern data udp_header *udp_packet;


#define udp_is_valid()    (udp_packet != NULL)
#define udp_get_length()  (udp_packet->length.value)
#define udp_get_src()     (udp_packet->src.value)
#define udp_get_dst()     (udp_packet->dst.value)

byte udp_process();
void udp_reply(data byte *packet, word length);
void udp_send(data udp_socket *dest, word source, data byte *packet, word length);
word udp_cksum(data byte *packet, word length);


#endif

