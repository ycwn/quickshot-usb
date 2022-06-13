

#ifndef __SPI_H
#define __SPI_H


enum spi_transfer_mode {

	spi_transfer_idle = 0,

	spi_transfer_spi_rx     = 1,
	spi_transfer_spi_tx_ram = 2,
	spi_transfer_spi_tx_rom = 3,

};


void spi_mode(byte mode);
byte spi_io(byte value);
byte spi_status();

void spi_rx_transfer(data byte *buffer, byte length);
void spi_tx_ram_transfer(data byte *buffer, byte length);
void spi_tx_rom_transfer(code byte *buffer, byte length);

void spi_transfer();


#endif

