

#include "core/algorithm.h"
#include "core/core.h"

#include "usb/usb.h"

#include "joystick.h"
#include "usbdev.h"



void setup()
{

	RCONbits.IPEN   = 1;
	INTCONbits.GIEL = 1;
	INTCONbits.GIEH = 1;

	isr_attach(ISR_HIGH, &usbdev_process);

	joystick_init();
	usbdev_init();

}



void loop()
{

	joystick_update();

	if (JOYSTICK_STATE_AXIS_X >= 0) usbdev_set_axis(JOYSTICK_STATE_AXIS_X, joystick_state[JOYSTICK_STATE_AXIS_X]);
	if (JOYSTICK_STATE_AXIS_Y >= 0) usbdev_set_axis(JOYSTICK_STATE_AXIS_Y, joystick_state[JOYSTICK_STATE_AXIS_Y]);
	if (JOYSTICK_STATE_AXIS_Z >= 0) usbdev_set_axis(JOYSTICK_STATE_AXIS_Z, joystick_state[JOYSTICK_STATE_AXIS_Z]);

	if (JOYSTICK_STATE_AXIS_RX >= 0) usbdev_set_axis(JOYSTICK_STATE_AXIS_RX, joystick_state[JOYSTICK_STATE_AXIS_RX]);
	if (JOYSTICK_STATE_AXIS_RY >= 0) usbdev_set_axis(JOYSTICK_STATE_AXIS_RY, joystick_state[JOYSTICK_STATE_AXIS_RY]);
	if (JOYSTICK_STATE_AXIS_RZ >= 0) usbdev_set_axis(JOYSTICK_STATE_AXIS_RZ, joystick_state[JOYSTICK_STATE_AXIS_RZ]);

	if (JOYSTICK_STATE_AXIS_VX >= 0) usbdev_set_axis(JOYSTICK_STATE_AXIS_VX, joystick_state[JOYSTICK_STATE_AXIS_VX]);
	if (JOYSTICK_STATE_AXIS_VY >= 0) usbdev_set_axis(JOYSTICK_STATE_AXIS_VY, joystick_state[JOYSTICK_STATE_AXIS_VY]);
	if (JOYSTICK_STATE_AXIS_VZ >= 0) usbdev_set_axis(JOYSTICK_STATE_AXIS_VZ, joystick_state[JOYSTICK_STATE_AXIS_VZ]);

	if (JOYSTICK_STATE_THROTTLE >= 0) usbdev_set_axis(JOYSTICK_STATE_THROTTLE, joystick_state[JOYSTICK_STATE_THROTTLE]);
	if (JOYSTICK_STATE_RUDDER   >= 0) usbdev_set_axis(JOYSTICK_STATE_RUDDER,   joystick_state[JOYSTICK_STATE_RUDDER]);
	if (JOYSTICK_STATE_POVHAT   >= 0) usbdev_set_axis(JOYSTICK_STATE_POVHAT,   joystick_state[JOYSTICK_STATE_POVHAT]);

	usbdev_set_buttons(joystick_state[JOYSTICK_STATE_BUTTONS]);

}

