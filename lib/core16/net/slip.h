

#ifndef __SLIP_H
#define __SLIP_H


#define SLIP_PHY \
	_constructor(10, slip_reset) \
	_thread(10,      slip_update) \
	_vector(50,      slip_process, VECTOR_UART_RX)


#define SLIP_MTU      576

#define SLIP_END      0300
#define SLIP_ESC      0333
#define SLIP_ESC_END  0334
#define SLIP_ESC_ESC  0335


enum slip_state {

	slip_state_idle     = 0,
	slip_state_escape   = 1,
	slip_state_transfer = 2,
	slip_state_ready    = 3

};


void slip_reset();
void slip_process();
void slip_update();
void slip_begin();
void slip_send(data byte *packet, word length);
void slip_end();


#endif

