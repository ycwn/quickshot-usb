

#ifndef USB_HID_H
#define USB_HID_H


enum {

	USB_DESCRIPTOR_HID          = 0x21,
	USB_DESCRIPTOR_HID_REPORT   = 0x22,
	USB_DESCRIPTOR_HID_PHYSICAL = 0x23

};


enum {

	USB_CLASS_HID = 0x03

};


enum {

	USB_SUBCLASS_HID_BOOT = 0x01

};


enum {

	USB_PROTOCOL_HID_KEYBOARD = 0x01,
	USB_PROTOCOL_HID_MOUSE    = 0x02

};


enum {

	USB_HID_VERSION = 0x111

};


enum {

	USB_REQUEST_TYPE_HID_INTERFACE_IN  = USB_REQUEST_DIR_D2H | USB_REQUEST_TYPE_CLASS | USB_REQUEST_RCPT_INTERFACE,
	USB_REQUEST_TYPE_HID_INTERFACE_OUT = USB_REQUEST_DIR_H2D | USB_REQUEST_TYPE_CLASS | USB_REQUEST_RCPT_INTERFACE

};


enum {

	USB_REQUEST_CODE_HID_GET_REPORT   = 0x01,
	USB_REQUEST_CODE_HID_GET_IDLE     = 0x02,
	USB_REQUEST_CODE_HID_GET_PROTOCOL = 0x03,

	USB_REQUEST_CODE_HID_SET_REPORT   = 0x09,
	USB_REQUEST_CODE_HID_SET_IDLE     = 0x0a,
	USB_REQUEST_CODE_HID_SET_PROTOCOL = 0x0b

};


enum {

	USB_HID_REQUEST_GET_DESCRIPTOR = USB_MKRQID(USB_REQUEST_TYPE_INTERFACE_IN, USB_REQUEST_CODE_GET_DESCRIPTOR),

	USB_HID_REQUEST_GET_REPORT   = USB_MKRQID(USB_REQUEST_TYPE_HID_INTERFACE_IN, USB_REQUEST_CODE_HID_GET_REPORT),
	USB_HID_REQUEST_GET_IDLE     = USB_MKRQID(USB_REQUEST_TYPE_HID_INTERFACE_IN, USB_REQUEST_CODE_HID_GET_IDLE),
	USB_HID_REQUEST_GET_PROTOCOL = USB_MKRQID(USB_REQUEST_TYPE_HID_INTERFACE_IN, USB_REQUEST_CODE_HID_GET_PROTOCOL),

	USB_HID_REQUEST_SET_REPORT   = USB_MKRQID(USB_REQUEST_TYPE_HID_INTERFACE_OUT, USB_REQUEST_CODE_HID_SET_REPORT),
	USB_HID_REQUEST_SET_IDLE     = USB_MKRQID(USB_REQUEST_TYPE_HID_INTERFACE_OUT, USB_REQUEST_CODE_HID_SET_IDLE),
	USB_HID_REQUEST_SET_PROTOCOL = USB_MKRQID(USB_REQUEST_TYPE_HID_INTERFACE_OUT, USB_REQUEST_CODE_HID_SET_PROTOCOL)

};


enum {
	USB_HID_LOCALE_NONE        =  0,
	USB_HID_LOCALE_ARABIC      =  1,
	USB_HID_LOCALE_BELGIAN     =  2,
	USB_HID_LOCALE_CANADIAN    =  3,
	USB_HID_LOCALE_CANADIAN_FR =  4,
	USB_HID_LOCALE_CZECH       =  5,
	USB_HID_LOCALE_DANISH      =  6,
	USB_HID_LOCALE_FINNISH     =  7,
	USB_HID_LOCALE_FRENCH      =  8,
	USB_HID_LOCALE_GERMAN      =  9,
	USB_HID_LOCALE_GREEK       = 10,
	USB_HID_LOCALE_HEBREW      = 11,
	USB_HID_LOCALE_HUNGARY     = 12,
	USB_HID_LOCALE_ISO         = 13,
	USB_HID_LOCALE_ITALIAN     = 14,
	USB_HID_LOCALE_JAPAN       = 15,
	USB_HID_LOCALE_KOREAN      = 16,
	USB_HID_LOCALE_LATIN       = 17,
	USB_HID_LOCALE_DUTCH       = 18,
	USB_HID_LOCALE_NORWEGIAN   = 19,
	USB_HID_LOCALE_PERSIAN     = 20,
	USB_HID_LOCALE_POLISH      = 21,
	USB_HID_LOCALE_PORTUGUESE  = 22,
	USB_HID_LOCALE_RUSSIAN     = 23,
	USB_HID_LOCALE_SLOVAKIAN   = 24,
	USB_HID_LOCALE_SPANISH     = 25,
	USB_HID_LOCALE_SWEDISH     = 26,
	USB_HID_LOCALE_SWISS_FR    = 27,
	USB_HID_LOCALE_SWISS_DE    = 28,
	USB_HID_LOCALE_SWISS       = 29,
	USB_HID_LOCALE_TAIWAN      = 30,
	USB_HID_LOCALE_TURKISH_Q   = 31,
	USB_HID_LOCALE_UK          = 32,
	USB_HID_LOCALE_US          = 33,
	USB_HID_LOCALE_YUGOSLAVIC  = 34,
	USB_HID_LOCALE_TURKISH_F   = 35
};


