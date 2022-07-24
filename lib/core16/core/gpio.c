

#include "core/core.h"
#include "core/gpio.h"



void gpio_set_input(u8 pin, bool dir)
{

	const u8 mask = 1 << GPIO_PIN_BIT(pin);
	const u8 port = GPIO_PIN_PORT(pin);

	if      (port == GPIO_PORTA) TRISA = (TRISA & ~mask) | mask;
	else if (port == GPIO_PORTB) TRISB = (TRISB & ~mask) | mask;
	else if (port == GPIO_PORTC) TRISC = (TRISC & ~mask) | mask;
	else if (port == GPIO_PORTD) TRISD = (TRISD & ~mask) | mask;
	else if (port == GPIO_PORTE) TRISE = (TRISE & ~mask) | mask;

}



bool gpio_get_input(u8 pin)
{

	const u8 mask = 1 << GPIO_PIN_BIT(pin);
	const u8 port = GPIO_PIN_PORT(pin);

	if      (port == GPIO_PORTA) return (TRISA & mask) != 0;
	else if (port == GPIO_PORTB) return (TRISB & mask) != 0;
	else if (port == GPIO_PORTC) return (TRISC & mask) != 0;
	else if (port == GPIO_PORTD) return (TRISD & mask) != 0;
	else if (port == GPIO_PORTE) return (TRISE & mask) != 0;

	return 0;

}



void gpio_write(u8 pin, bool value)
{

	const u8 mask = 1 << GPIO_PIN_BIT(pin);
	const u8 port = GPIO_PIN_PORT(pin);

	if      (port == GPIO_PORTA) PORTA = (PORTA & ~mask) | mask;
	else if (port == GPIO_PORTB) PORTB = (PORTB & ~mask) | mask;
	else if (port == GPIO_PORTC) PORTC = (PORTC & ~mask) | mask;
	else if (port == GPIO_PORTD) PORTD = (PORTD & ~mask) | mask;
	else if (port == GPIO_PORTE) PORTE = (PORTE & ~mask) | mask;

}



void gpio_toggle(u8 pin)
{

	const u8 mask = 1 << GPIO_PIN_BIT(pin);
	const u8 port = GPIO_PIN_PORT(pin);

	if      (port == GPIO_PORTA) PORTA ^= mask;
	else if (port == GPIO_PORTB) PORTB ^= mask;
	else if (port == GPIO_PORTC) PORTC ^= mask;
	else if (port == GPIO_PORTD) PORTD ^= mask;
	else if (port == GPIO_PORTE) PORTE ^= mask;

}



bool gpio_read(u8 pin)
{

	const u8 mask = 1 << GPIO_PIN_BIT(pin);
	const u8 port = GPIO_PIN_PORT(pin);

	if      (port == GPIO_PORTA) return (PORTA & mask) != 0;
	else if (port == GPIO_PORTB) return (PORTB & mask) != 0;
	else if (port == GPIO_PORTC) return (PORTC & mask) != 0;
	else if (port == GPIO_PORTD) return (PORTD & mask) != 0;
	else if (port == GPIO_PORTE) return (PORTE & mask) != 0;

	return 0;

}



void gpio_port_set_pullups(u8 port, bool pull)
{

	port = GPIO_PIN_PORT(port);

	if (port == GPIO_PORTB) {

		if (pull) INTCON2bits.RBPU = 1;
		else      INTCON2bits.RBPU = 0;

	} else if (port == GPIO_PORTD) {

		if (pull) PORTEbits.RDPU = 1;
		else      PORTEbits.RDPU = 0;

	}

}



bool gpio_port_get_pullups(u8 port)
{

	port = GPIO_PIN_PORT(port);

	if      (port == GPIO_PORTB) return INTCON2bits.RBPU;
	else if (port == GPIO_PORTD) return PORTEbits.RDPU;

	return 0;

}



void gpio_port_set_inputs(u8 port, u8 mask)
{

	port = GPIO_PIN_PORT(port);

	if      (port == GPIO_PORTA) TRISA = mask;
	else if (port == GPIO_PORTB) TRISB = mask;
	else if (port == GPIO_PORTC) TRISC = mask;
	else if (port == GPIO_PORTD) TRISD = mask;
	else if (port == GPIO_PORTE) TRISE = mask;

}



u8 gpio_port_get_inputs(u8 port)
{

	port = GPIO_PIN_PORT(port);

	if      (port == GPIO_PORTA) return TRISA;
	else if (port == GPIO_PORTB) return TRISB;
	else if (port == GPIO_PORTC) return TRISC;
	else if (port == GPIO_PORTD) return TRISD;
	else if (port == GPIO_PORTE) return TRISE;

	return 0;

}



void gpio_port_write(u8 port, u8 value)
{

	port = GPIO_PIN_PORT(port);

	if      (port == GPIO_PORTA) PORTA = value;
	else if (port == GPIO_PORTB) PORTB = value;
	else if (port == GPIO_PORTC) PORTC = value;
	else if (port == GPIO_PORTD) PORTD = value;
	else if (port == GPIO_PORTE) PORTE = value;

}



void gpio_port_toggle(u8 port, u8 mask)
{

	port = GPIO_PIN_PORT(port);

	if      (port == GPIO_PORTA) PORTA ^= mask;
	else if (port == GPIO_PORTB) PORTB ^= mask;
	else if (port == GPIO_PORTC) PORTC ^= mask;
	else if (port == GPIO_PORTD) PORTD ^= mask;
	else if (port == GPIO_PORTE) PORTE ^= mask;

}



u8 gpio_port_read(u8 port)
{

	port = GPIO_PIN_PORT(port);

	if      (port == GPIO_PORTA) return PORTA;
	else if (port == GPIO_PORTB) return PORTB;
	else if (port == GPIO_PORTC) return PORTC;
	else if (port == GPIO_PORTD) return PORTD;
	else if (port == GPIO_PORTE) return PORTE;

	return 0;

}



volatile data u8 *gpio_port_get_port(u8 port)
{

	port = GPIO_PIN_PORT(port);

	if      (port == GPIO_PORTA) return &PORTA;
	else if (port == GPIO_PORTB) return &PORTB;
	else if (port == GPIO_PORTC) return &PORTC;
	else if (port == GPIO_PORTD) return &PORTD;
	else if (port == GPIO_PORTE) return &PORTE;

	return NULL;

}



volatile data u8 *port_port_get_tris(u8 port)
{

	port = GPIO_PIN_PORT(port);

	if      (port == GPIO_PORTA) return &TRISA;
	else if (port == GPIO_PORTB) return &TRISB;
	else if (port == GPIO_PORTC) return &TRISC;
	else if (port == GPIO_PORTD) return &TRISD;
	else if (port == GPIO_PORTE) return &TRISE;

	return NULL;

}



volatile data u8 *port_port_get_lat(u8 port)
{

	port = GPIO_PIN_PORT(port);

	if      (port == GPIO_PORTA) return &LATA;
	else if (port == GPIO_PORTB) return &LATB;
	else if (port == GPIO_PORTC) return &LATC;
	else if (port == GPIO_PORTD) return &LATD;
	else if (port == GPIO_PORTE) return &LATE;

	return NULL;

}

