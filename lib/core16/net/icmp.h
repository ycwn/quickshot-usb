

#ifndef __ICMP_H
#define __ICMP_H


typedef struct {

	word type;
	word checksum;
	word ident;
	word sequence;

} icmp_header;


#define ICMP_PROTOCOL_NUMBER 0x01
#define ICMP_PROTOCOL \
			_constructor(NET_CONSTRUCTOR_PRIORITY, icmp_reset) \
			_protocol(ICMP_PROTOCOL_NUMBER,        icmp_process)

#define ICMP_ECHO_REPLY              0x0000
#define ICMP_DEST_UNREACHABLE_NET    0x0003
#define ICMP_DEST_UNREACHABLE_HOST   0x0103
#define ICMP_DEST_UNREACHABLE_PROTO  0x0203
#define ICMP_DEST_UNREACHABLE_PORT   0x0303
#define ICMP_DEST_UNKNOWN_NET        0x0603
#define ICMP_DEST_UNKNOWN_HOST       0x0703
#define ICMP_ECHO_REQUEST            0x0008
#define ICMP_TIME_EXCEEDED_TTL       0x000b
#define ICMP_TIME_EXCEEDED_FRAG      0x010b


void icmp_reset();
byte icmp_process();
void icmp_send(data ip_address *dst, word message, data byte *packet, word length);
word icmp_checksum(data icmp_header *header, data word *packet, word length);


#endif