/**
 *  USB keyboard scancodes. Usage Page 07: Keyboard
 *  Copied from MightyPork
 *  https://gist.github.com/MightyPork/6da26e382a7ad91b5496ee55fdc73db2
 **/
enum {

	// Modifier masks - used for the first byte in the HID report.

	USB_HID_KEY_MOD_LCTRL  = 0x01,
	USB_HID_KEY_MOD_LSHIFT = 0x02,
	USB_HID_KEY_MOD_LALT   = 0x04,
	USB_HID_KEY_MOD_LMETA  = 0x08,
	USB_HID_KEY_MOD_RCTRL  = 0x10,
	USB_HID_KEY_MOD_RSHIFT = 0x20,
	USB_HID_KEY_MOD_RALT   = 0x40,
	USB_HID_KEY_MOD_RMETA  = 0x80,

	// Scan codes - last N slots in the HID report (usually 6).

	USB_HID_KEY_NONE          = 0x00,       // No key pressed
	USB_HID_KEY_ERR_OVF       = 0x01,       // Keyboard Error Roll Over - used for all slots if too many keys are pressed ("Phantom key")
	USB_HID_KEY_ERR_POST_FAIL = 0x02,       // Keyboard POST Fail
	USB_HID_KEY_ERR_UNDEFINED = 0x03,       // Keyboard Error Undefined

	USB_HID_KEY_A = 0x04,                   // Keyboard a and A
	USB_HID_KEY_B = 0x05,                   // Keyboard b and B
	USB_HID_KEY_C = 0x06,                   // Keyboard c and C
	USB_HID_KEY_D = 0x07,                   // Keyboard d and D
	USB_HID_KEY_E = 0x08,                   // Keyboard e and E
	USB_HID_KEY_F = 0x09,                   // Keyboard f and F
	USB_HID_KEY_G = 0x0a,                   // Keyboard g and G
	USB_HID_KEY_H = 0x0b,                   // Keyboard h and H
	USB_HID_KEY_I = 0x0c,                   // Keyboard i and I
	USB_HID_KEY_J = 0x0d,                   // Keyboard j and J
	USB_HID_KEY_K = 0x0e,                   // Keyboard k and K
	USB_HID_KEY_L = 0x0f,                   // Keyboard l and L
	USB_HID_KEY_M = 0x10,                   // Keyboard m and M
	USB_HID_KEY_N = 0x11,                   // Keyboard n and N
	USB_HID_KEY_O = 0x12,                   // Keyboard o and O
	USB_HID_KEY_P = 0x13,                   // Keyboard p and P
	USB_HID_KEY_Q = 0x14,                   // Keyboard q and Q
	USB_HID_KEY_R = 0x15,                   // Keyboard r and R
	USB_HID_KEY_S = 0x16,                   // Keyboard s and S
	USB_HID_KEY_T = 0x17,                   // Keyboard t and T
	USB_HID_KEY_U = 0x18,                   // Keyboard u and U
	USB_HID_KEY_V = 0x19,                   // Keyboard v and V
	USB_HID_KEY_W = 0x1a,                   // Keyboard w and W
	USB_HID_KEY_X = 0x1b,                   // Keyboard x and X
	USB_HID_KEY_Y = 0x1c,                   // Keyboard y and Y
	USB_HID_KEY_Z = 0x1d,                   // Keyboard z and Z

	USB_HID_KEY_1 = 0x1e,                   // Keyboard 1 and !
	USB_HID_KEY_2 = 0x1f,                   // Keyboard 2 and @
	USB_HID_KEY_3 = 0x20,                   // Keyboard 3 and #
	USB_HID_KEY_4 = 0x21,                   // Keyboard 4 and $
	USB_HID_KEY_5 = 0x22,                   // Keyboard 5 and %
	USB_HID_KEY_6 = 0x23,                   // Keyboard 6 and ^
	USB_HID_KEY_7 = 0x24,                   // Keyboard 7 and &
	USB_HID_KEY_8 = 0x25,                   // Keyboard 8 and *
	USB_HID_KEY_9 = 0x26,                   // Keyboard 9 and (
	USB_HID_KEY_0 = 0x27,                   // Keyboard 0 and )

