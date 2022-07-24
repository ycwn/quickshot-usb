

//
// QuickShot Skymaster QS-206
//
#ifdef CONFIG_JOYSTICK_QS206


#define JOYSTICK_VENDOR    'Q','u','i','c','k','S','h','o','t'
#define JOYSTICK_NAME      'S','k','y','m','a','s','t','e','r',' ','Q','S','-','2','0','6'
#define JOYSTICK_SERIAL    'Q','S','-','2','0','6'

#define JOYSTICK_BUTTONS    RB0, RB1, RB2, RB3

#define JOYSTICK_AXIS_X     ANALOG(RA0)
#define JOYSTICK_AXIS_Y     ANALOG(RA1)
#define JOYSTICK_AXIS_Z     DISABLED

#define JOYSTICK_AXIS_RX    DISABLED
#define JOYSTICK_AXIS_RY    DISABLED
#define JOYSTICK_AXIS_RZ    DISABLED

#define JOYSTICK_AXIS_VX    DISABLED
#define JOYSTICK_AXIS_VY    DISABLED
#define JOYSTICK_AXIS_VZ    DISABLED

#define JOYSTICK_THROTTLE   ANALOG(RA2)
#define JOYSTICK_RUDDER     DISABLED
#define JOYSTICK_POVHAT     ANALOG(RA3)


#endif

