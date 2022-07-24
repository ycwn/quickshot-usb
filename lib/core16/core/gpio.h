

#ifndef CORE_GPIO_H
#define CORE_GPIO_H


enum {

	GPIO_OUTPUT = 0,
	GPIO_INPUT  = 1,

	GPIO_PULLUP = 8

};


enum {

	GPIO_PORTA = 0 << 3,
	GPIO_PORTB = 1 << 3,
	GPIO_PORTC = 2 << 3,
	GPIO_PORTD = 3 << 3,
	GPIO_PORTE = 4 << 3

};


enum {

	RA0 = GPIO_PORTA | 0,
	RA1 = GPIO_PORTA | 1,
	RA2 = GPIO_PORTA | 2,
	RA3 = GPIO_PORTA | 3,
	RA4 = GPIO_PORTA | 4,
	RA5 = GPIO_PORTA | 5,
	RA6 = GPIO_PORTA | 6,
	RA7 = GPIO_PORTA | 7,

	RB0 = GPIO_PORTB | 0,
	RB1 = GPIO_PORTB | 1,
	RB2 = GPIO_PORTB | 2,
	RB3 = GPIO_PORTB | 3,
	RB4 = GPIO_PORTB | 4,
	RB5 = GPIO_PORTB | 5,
	RB6 = GPIO_PORTB | 6,
	RB7 = GPIO_PORTB | 7,

	RC0 = GPIO_PORTC | 0,
	RC1 = GPIO_PORTC | 1,
	RC2 = GPIO_PORTC | 2,
	RC3 = GPIO_PORTC | 3,
	RC4 = GPIO_PORTC | 4,
	RC5 = GPIO_PORTC | 5,
	RC6 = GPIO_PORTC | 6,
	RC7 = GPIO_PORTC | 7,

	RD0 = GPIO_PORTD | 0,
	RD1 = GPIO_PORTD | 1,
	RD2 = GPIO_PORTD | 2,
	RD3 = GPIO_PORTD | 3,
	RD4 = GPIO_PORTD | 4,
	RD5 = GPIO_PORTD | 5,
	RD6 = GPIO_PORTD | 6,
	RD7 = GPIO_PORTD | 7,

	RE0 = GPIO_PORTE | 0,
	RE1 = GPIO_PORTE | 1,
	RE2 = GPIO_PORTE | 2,
	RE3 = GPIO_PORTE | 3,
	RE4 = GPIO_PORTE | 4,
	RE5 = GPIO_PORTE | 5,
	RE6 = GPIO_PORTE | 6,
	RE7 = GPIO_PORTE | 7

};


enum {

	AN0  = (0  << 8) | RA0,
	AN1  = (1  << 8) | RA1,
	AN2  = (2  << 8) | RA2,
	AN3  = (3  << 8) | RA3,
	AN4  = (4  << 8) | RA5,
	AN5  = (5  << 8) | RE0,
	AN6  = (6  << 8) | RE1,
	AN7  = (7  << 8) | RE2,
	AN8  = (8  << 8) | RB2,
	AN9  = (9  << 8) | RB3,
	AN10 = (10 << 8) | RB1,
	AN11 = (11 << 8) | RB4,
	AN12 = (12 << 8) | RB0,
	AN13 = (13 << 8) | RB5,
	AN14 = (14 << 8) | RC2,
	AN15 = (15 << 8) | RC3,
	AN16 = (16 << 8) | RC4,
	AN17 = (17 << 8) | RC5,
	AN18 = (18 << 8) | RC6,
	AN19 = (19 << 8) | RC7,
	AN20 = (20 << 8) | RD0,
	AN21 = (21 << 8) | RD1,
	AN22 = (22 << 8) | RD2,
	AN23 = (23 << 8) | RD3,
	AN24 = (24 << 8) | RD4,
	AN25 = (25 << 8) | RD5,
	AN26 = (26 << 8) | RD6,
	AN27 = (27 << 8) | RD7

};


#define GPIO_PIN_BIT(pin)    ((pin) & 0x0007)
#define GPIO_PIN_PORT(pin)   ((pin) & 0x0038)
#define GPIO_PIN_ANALOG(pin) ((pin) & 0xff00)


void gpio_set_input(u8 pin, bool dir);
bool gpio_get_input(u8 pin);
void gpio_write(u8 pin, bool value);
void gpio_toggle(u8 pin);
bool gpio_read(u8 pin);

void gpio_port_set_pullups(u8 port, bool pull);
bool gpio_port_get_pullups(u8 port);
void gpio_port_set_inputs(u8 port, u8 mask);
u8   gpio_port_get_inputs(u8 port);
void gpio_port_write(u8 pin, u8 value);
void gpio_port_toggle(u8 pin, u8 mask);
u8   gpio_port_read(u8 pin);

volatile data u8 *gpio_port_get_port(u8 port);
volatile data u8 *gpio_port_get_tris(u8 port);
volatile data u8 *gpio_port_get_lat(u8 port);


#endif