	USB_HID_KEY_ENTER      = 0x28,          // Keyboard Return (ENTER)
	USB_HID_KEY_ESC        = 0x29,          // Keyboard ESCAPE
	USB_HID_KEY_BACKSPACE  = 0x2a,          // Keyboard DELETE (Backspace)
	USB_HID_KEY_TAB        = 0x2b,          // Keyboard Tab
	USB_HID_KEY_SPACE      = 0x2c,          // Keyboard Spacebar
	USB_HID_KEY_MINUS      = 0x2d,          // Keyboard - and _
	USB_HID_KEY_EQUAL      = 0x2e,          // Keyboard = and +
	USB_HID_KEY_LEFTBRACE  = 0x2f,          // Keyboard [ and {
	USB_HID_KEY_RIGHTBRACE = 0x30,          // Keyboard ] and }
	USB_HID_KEY_BACKSLASH  = 0x31,          // Keyboard \ and |
	USB_HID_KEY_HASHTILDE  = 0x32,          // Keyboard Non-US # and ~
	USB_HID_KEY_SEMICOLON  = 0x33,          // Keyboard ; and :
	USB_HID_KEY_APOSTROPHE = 0x34,          // Keyboard ' and "
	USB_HID_KEY_GRAVE      = 0x35,          // Keyboard ` and ~
	USB_HID_KEY_COMMA      = 0x36,          // Keyboard , and <
	USB_HID_KEY_DOT        = 0x37,          // Keyboard . and >
	USB_HID_KEY_SLASH      = 0x38,          // Keyboard / and ?
	USB_HID_KEY_CAPSLOCK   = 0x39,          // Keyboard Caps Lock

	USB_HID_KEY_F1  = 0x3a,                 // Keyboard F1
	USB_HID_KEY_F2  = 0x3b,                 // Keyboard F2
	USB_HID_KEY_F3  = 0x3c,                 // Keyboard F3
	USB_HID_KEY_F4  = 0x3d,                 // Keyboard F4
	USB_HID_KEY_F5  = 0x3e,                 // Keyboard F5
	USB_HID_KEY_F6  = 0x3f,                 // Keyboard F6
	USB_HID_KEY_F7  = 0x40,                 // Keyboard F7
	USB_HID_KEY_F8  = 0x41,                 // Keyboard F8
	USB_HID_KEY_F9  = 0x42,                 // Keyboard F9
	USB_HID_KEY_F10 = 0x43,                 // Keyboard F10
	USB_HID_KEY_F11 = 0x44,                 // Keyboard F11
	USB_HID_KEY_F12 = 0x45,                 // Keyboard F12

	USB_HID_KEY_SYSRQ      = 0x46,          // Keyboard Print Screen
	USB_HID_KEY_SCROLLLOCK = 0x47,          // Keyboard Scroll Lock
	USB_HID_KEY_PAUSE      = 0x48,          // Keyboard Pause
	USB_HID_KEY_INSERT     = 0x49,          // Keyboard Insert
	USB_HID_KEY_HOME       = 0x4a,          // Keyboard Home
	USB_HID_KEY_PAGEUP     = 0x4b,          // Keyboard Page Up
	USB_HID_KEY_DELETE     = 0x4c,          // Keyboard Delete Forward
	USB_HID_KEY_END        = 0x4d,          // Keyboard End
	USB_HID_KEY_PAGEDOWN   = 0x4e,          // Keyboard Page Down
	USB_HID_KEY_RIGHT      = 0x4f,          // Keyboard Right Arrow
	USB_HID_KEY_LEFT       = 0x50,          // Keyboard Left Arrow
	USB_HID_KEY_DOWN       = 0x51,          // Keyboard Down Arrow
	USB_HID_KEY_UP         = 0x52,          // Keyboard Up Arrow

	USB_HID_KEY_NUMLOCK    = 0x53,          // Keyboard Num Lock and Clear
	USB_HID_KEY_KPSLASH    = 0x54,          // Keypad /
	USB_HID_KEY_KPASTERISK = 0x55,          // Keypad *
	USB_HID_KEY_KPMINUS    = 0x56,          // Keypad -
	USB_HID_KEY_KPPLUS     = 0x57,          // Keypad +
	USB_HID_KEY_KPENTER    = 0x58,          // Keypad ENTER
	USB_HID_KEY_KP1        = 0x59,          // Keypad 1 and End
	USB_HID_KEY_KP2        = 0x5a,          // Keypad 2 and Down Arrow
	USB_HID_KEY_KP3        = 0x5b,          // Keypad 3 and PageDn
	USB_HID_KEY_KP4        = 0x5c,          // Keypad 4 and Left Arrow
	USB_HID_KEY_KP5        = 0x5d,          // Keypad 5
	USB_HID_KEY_KP6        = 0x5e,          // Keypad 6 and Right Arrow
	USB_HID_KEY_KP7        = 0x5f,          // Keypad 7 and Home
	USB_HID_KEY_KP8        = 0x60,          // Keypad 8 and Up Arrow
	USB_HID_KEY_KP9        = 0x61,          // Keypad 9 and Page Up
	USB_HID_KEY_KP0        = 0x62,          // Keypad 0 and Insert
	USB_HID_KEY_KPDOT      = 0x63,          // Keypad . and Delete

	USB_HID_KEY_102ND   = 0x64,             // Keyboard Non-US \ and |
	USB_HID_KEY_COMPOSE = 0x65,             // Keyboard Application
	USB_HID_KEY_POWER   = 0x66,             // Keyboard Power
	USB_HID_KEY_KPEQUAL = 0x67,             // Keypad =

