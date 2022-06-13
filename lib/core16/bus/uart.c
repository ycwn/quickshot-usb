

#include "core/core.h"
#include "core/gpio.h"

#include "bus/uart.h"


uart_transfer uart;



void uart_mode(byte mode, word spbrg)
{

	uart.mode = uart_transfer_mode_idle;

	if ((mode & uart_enabled) != 0) {

		TRISC |= 0xc0;

		SPBRGH = ((spbrg) >> 8) & 255;
		SPBRG  = (spbrg) & 255;

		BAUDCON = 0x08;
		RCSTA   = 0x90;

		if ((mode & uart_hi_speed) != 0)
			TXSTA = 0x24;

		else
			TXSTA = 0x20;

		if (mode & uart_irq)
			PIE1bits.RCIE = 1;

		else
			PIE1bits.RCIE = 0;

	} else {

		BAUDCON = 0x00;
		TXSTA   = 0x00;
		RCSTA   = 0x00;

		PIE1bits.RCIE = 0;
		PIE1bits.TXIE = 0;

	}

}



byte uart_read()
{

	if (RCSTAbits.OERR) {

		RCSTAbits.CREN = 0;
		RCSTAbits.CREN = 1;

	}

	return RCREG;

}



void uart_write(byte value)
{

	while (!TXSTAbits.TRMT);

	TXREG = value;

}



void uart_set_flow(byte value)
{


}



byte uart_get_flow()
{

	return 1;

}



void uart_rx(data byte *buffer, byte length)
{

	uart.length     = length;
	uart.buffer.ram = buffer;
	uart.mode       = uart_transfer_mode_rx;

}



void uart_tx_ram(data byte *buffer, byte length)
{

	uart.length     = length;
	uart.buffer.ram = buffer;
	uart.mode       = uart_transfer_mode_tx_ram;

	uart_transfer_tx();

}



void uart_tx_rom(code byte *buffer, byte length)
{

	uart.length     = length;
	uart.buffer.rom = buffer;
	uart.mode       = uart_transfer_mode_tx_rom;

	uart_transfer_tx();

}



void uart_transfer_rx()
{

}



void uart_transfer_tx()
{

}

