

#ifndef __I2C_H
#define __I2C_H


enum i2c_transfer_mode {

	i2c_transfer_idle = 0,

	i2c_transfer_spi_rx     = 1,
	i2c_transfer_spi_tx_ram = 2,
	i2c_transfer_spi_tx_rom = 3,

	i2c_transfer_i2c_rx     = 1,
	i2c_transfer_i2c_tx_ram = 2,
	i2c_transfer_i2c_tx_rom = 3,

};


void i2c_mode(byte mode);
byte i2c_io(byte value);
byte i2c_status();

void i2c_rx_transfer(data byte *buffer, byte length);
void i2c_tx_ram_transfer(data byte *buffer, byte length);
void i2c_tx_rom_transfer(code byte *buffer, byte length);

void i2c_transfer();


#endif