	USB_HID_KEY_F13 = 0x68,                 // Keyboard F13
	USB_HID_KEY_F14 = 0x69,                 // Keyboard F14
	USB_HID_KEY_F15 = 0x6a,                 // Keyboard F15
	USB_HID_KEY_F16 = 0x6b,                 // Keyboard F16
	USB_HID_KEY_F17 = 0x6c,                 // Keyboard F17
	USB_HID_KEY_F18 = 0x6d,                 // Keyboard F18
	USB_HID_KEY_F19 = 0x6e,                 // Keyboard F19
	USB_HID_KEY_F20 = 0x6f,                 // Keyboard F20
	USB_HID_KEY_F21 = 0x70,                 // Keyboard F21
	USB_HID_KEY_F22 = 0x71,                 // Keyboard F22
	USB_HID_KEY_F23 = 0x72,                 // Keyboard F23
	USB_HID_KEY_F24 = 0x73,                 // Keyboard F24

	USB_HID_KEY_OPEN       = 0x74,          // Keyboard Execute
	USB_HID_KEY_HELP       = 0x75,          // Keyboard Help
	USB_HID_KEY_PROPS      = 0x76,          // Keyboard Menu
	USB_HID_KEY_FRONT      = 0x77,          // Keyboard Select
	USB_HID_KEY_STOP       = 0x78,          // Keyboard Stop
	USB_HID_KEY_AGAIN      = 0x79,          // Keyboard Again
	USB_HID_KEY_UNDO       = 0x7a,          // Keyboard Undo
	USB_HID_KEY_CUT        = 0x7b,          // Keyboard Cut
	USB_HID_KEY_COPY       = 0x7c,          // Keyboard Copy
	USB_HID_KEY_PASTE      = 0x7d,          // Keyboard Paste
	USB_HID_KEY_FIND       = 0x7e,          // Keyboard Find
	USB_HID_KEY_MUTE       = 0x7f,          // Keyboard Mute
	USB_HID_KEY_VOLUMEUP   = 0x80,          // Keyboard Volume Up
	USB_HID_KEY_VOLUMEDOWN = 0x81,          // Keyboard Volume Down

	USB_HID_KEY_LOCKING_CAPS       = 0x82,  // Keyboard Locking Caps Lock
	USB_HID_KEY_LOCKING_NUMLOCK    = 0x83,  // Keyboard Locking Num Lock
	USB_HID_KEY_LOCKING_SCROLLLOCK = 0x84,  // Keyboard Locking Scroll Lock

	USB_HID_KEY_KPCOMMA       = 0x85,       // Keypad Comma
	USB_HID_KEY_KPEQUAL_AS400 = 0x86,       // Keypad Equal Sign

	USB_HID_KEY_INTL1 = 0x87,               // Keyboard International1
	USB_HID_KEY_INTL2 = 0x88,               // Keyboard International2
	USB_HID_KEY_INTL3 = 0x89,               // Keyboard International3
	USB_HID_KEY_INTL4 = 0x8a,               // Keyboard International4
	USB_HID_KEY_INTL5 = 0x8b,               // Keyboard International5
	USB_HID_KEY_INTL6 = 0x8c,               // Keyboard International6
	USB_HID_KEY_INTL7 = 0x8d,               // Keyboard International7
	USB_HID_KEY_INTL8 = 0x8e,               // Keyboard International8
	USB_HID_KEY_INTL9 = 0x8f,               // Keyboard International9

	USB_HID_KEY_LANG1 = 0x90,               // Keyboard LANG1
	USB_HID_KEY_LANG2 = 0x91,               // Keyboard LANG2
	USB_HID_KEY_LANG3 = 0x92,               // Keyboard LANG3
	USB_HID_KEY_LANG4 = 0x93,               // Keyboard LANG4
	USB_HID_KEY_LANG5 = 0x94,               // Keyboard LANG5
	USB_HID_KEY_LANG6 = 0x95,               // Keyboard LANG6
	USB_HID_KEY_LANG7 = 0x96,               // Keyboard LANG7
	USB_HID_KEY_LANG8 = 0x97,               // Keyboard LANG8
	USB_HID_KEY_LANG9 = 0x98,               // Keyboard LANG9

	USB_HID_KEY_ALT_ERASE   = 0x99,         // Keyboard Alternate Erase
	USB_HID_KEY_SYSRQ_ATTN  = 0x9a,         // Keyboard SysReq/Attention
	USB_HID_KEY_CANCEL      = 0x9b,         // Keyboard Cancel
	USB_HID_KEY_CLEAR       = 0x9c,         // Keyboard Clear
	USB_HID_KEY_PRIOR       = 0x9d,         // Keyboard Prior
	USB_HID_KEY_RETURN      = 0x9e,         // Keyboard Return
	USB_HID_KEY_SEPARATOR   = 0x9f,         // Keyboard Separator
	USB_HID_KEY_OUT         = 0xa0,         // Keyboard Out
	USB_HID_KEY_OPER        = 0xa1,         // Keyboard Oper
	USB_HID_KEY_CLEAR_AGAIN = 0xa2,         // Keyboard Clear/Again
	USB_HID_KEY_CRSEL_PROPS = 0xa3,         // Keyboard CrSel/Props
	USB_HID_KEY_EXSEL       = 0xa4,         // Keyboard ExSel

