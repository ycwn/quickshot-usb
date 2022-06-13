

#ifndef __TCP_H
#define __TCP_H



typedef struct {

	word src;
	word dst;

	dword sequence_number;
	dword acknowledgement_number;

	byte offset;
	byte flags;
	word window;

	word checksum;
	word urgent;

	byte options[40];

} tcp_header;


#define TCP_PROTOCOL_NUMBER 0x06
#define TCP_PROTOCOL

extern data tcp_header *tcp_packet;


void tcp_enter(data byte *packet, word length);
void tcp_leave();
void tcp_connect();
void tcp_close();


#endif

