

#ifndef __CORE_H
#define __CORE_H


#include <stddef.h>
#include <pic18fregs.h>


#ifdef AUTOMAGIC
#define _constructor(pri, func)    automagic(constructor, pri, func)
#define _thread(pri, func)         automagic(thread,      pri, func)
#define _vector(pri, func, vec...) automagic(vector,      pri, func, vec)
#define MODULE_SETUP(module...)    module
#else
#define _constructor(pri, func)
#define _thread(pri, func)
#define _vector(pri, func, vec...)
#define MODULE_SETUP(module...)
#endif


#define nop()     { _asm nop _endasm; }
#define hlt()     { _asm goto $+0 _endasm; }
#define iodelay() { _asm goto $+4 _endasm; }
#define use(x)    { (x); }


#define VECTOR_ADC_SAMPLE          PIR1, 6
#define VECTOR_CCP1_CAPTURE        PIR1, 2
#define VECTOR_CCP1_COMPARE        PIR1, 2
#define VECTOR_CCP2_CAPTURE        PIR2, 0
#define VECTOR_CCP2_COMPARE        PIR2, 0
#define VECTOR_COMPARATOR          PIR2, 6
#define VECTOR_EEPROM_WRITE        PIR2, 4
#define VECTOR_I2C_COLLISION       PIR2, 3
#define VECTOR_I2C_TRANSFER        PIR1, 3
#define VECTOR_INT0                0xff2, 1
#define VECTOR_INT1                0xff0, 0
#define VECTOR_INT2                0xff0, 1
#define VECTOR_MF_CAPTURE1         0xfa4, 1
#define VECTOR_MF_CAPTURE2         0xfa4, 2
#define VECTOR_MF_CAPTURE3         0xfa4, 3
#define VECTOR_OSCILLATOR_FAIL     PIR2, 7
#define VECTOR_PARPORT             PIR1, 7
#define VECTOR_PORTB_CHANGE        0xff2, 0
#define VECTOR_PWM_TIME_BASE       0xfa4, 4
#define VECTOR_QEI_VELOCITY        0xfa4, 1
#define VECTOR_QEI_POSITION        0xfa4, 2
#define VECTOR_QEI_DIRECTION       0xfa4, 3
#define VECTOR_SPI_TRANSFER        PIR1, 3
#define VECTOR_TIMER0              0xff2, 2
#define VECTOR_TIMER1              PIR1, 0
#define VECTOR_TIMER2              PIR1, 1
#define VECTOR_TIMER3              PIR2, 1
#define VECTOR_TIMER5              0xfa4, 0
#define VECTOR_UART_RX             PIR1, RCIF
#define VECTOR_UART_TX             PIR1, TXIF
#define VECTOR_USB                 PIR2, 5
#define VECTOR_USB_ACTIVE          0xf68, 2
#define VECTOR_USB_ERROR           0xf68, 1
#define VECTOR_USB_ERROR_BITSTUFF  0xf6a, 7
#define VECTOR_USB_ERROR_CRC5      0xf6a, 1
#define VECTOR_USB_ERROR_CRC16     0xf6a, 2
#define VECTOR_USB_ERROR_DNF8      0xf6a, 3
#define VECTOR_USB_ERROR_PID       0xf6a, 0
#define VECTOR_USB_ERROR_TIMEOUT   0xf6a, 4
#define VECTOR_USB_FRAME_START     0xf68, 6
#define VECTOR_USB_IDLE            0xf68, 4
#define VECTOR_USB_STALL           0xf68, 5
#define VECTOR_USB_RESET           0xf68, 0
#define VECTOR_USB_TRANSFER        0xf68, 3
#define VECTOR_VOLTAGE_DETECT      0xfa1, 2


typedef unsigned char  byte;
typedef unsigned short word;
typedef unsigned long  dword;

#define BYTE( x, n)  (((x) >> (8  * (n))) & 255)
#define WORD( x, n)  (((x) >> (16 * (n))) & 65535)
#define DWORD(x, n)  (((x) >> (32 * (n))) & 4294967295)

#define WORD2( a, b)        ((a) | ((b) <<  8))
#define DWORD2(a, b)        ((a) | ((b) << 16))
#define DWORD4(a, b, c, d)  ((a) | ((b) <<  8) | ((c) << 16) | ((d) << 24))

static char mini8( char a, char b) { return (a < b)? a: b; }
static int  mini16(int  a, int  b) { return (a < b)? a: b; }
static long mini32(long a, long b) { return (a < b)? a: b; }

static byte  minu8( byte  a, byte  b) { return (a < b)? a: b; }
static word  minu16(word  a, word  b) { return (a < b)? a: b; }
static dword minu32(dword a, dword b) { return (a < b)? a: b; }

static char maxi8( char a, char b) { return (a > b)? a: b; }
static int  maxi16(int  a, int  b) { return (a > b)? a: b; }
static long maxi32(long a, long b) { return (a > b)? a: b; }

static byte  maxu8( byte  a, byte  b) { return (a > b)? a: b; }
static word  maxu16(word  a, word  b) { return (a > b)? a: b; }
static dword maxu32(dword a, dword b) { return (a > b)? a: b; }


void usleep(byte usec);
void msleep(byte msec);
void sleep(byte sec);


#endif

