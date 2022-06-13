

#ifndef __NET_H
#define __NET_H


#define MODULE_NETWORK \
			_constructor(NET_CONSTRUCTOR_PRIORITY, net)


typedef union {

	word value;

	struct {

		byte high;
		byte low;

	};

} netword;

#define NET_CONSTRUCTOR_PRIORITY 10

#define NET_HIGH(word) (((word) >> 8) & 255)
#define NET_LOW(word)  ((word) & 255)


#ifdef AUTOMAGIC
#define _protocol(number, processor) automagic(protocol, number, processor)
#define _socket(number, handler)     automagic(socket, number, handler)
#else
#define _protocol(number, processor)
#define _socket(number, handler)
#endif


extern byte       net_proto_number;
extern word       net_socket_number;
extern data byte *net_buffer;


#define net_get_packet()          (net_buffer)
#define net_set_packet(buffer)    net_buffer = (buffer);
#define net_buffer_advance(bytes) net_buffer += (bytes);
#define net_buffer_retract(bytes) net_buffer -= (bytes);
#define net_get_proto()           (net_proto_number)
#define net_set_proto(number)     net_proto_number = (number)
#define net_get_socket()          (net_socket_number)
#define net_set_socket(number)    net_socket_number = (number)

#define htons(word) { word.high ^= word.low; word.low ^= word.high; word.high ^= word.low; }
#define ntohs(word) htons(word)


void net();
byte net_proto_relay();
byte net_socket_relay();


#endif