	USB_HID_KEY_RESERVED_A5 = 0xa5,         // Reserved scancodes
	USB_HID_KEY_RESERVED_A6 = 0xa6,
	USB_HID_KEY_RESERVED_A7 = 0xa7,
	USB_HID_KEY_RESERVED_A8 = 0xa8,
	USB_HID_KEY_RESERVED_A9 = 0xa9,
	USB_HID_KEY_RESERVED_AA = 0xaa,
	USB_HID_KEY_RESERVED_AB = 0xab,
	USB_HID_KEY_RESERVED_AC = 0xac,
	USB_HID_KEY_RESERVED_AD = 0xad,
	USB_HID_KEY_RESERVED_AE = 0xae,
	USB_HID_KEY_RESERVED_AF = 0xaf,

	USB_HID_KEY_KP00          = 0xb0,       // Keypad 00
	USB_HID_KEY_KP000         = 0xb1,       // Keypad 000
	USB_HID_KEY_THOUSEP       = 0xb2,       // Thousands Separator
	USB_HID_KEY_DECSEP        = 0xb3,       // Decimal Separator
	USB_HID_KEY_CURRENCY_UNIT = 0xb4,       // Currency Unit
	USB_HID_KEY_CURRENCY_SUB  = 0xb5,       // Currency Sub-unit

	USB_HID_KEY_KPLEFTPAREN  = 0xb6,        // Keypad (
	USB_HID_KEY_KPRIGHTPAREN = 0xb7,        // Keypad )
	USB_HID_KEY_KPLEFTBRACE  = 0xb8,        // Keypad {
	USB_HID_KEY_KPRIGHTBRACE = 0xb9,        // Keypad }
	USB_HID_KEY_KPTAB        = 0xba,        // Keypad Tab
	USB_HID_KEY_KPBACKSPACE  = 0xbb,        // Keypad Backspace
	USB_HID_KEY_KPA          = 0xbc,        // Keypad A
	USB_HID_KEY_KPB          = 0xbd,        // Keypad B
	USB_HID_KEY_KPC          = 0xbe,        // Keypad C
	USB_HID_KEY_KPD          = 0xbf,        // Keypad D
	USB_HID_KEY_KPE          = 0xc0,        // Keypad E
	USB_HID_KEY_KPF          = 0xc1,        // Keypad F
	USB_HID_KEY_KPXOR        = 0xc2,        // Keypad XOR
	USB_HID_KEY_KPCARET      = 0xc3,        // Keypad ^
	USB_HID_KEY_KPPERCENT    = 0xc4,        // Keypad %
	USB_HID_KEY_KPLESS       = 0xc5,        // Keypad <
	USB_HID_KEY_KPGREATER    = 0xc6,        // Keypad >
	USB_HID_KEY_KPAMP        = 0xc7,        // Keypad &
	USB_HID_KEY_KPAND        = 0xc8,        // Keypad &&
	USB_HID_KEY_KPVBAR       = 0xc9,        // Keypad |
	USB_HID_KEY_KPOR         = 0xca,        // Keypad ||
	USB_HID_KEY_KPCOLON      = 0xcb,        // Keypad :
	USB_HID_KEY_KPHASH       = 0xcc,        // Keypad #
	USB_HID_KEY_KPSPACE      = 0xcd,        // Keypad Space
	USB_HID_KEY_KPAT         = 0xce,        // Keypad @
	USB_HID_KEY_KPEXCL       = 0xcf,        // Keypad !
	USB_HID_KEY_KPMEMSTORE   = 0xd0,        // Keypad Memory Store
	USB_HID_KEY_KPMEMRECALL  = 0xd1,        // Keypad Memory Recall
	USB_HID_KEY_KPMEMCLEAR   = 0xd2,        // Keypad Memory Clear
	USB_HID_KEY_KPMEMADD     = 0xd3,        // Keypad Memory Add
	USB_HID_KEY_KPMEMSUB     = 0xd4,        // Keypad Memory Subtract
	USB_HID_KEY_KPMEMMUL     = 0xd5,        // Keypad Memory Multiply
	USB_HID_KEY_KPMEMDIV     = 0xd6,        // Keypad Memory Divide
	USB_HID_KEY_KPSIGN       = 0xd7,        // Keypad +/-
	USB_HID_KEY_KPCLEAR      = 0xd8,        // Keypad Clear
	USB_HID_KEY_KPCLEARENT   = 0xd9,        // Keypad Clear Entry
	USB_HID_KEY_KPBIN        = 0xda,        // Keypad Binary
	USB_HID_KEY_KPOCT        = 0xdb,        // Keypad Octal
	USB_HID_KEY_KPDEC        = 0xdc,        // Keypad Decimal
	USB_HID_KEY_KPHEX        = 0xdd,        // Keypad Hexadecimal

	USB_HID_KEY_LEFTCTRL   = 0xe0,          // Keyboard Left Control
	USB_HID_KEY_LEFTSHIFT  = 0xe1,          // Keyboard Left Shift
	USB_HID_KEY_LEFTALT    = 0xe2,          // Keyboard Left Alt
	USB_HID_KEY_LEFTMETA   = 0xe3,          // Keyboard Left GUI
	USB_HID_KEY_RIGHTCTRL  = 0xe4,          // Keyboard Right Control
	USB_HID_KEY_RIGHTSHIFT = 0xe5,          // Keyboard Right Shift
	USB_HID_KEY_RIGHTALT   = 0xe6,          // Keyboard Right Alt
	USB_HID_KEY_RIGHTGUI   = 0xe7           // Keyboard Right GUI

};


