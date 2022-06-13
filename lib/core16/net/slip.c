

#include "core/core.h"
#include "bus/uart.h"
#include "net/net.h"
#include "net/slip.h"
#include "net/ip.h"


word slip_pos;
byte slip_state;
data byte slip_buffer[SLIP_MTU];



void slip_reset()
{

	slip_pos = 0;
	slip_state = slip_state_idle;

	uart_set_flow(1);

}



void slip_process()
{

	byte ch;


	ch = uart_read();


	if (slip_state == slip_state_ready)
		return;

	if (slip_state == slip_state_escape) {

		if (ch == SLIP_ESC_END)
			ch = SLIP_END;

		else if (ch == SLIP_ESC_ESC)
			ch = SLIP_ESC;

	} else {

		if (ch == SLIP_ESC) {

			slip_state = slip_state_escape;
			return;

		} else if (ch == SLIP_END) {

			if (slip_pos == 0) {

				slip_state = slip_state_idle;
				return;

			}

			slip_state = slip_state_ready;
			uart_set_flow(0);

			return;

		}

	}

	if (slip_pos < SLIP_MTU)
		slip_buffer[slip_pos++] = ch;

	slip_state = slip_state_transfer;

}



void slip_update()
{

	if (slip_state != slip_state_ready)
		return;

	net_set_packet(slip_buffer);
	ip_process();

	slip_reset();

}



void slip_begin()
{

	uart_write(SLIP_END);

}



void slip_send(data byte *packet, word length)
{

	byte ch;


	while (length-- > 0) {

		ch = *packet++;

		if (ch == SLIP_END) {

			uart_write(SLIP_ESC);
			uart_write(SLIP_ESC_END);

		} else if (ch == SLIP_ESC) {

			uart_write(SLIP_ESC);
			uart_write(SLIP_ESC_ESC);

		} else
			uart_write(ch);

	}

}



void slip_end()
{

	uart_write(SLIP_END);

}


