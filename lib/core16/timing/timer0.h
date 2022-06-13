

#ifndef __TIMER0_H
#define __TIMER0_H


void timer0_mode(byte mode);

byte timer0_read8();
word timer0_read16();

void timer0_write8(byte value);
void timer0_write16(word value);


#endif