#define USB_HID_INTERFACE_REPORT(report_length) \
	, USB_DESCRIPTOR_HID_REPORT, BYTE(report_length, 0), BYTE(report_length, 1)

#define USB_HID_INTERFACE(country, report_lengths...)       \
	6 + 3 * PP_NARG(report_lengths),                    \
	USB_DESCRIPTOR_HID,                                 \
	BYTE(USB_HID_VERSION, 0), BYTE(USB_HID_VERSION, 1), \
	(country),                                          \
	PP_NARG(report_lengths)                             \
	PP_FOREACH(USB_HID_INTERFACE_REPORT, report_lengths)


#define USB_HID(id, country, report_lengths...)             \
	USB_DESCRIPTOR_BEGIN(byte, USB_DESCRIPTOR_HID, id)  \
		USB_HID_INTERFACE(country, report_lengths)  \
	USB_DESCRIPTOR_END


#define USB_HID_REPORT(id, report...)                              \
	USB_DESCRIPTOR_BEGIN(byte, USB_DESCRIPTOR_HID_REPORT, id)  \
		report                                             \
	USB_DESCRIPTOR_END


/**
 * Usage Pages
 **/
#define USB_HID_USAGE_PAGE_GENERIC_DESKTOP  0x05, 0x01,
#define USB_HID_USAGE_PAGE_KEYBOARD         0x05, 0x07,
#define USB_HID_USAGE_PAGE_LEDS             0x05, 0x08,
#define USB_HID_USAGE_PAGE_BUTTON           0x05, 0x09,

/**
 * Usages for Generic Desktop
 **/
#define USB_HID_USAGE_UNDEFINED            0x09, 0x00,
#define USB_HID_USAGE_POINTER              0x09, 0x01,
#define USB_HID_USAGE_MOUSE                0x09, 0x02,
#define USB_HID_USAGE_RESERVED             0x09, 0x03,
#define USB_HID_USAGE_JOYSTICK             0x09, 0x04,
#define USB_HID_USAGE_GAMEPAD              0x09, 0x05,
#define USB_HID_USAGE_KEYBOARD             0x09, 0x06,
#define USB_HID_USAGE_KEYPAD               0x09, 0x07,
#define USB_HID_USAGE_MULTIAXIS            0x09, 0x08,
#define USB_HID_USAGE_X                    0x09, 0x30,
#define USB_HID_USAGE_Y                    0x09, 0x31,
#define USB_HID_USAGE_Z                    0x09, 0x32,
#define USB_HID_USAGE_RX                   0x09, 0x33,
#define USB_HID_USAGE_RY                   0x09, 0x34,
#define USB_HID_USAGE_RZ                   0x09, 0x35,
#define USB_HID_USAGE_SLIDER               0x09, 0x36,
#define USB_HID_USAGE_DIAL                 0x09, 0x37,
#define USB_HID_USAGE_WHEEL                0x09, 0x38,
#define USB_HID_USAGE_HAT_SWITCH           0x09, 0x39,
#define USB_HID_USAGE_COUNTED_BUFFER       0x09, 0x3A,
#define USB_HID_USAGE_BYTE_COUNT           0x09, 0x3B,
#define USB_HID_USAGE_MOTION_WAKEUP        0x09, 0x3C,
#define USB_HID_USAGE_VX                   0x09, 0x40,
#define USB_HID_USAGE_VY                   0x09, 0x41,
#define USB_HID_USAGE_VZ                   0x09, 0x42,
#define USB_HID_USAGE_VBRX                 0x09, 0x43,
#define USB_HID_USAGE_VBRY                 0x09, 0x44,
#define USB_HID_USAGE_VBRZ                 0x09, 0x45,
#define USB_HID_USAGE_VNO                  0x09, 0x46,
#define USB_HID_USAGE_SYSTEM_CONTROL       0x09, 0x80,
#define USB_HID_USAGE_SYSTEM_POWERDOWN     0x09, 0x81,
#define USB_HID_USAGE_SYSTEM_SLEEP         0x09, 0x82,
#define USB_HID_USAGE_SYSTEM_WAKEUP        0x09, 0x83,
#define USB_HID_USAGE_SYSTEM_CONTEXT_MENU  0x09, 0x84,
#define USB_HID_USAGE_SYSTEM_MAIN_MENU     0x09, 0x85,
#define USB_HID_USAGE_SYSTEM_APP_MENU      0x09, 0x86,
#define USB_HID_USAGE_SYSTEM_MENU_HELP     0x09, 0x87,
#define USB_HID_USAGE_SYSTEM_MENU_EXIT     0x09, 0x88,
#define USB_HID_USAGE_SYSTEM_MENU_SELECT   0x09, 0x89,
#define USB_HID_USAGE_SYSTEM_MENU_RIGHT    0x09, 0x8A,
#define USB_HID_USAGE_SYSTEM_MENU_LEFT     0x09, 0x8B,
#define USB_HID_USAGE_SYSTEM_MENU_UP       0x09, 0x8C,
#define USB_HID_USAGE_SYSTEM_MENU_DOWN     0x09, 0x8D,
#define USB_HID_USAGE_DPAD_UP              0x09, 0x90,
#define USB_HID_USAGE_DPAD_DOWN            0x09, 0x91,
#define USB_HID_USAGE_DPAD_RIGHT           0x09, 0x92,
#define USB_HID_USAGE_DPAD_LEFT            0x09, 0x93,

