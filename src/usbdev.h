

#ifndef USBDEV_H
#define USBDEV_H


void usbdev_init();
void usbdev_process();

void usbdev_set_axis(i8 n, word value);
void usbdev_set_buttons(word mask);


#endif

