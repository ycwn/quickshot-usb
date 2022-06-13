

#ifndef __GPIO_H
#define __GPIO_H


#define GPIO_LOW    0
#define GPIO_HIGH   1

#define GPIO_OUTPUT 0
#define GPIO_INPUT  1

//
// PORTA alias
//

#define PORT_A(pin) (PORTAbits.RA ## pin)
#define TRIS_A(pin) (TRISAbits.TRISA ## pin)
#define GPIO_A(pin) (LATAbits.LATA ## pin)


//
// PORTB alias
//

#define PORT_B(pin) (PORTBbits.RB ## pin)
#define TRIS_B(pin) (TRISBbits.TRISB ## pin)
#define GPIO_B(pin) (LATBbits.LATB ## pin)


//
// PORTC alias
//

#define PORT_C(pin) (PORTCbits.RC ## pin)
#define TRIS_C(pin) (TRISCbits.TRISC ## pin)
#define GPIO_C(pin)  (LATCbits.LATC ## pin)


//
// PORTD alias
//

#define PORT_D(pin) (PORTDbits.RD ## pin)
#define TRIS_D(pin) (TRISDbits.TRISD ## pin)
#define GPIO_D(pin) (LATDbits.LATD ## pin)


//
// PORTE alias
//

#define PORT_E(pin) (PORTEbits.RE ## pin)
#define TRIS_E(pin) (TRISEbits.TRISE ## pin)
#define GPIO_E(pin) (LATEbits.LATE ## pin)


#endif