/**
 * Collections
 **/
#define USB_HID_COLLECTION_PHYSICAL        0xa1, 0x00,
#define USB_HID_COLLECTION_APPLICATION     0xa1, 0x01,
#define USB_HID_COLLECTION_LOGICAL         0xa1, 0x02,
#define USB_HID_COLLECTION_REPORT          0xa1, 0x03,
#define USB_HID_COLLECTION_NAMED_ARRAY     0xa1, 0x04,
#define USB_HID_COLLECTION_USAGE_SWITCH    0xa1, 0x05,
#define USB_HID_COLLECTION_USAGE_MODIFIER  0xa1, 0x06,
#define USB_HID_COLLECTION_END             0xc0,


#define USB_HID_USAGE_MIN8(x)   0x19, BYTE(x, 0),
#define USB_HID_USAGE_MIN16(x)  0x1a, BYTE(x, 0), BYTE(x, 1),

#define USB_HID_USAGE_MAX8(x)   0x29, BYTE(x, 0),
#define USB_HID_USAGE_MAX16(x)  0x2a, BYTE(x, 0), BYTE(x, 1),

#define USB_HID_LOGICAL_MIN8(x)   0x15, BYTE(x, 0),
#define USB_HID_LOGICAL_MIN16(x)  0x16, BYTE(x, 0), BYTE(x, 1),
#define USB_HID_LOGICAL_MIN32(x)  0x17, BYTE(x, 0), BYTE(x, 1), BYTE(x, 2), BYTE(x, 3),

#define USB_HID_LOGICAL_MAX8(x)   0x25, BYTE(x, 0),
#define USB_HID_LOGICAL_MAX16(x)  0x26, BYTE(x, 0), BYTE(x, 1),
#define USB_HID_LOGICAL_MAX32(x)  0x27, BYTE(x, 0), BYTE(x, 1), BYTE(x, 2), BYTE(x, 3),

#define USB_HID_REPORT_ID8(x)   0x85, BYTE(x, 0),
#define USB_HID_REPORT_ID16(x)  0x86, BYTE(x, 0), BYTE(x, 1),
#define USB_HID_REPORT_ID32(x)  0x87, BYTE(x, 0), BYTE(x, 1), BYTE(x, 2), BYTE(x, 3),

#define USB_HID_REPORT_SIZE8(x)   0x75, BYTE(x, 0),
#define USB_HID_REPORT_SIZE16(x)  0x76, BYTE(x, 0), BYTE(x, 1),
#define USB_HID_REPORT_SIZE32(x)  0x77, BYTE(x, 0), BYTE(x, 1), BYTE(x, 2), BYTE(x, 3),

#define USB_HID_REPORT_COUNT8(x)   0x95, BYTE(x, 0),
#define USB_HID_REPORT_COUNT16(x)  0x96, BYTE(x, 0), BYTE(x, 1),
#define USB_HID_REPORT_COUNT32(x)  0x97, BYTE(x, 0), BYTE(x, 1), BYTE(x, 2), BYTE(x, 3),

#define USB_HID_UNIT_EXPONENT8(x)  0x55, BYTE(x, 0),


enum {

	USB_HID_INPUT_DATA              = 0 << 0,    // Bit 0 {Data (0) | Constant (1)}
	USB_HID_INPUT_CONST             = 1 << 0,
	USB_HID_INPUT_ARRAY             = 0 << 1,    // Bit 1 {Array (0) | Variable (1)}
	USB_HID_INPUT_VARIABLE          = 1 << 1,
	USB_HID_INPUT_ABSOLUTE          = 0 << 2,    // Bit 2 {Absolute (0) | Relative (1)}
	USB_HID_INPUT_RELATIVE          = 1 << 2,
	USB_HID_INPUT_NO_WRAP           = 0 << 3,    // Bit 3 {No Wrap (0) | Wrap (1)}
	USB_HID_INPUT_WRAP              = 1 << 3,
	USB_HID_INPUT_LINEAR            = 0 << 4,    // Bit 4 {Linear (0) | Non Linear (1)}
	USB_HID_INPUT_NONLINEAR         = 1 << 4,
	USB_HID_INPUT_PREFERRED_STATE   = 0 << 5,    // Bit 5 {Preferred State (0) | No Preferred (1)}
	USB_HID_INPUT_NO_PREFERED_STATE = 1 << 5,
	USB_HID_INPUT_NO_NULL_POSITION  = 0 << 6,    // Bit 6 {No Null position (0) | Null state(1)}
	USB_HID_INPUT_NULL_STATE        = 1 << 6,
	USB_HID_INPUT_BIT_FIELD         = 0 << 8,    // Bit 8 {Bit Field (0) | Buffered Bytes (1)}
	USB_HID_INPUT_BUFFERED_BYTES    = 1 << 8

};

