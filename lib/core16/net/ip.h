

#ifndef __IP_H
#define __IP_H


typedef struct {

	byte a;
	byte b;
	byte c;
	byte d;

} ip_address;


typedef struct {

	union {

		byte version;
		byte length;

	};

	byte    tos;
	netword total;

	netword ident;
	word    frag;

	byte ttl;
	byte protocol;
	word checksum;

	ip_address src;
	ip_address dst;

} ip_header;


#define IP_DEFAULT_TTL     100
#define IP_PROTOCOL_NUMBER 0x04
#define IP_PROTOCOL \
			_constructor(NET_CONSTRUCTOR_PRIORITY, ip_reset) \
			_protocol(IP_PROTOCOL_NUMBER,          ip_process)


extern ip_address       ip;
extern data ip_header  *ip_packet;
extern byte             ip_offset;
extern word             ip_length;


#define ip_is_valid()                   (ip_packet != NULL)
#define ip_get_ttl()                    (ip_packet->time_to_live)
#define ip_get_proto()                  (ip_packet->protocol)
#define ip_get_source()                 (ip_packet->src)
#define ip_get_length()                 (ip_length)
#define ip_get_address()                (ip)
#define ip_set_address(_a, _b, _c, _d)  { ip.a = (_a); ip.b = (_b); ip.c = (_c); ip.d = (_d); }

void ip_reset();
byte ip_process();
word ip_checksum(data word *header);
void ip_begin(data ip_address *dst, byte ttl, byte proto, word length);
void ip_send(data byte *packet, word length);
void ip_end();


#endif

