

//
// SpectraVideo QuickShot II Plus SVI-102
//
#ifdef CONFIG_JOYSTICK_SVI102


#define JOYSTICK_VENDOR    'S','p','e','c','t','r','a','V','i','d','e','o'
#define JOYSTICK_NAME      'Q','u','i','c','k','S','h','o','t',' ','I','I',' ','P','l','u','s',' ','-',' ','S','V','I','-','1','0','2'
#define JOYSTICK_SERIAL    'S','V','I','-','1','0','2'

#define JOYSTICK_BUTTONS    RB0, RB1

#define JOYSTICK_AXIS_X     DIGITAL(RA0, RA1)
#define JOYSTICK_AXIS_Y     DIGITAL(RA2, RA3)
#define JOYSTICK_AXIS_Z     DISABLED

#define JOYSTICK_AXIS_RX    DISABLED
#define JOYSTICK_AXIS_RY    DISABLED
#define JOYSTICK_AXIS_RZ    DISABLED

#define JOYSTICK_AXIS_VX    DISABLED
#define JOYSTICK_AXIS_VY    DISABLED
#define JOYSTICK_AXIS_VZ    DISABLED

#define JOYSTICK_THROTTLE   DISABLED
#define JOYSTICK_RUDDER     DISABLED
#define JOYSTICK_POVHAT     DISABLED


#endif

