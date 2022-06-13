

#ifndef __UART_H
#define __UART_H


#define UART_VECTOR_PRIORITY 100

#define MODULE_UART \
	_vector(UART_VECTOR_PRIORITY, uart_transfer_rx, VECTOR_UART_RX) \
	_vector(UART_VECTOR_PRIORITY, uart_transfer_tx, VECTOR_UART_TX)



enum uart_mode {

	uart_disabled = 0,
	uart_enabled  = 1,
	uart_hi_speed = 2,

	uart_9bit     = 4,
	uart_irq      = 8

};


enum uart_transfer_mode {

	uart_transfer_mode_idle   = 0,
	uart_transfer_mode_rx     = 1,
	uart_transfer_mode_tx_ram = 2,
	uart_transfer_mode_tx_rom = 3

};


typedef struct {

	byte mode;
	byte length;

	union {

		code byte *rom;
		data byte *ram;

	} buffer;

} uart_transfer;


#define UART_SPBRG(baud, fosc)  ((fosc) / (16 * (baud)) - 1)
#define UART_HSPBRG(baud, fosc) ((fosc) / (4  * (baud)) - 1)


void uart_mode(byte mode, word spbrg);

byte uart_read();
void uart_write(byte value);

void uart_set_flow(byte flow);
byte uart_get_flow();

void uart_rx(data byte *buffer, byte length);
void uart_tx_ram(data byte *buffer, byte length);
void uart_tx_rom(code byte *buffer, byte length);

void uart_transfer_rx();
void uart_transfer_tx();


#endif