#define USB_HID_INPUT8(x)   0x81, BYTE(x, 0),
#define USB_HID_INPUT16(x)  0x82, BYTE(x, 0), BYTE(x, 1),
#define USB_HID_INPUT32(x)  0x83, BYTE(x, 0), BYTE(x, 1), BYTE(x, 2), BYTE(x, 3),


enum {

	USB_HID_OUTPUT_DATA              = 0 << 0,    // Bit 0 {Data (0) | Constant (1)}
	USB_HID_OUTPUT_CONST             = 1 << 0,
	USB_HID_OUTPUT_ARRAY             = 0 << 1,    // Bit 1 {Array (0) | Variable (1)}
	USB_HID_OUTPUT_VARIABLE          = 1 << 1,
	USB_HID_OUTPUT_ABSOLUTE          = 0 << 2,    // Bit 2 {Absolute (0) | Relative (1)}
	USB_HID_OUTPUT_RELATIVE          = 1 << 2,
	USB_HID_OUTPUT_NO_WRAP           = 0 << 3,    // Bit 3 {No Wrap (0) | Wrap (1)}
	USB_HID_OUTPUT_WRAP              = 1 << 3,
	USB_HID_OUTPUT_LINEAR            = 0 << 4,    // Bit 4 {Linear (0) | Non Linear (1)}
	USB_HID_OUTPUT_NONLINEAR         = 1 << 4,
	USB_HID_OUTPUT_PREFERRED_STATE   = 0 << 5,    // Bit 5 {Preferred State (0) | No Preferred (1)}
	USB_HID_OUTPUT_NO_PREFERED_STATE = 1 << 5,
	USB_HID_OUTPUT_NO_NULL_POSITION  = 0 << 6,    // Bit 6 {No Null position (0) | Null state(1)}
	USB_HID_OUTPUT_NULL_STATE        = 1 << 6,
	USB_HID_OUTPUT_NON_VOLATILE      = 0 << 7,    // Bit 7 {Non Volatile (0) | Volatile (1)}
	USB_HID_OUTPUT_VOLATILE          = 1 << 7,
	USB_HID_OUTPUT_BIT_FIELD         = 0 << 8,    // Bit 8 {Bit Field (0) | Buffered Bytes (1)}
	USB_HID_OUTPUT_BUFFERED_BYTES    = 1 << 8

};

#define USB_HID_OUTPUT8(x)   0x91, BYTE(x, 0),
#define USB_HID_OUTPUT16(x)  0x92, BYTE(x, 0), BYTE(x, 1),
#define USB_HID_OUTPUT32(x)  0x93, BYTE(x, 0), BYTE(x, 1), BYTE(x, 2), BYTE(x, 3),


enum {

	USB_HID_FEATURE_DATA              = 0 << 0,    // Bit 0 {Data (0) | Constant (1)}
	USB_HID_FEATURE_CONST             = 1 << 0,
	USB_HID_FEATURE_ARRAY             = 0 << 1,    // Bit 1 {Array (0) | Variable (1)}
	USB_HID_FEATURE_VARIABLE          = 1 << 1,
	USB_HID_FEATURE_ABSOLUTE          = 0 << 2,    // Bit 2 {Absolute (0) | Relative (1)}
	USB_HID_FEATURE_RELATIVE          = 1 << 2,
	USB_HID_FEATURE_NO_WRAP           = 0 << 3,    // Bit 3 {No Wrap (0) | Wrap (1)}
	USB_HID_FEATURE_WRAP              = 1 << 3,
	USB_HID_FEATURE_LINEAR            = 0 << 4,    // Bit 4 {Linear (0) | Non Linear (1)}
	USB_HID_FEATURE_NONLINEAR         = 1 << 4,
	USB_HID_FEATURE_PREFERRED_STATE   = 0 << 5,    // Bit 5 {Preferred State (0) | No Preferred (1)}
	USB_HID_FEATURE_NO_PREFERED_STATE = 1 << 5,
	USB_HID_FEATURE_NO_NULL_POSITION  = 0 << 6,    // Bit 6 {No Null position (0) | Null state(1)}
	USB_HID_FEATURE_NULL_STATE        = 1 << 6,
	USB_HID_FEATURE_NON_VOLATILE      = 0 << 7,    // Bit 7 {Non Volatile (0) | Volatile (1)}
	USB_HID_FEATURE_VOLATILE          = 1 << 7,
	USB_HID_FEATURE_BIT_FIELD         = 0 << 8,    // Bit 8 {Bit Field (0) | Buffered Bytes (1)}
	USB_HID_FEATURE_BUFFERED_BYTES    = 1 << 8

};

#define USB_HID_FEATURE8(x)   0xb1, BYTE(x, 0),
#define USB_HID_FEATURE16(x)  0xb2, BYTE(x, 0), BYTE(x, 1),
#define USB_HID_FEATURE32(x)  0xb3, BYTE(x, 0), BYTE(x, 1), BYTE(x, 2), BYTE(x, 3),


#endif

