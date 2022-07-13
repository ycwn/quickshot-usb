

#ifndef USB_CDC_H
#define USB_CDC_H


enum {

	USB_DESCRIPTOR_CDC_CS_INTERFACE = 0x24,
	USB_DESCRIPTOR_CDC_CS_ENDPOINT  = 0x25,

	USB_DESCRIPTOR_CDC_FUNC_HEADER                           = 0x00,
	USB_DESCRIPTOR_CDC_FUNC_CALL_MGMT                        = 0x01,
	USB_DESCRIPTOR_CDC_FUNC_ABSTRACT_CONTROL_MGMT            = 0x02,
	USB_DESCRIPTOR_CDC_FUNC_DIRECT_LINE_MGMT                 = 0x03,
	USB_DESCRIPTOR_CDC_FUNC_TELEPHOBE_RINGER                 = 0x04,
	USB_DESCRIPTOR_CDC_FUNC_TELEPHOBE_CALL_LINE_STATE_REPORT = 0x05,
	USB_DESCRIPTOR_CDC_FUNC_UNION                            = 0x06,
	USB_DESCRIPTOR_CDC_FUNC_COUNTRY_SELECT                   = 0x07,
	USB_DESCRIPTOR_CDC_FUNC_TELEPHONE_OPMODES                = 0x08,
	USB_DESCRIPTOR_CDC_FUNC_USB_TERMINAL                     = 0x09,
	USB_DESCRIPTOR_CDC_FUNC_NETWORK_CHANNEL_TERMINAL         = 0x0a,
	USB_DESCRIPTOR_CDC_FUNC_PROTOCOL_UNIT                    = 0x0b,
	USB_DESCRIPTOR_CDC_FUNC_EXTENSION_UNIT                   = 0x0c,
	USB_DESCRIPTOR_CDC_FUNC_MULTICHANNEL_MGMT                = 0x0d,
	USB_DESCRIPTOR_CDC_FUNC_CAPI_CONTROL_MGMT                = 0x0e,
	USB_DESCRIPTOR_CDC_FUNC_ETHERNET_NETWORKING              = 0x0f,
	USB_DESCRIPTOR_CDC_FUNC_ATM_NETWORKING                   = 0x10,
	USB_DESCRIPTOR_CDC_FUNC_WIRELESS_HANDSET_CONTROL_MODEL   = 0x11,
	USB_DESCRIPTOR_CDC_FUNC_MOBILE_DIRECT_LINE_MODEL         = 0x12,
	USB_DESCRIPTOR_CDC_FUNC_MDLM_DETAIL                      = 0x13,
	USB_DESCRIPTOR_CDC_FUNC_DEVICE_MGMT_MODEL                = 0x14,
	USB_DESCRIPTOR_CDC_FUNC_OBEX                             = 0x15,
	USB_DESCRIPTOR_CDC_FUNC_COMMAND_SET                      = 0x16,
	USB_DESCRIPTOR_CDC_FUNC_COMMAND_SET_DETAIL               = 0x17,
	USB_DESCRIPTOR_CDC_FUNC_TELEPHONE_CONTROL_MODEL          = 0x18,
	USB_DESCRIPTOR_CDC_FUNC_OBEX_SERVICE_ID                  = 0x19,
	USB_DESCRIPTOR_CDC_FUNC_NCM                              = 0x1a,

	USB_DESCRIPTOR_CDC_DATA_FUNC_HEADER = 0x00

};


enum {

	USB_CLASS_CDC      = 0x02,
	USB_CLASS_CDC_DATA = 0x0a

};


enum {

	USB_SUBCLASS_CDC_DIRECT_LINE_CONTROL        = 0x01,
	USB_SUBCLASS_CDC_ABSTRACT_CONTROL           = 0x02,
	USB_SUBCLASS_CDC_TELEPHONE_CONTROL          = 0x03,
	USB_SUBCLASS_CDC_MULTICHANNEL_CONTROL       = 0x04,
	USB_SUBCLASS_CDC_CAPI_CONTROL               = 0x05,
	USB_SUBCLASS_CDC_ETHERNET_CONTROL           = 0x06,
	USB_SUBCLASS_CDC_ATM_NETWORK_CONTROL        = 0x07,
	USB_SUBCLASS_CDC_WIRELESS_HANDSET_CONTROL   = 0x08,
	USB_SUBCLASS_CDC_DEVICE_MANAGEMENT          = 0x09,
	USB_SUBCLASS_CDC_MOBILE_DIRECT_LINE_CONTROL = 0x0a,
	USB_SUBCLASS_CDC_OBEX                       = 0x0b,
	USB_SUBCLASS_CDC_ETHERNET_EMULATION_CONTROL = 0x0c,

	USB_CLASS_CDC_DATA_DEFAULT = 0x00

};


enum {

	USB_PROTOCOL_CDC_NONE            = 0x00,    // No class specific protocol required
	USB_PROTOCOL_CDC_ITU_T_V250      = 0x01,    // AT Commands: V.250
	USB_PROTOCOL_CDC_PCCA101         = 0x02,    // AT Commands defined by PCCA-101
	USB_PROTOCOL_CDC_PCCA101_ANNEX_O = 0x03,    // AT Commands defined by PCCA-101 & Annex O
	USB_PROTOCOL_CDC_GSM_0707        = 0x04,    // AT Commands defined by GSM 07.07
	USB_PROTOCOL_CDC_3GPP_27007      = 0x05,    // AT Commands defined by 3GPP 27.007
	USB_PROTOCOL_CDC_C_S0017_0       = 0x06,    // AT Commands defined by TIA for CDMA
	USB_PROTOCOL_CDC_USB_EEM         = 0x07,    // Ethernet Emulation Model

	USB_PROTOCOL_CDC_DATA_NONE            = 0x00,    // No class specific protocol required
	USB_PROTOCOL_CDC_DATA_USBNCM          = 0x01,    // Network Transfer Block
	USB_PROTOCOL_CDC_DATA_I430            = 0x30,    // Physical interface protocol for ISDN BRI
	USB_PROTOCOL_CDC_DATA_ISOIEC3309_1993 = 0x31,    // HDLC
	USB_PROTOCOL_CDC_DATA_TRANSPARENT     = 0x32,
	USB_PROTOCOL_CDC_DATA_Q921M           = 0x50,    // Management protocol for Q.921 data link protocol
	USB_PROTOCOL_CDC_DATA_Q921            = 0x51,    // Data link protocol for Q.931
	USB_PROTOCOL_CDC_DATA_Q921TM          = 0x52,    // TEI-multiplexor for Q.921 data link protocol
	USB_PROTOCOL_CDC_DATA_V42BIS          = 0x90,    // V.42bis data compression procedures
	USB_PROTOCOL_CDC_DATA_Q931_EURO_ISDN  = 0x91,    // Euro-ISDN protocol control
	USB_PROTOCOL_CDC_DATA_V120            = 0x92,    // V.24 rate adaptation to ISDN
	USB_PROTOCOL_CDC_DATA_CAPI20          = 0x93,    // CAPI Commands
	USB_PROTOCOL_CDC_DATA_HOST            = 0xfd,    // Host based driver
	USB_PROTOCOL_CDC_DATA_CDC             = 0xfe     // Protocol unit functional descriptors on CDC interface

};


enum {

	USB_CDC_VERSION     = 0x0120,
	USB_CDC_WMC_VERSION = 0x0100

};


enum {

	USB_REQUEST_TYPE_CDC_INTERFACE_IN  = USB_REQUEST_DIR_D2H | USB_REQUEST_TYPE_CLASS | USB_REQUEST_RCPT_INTERFACE,
	USB_REQUEST_TYPE_CDC_INTERFACE_OUT = USB_REQUEST_DIR_H2D | USB_REQUEST_TYPE_CLASS | USB_REQUEST_RCPT_INTERFACE

};


enum {

//
// USBCDC1.2 request codes
//
	USB_REQUEST_CODE_CDC_SEND_ENCAPSULATED_COMMAND = 0x00,
	USB_REQUEST_CODE_CDC_GET_ENCAPSULATED_RESPONSE = 0x01,

//
// USBPSTN1.2 request codes
//
	USB_REQUEST_CODE_CDC_SET_COMM_FEATURE   = 0x02,
	USB_REQUEST_CODE_CDC_GET_COMM_FEATURE   = 0x03,
	USB_REQUEST_CODE_CDC_CLEAR_COMM_FEATURE = 0x04,

	USB_REQUEST_CODE_CDC_SET_AUX_LINE_STATE = 0x10,
	USB_REQUEST_CODE_CDC_SET_HOOK_STATE     = 0x11,
	USB_REQUEST_CODE_CDC_PULSE_SETUP        = 0x12,
	USB_REQUEST_CODE_CDC_SEND_PULSE         = 0x13,
	USB_REQUEST_CODE_CDC_SET_PULSE_TIME     = 0x14,
	USB_REQUEST_CODE_CDC_RING_AUX_JACK      = 0x15,

	USB_REQUEST_CODE_CDC_SET_LINE_CODING        = 0x20,
	USB_REQUEST_CODE_CDC_GET_LINE_CODING        = 0x21,
	USB_REQUEST_CODE_CDC_SET_CONTROL_LINE_STATE = 0x22,
	USB_REQUEST_CODE_CDC_SEND_BREAK             = 0x23,

	USB_REQUEST_CODE_CDC_SET_RINGER_PARMS    = 0x30,
	USB_REQUEST_CODE_CDC_GET_RINGER_PARMS    = 0x31,
	USB_REQUEST_CODE_CDC_SET_OPERATION_PARMS = 0x32,
	USB_REQUEST_CODE_CDC_GET_OPERATION_PARMS = 0x33,

	USB_REQUEST_CODE_CDC_SET_LINE_PARMS = 0x34,
	USB_REQUEST_CODE_CDC_GET_LINE_PARMS = 0x35,

	USB_REQUEST_CODE_CDC_DIAL_DIGITS = 0x36,

//
// USBISDN1.2 request codes
//
	USB_REQUEST_CODE_CDC_SET_UNIT_PARAMETER   = 0x37,
	USB_REQUEST_CODE_CDC_GET_UNIT_PARAMETER   = 0x38,
	USB_REQUEST_CODE_CDC_CLEAR_UNIT_PARAMETER = 0x39,

	USB_REQUEST_CODE_CDC_GET_PROFILE = 0x3a,

//
// USBECM1.2 request codes
//
	USB_REQUEST_CODE_CDC_SET_ETHERNET_MULTICAST_FILTERS = 0x40,

	USB_REQUEST_CODE_CDC_SET_ETHERNET_POWER_MANAGEMENT_PATTERN_FILTER = 0x41,
	USB_REQUEST_CODE_CDC_GET_ETHERNET_POWER_MANAGEMENT_PATTERN_FILTER = 0x42,

	USB_REQUEST_CODE_CDC_SET_ETHERNET_PACKET_FILTER = 0x43,
	USB_REQUEST_CODE_CDC_GET_ETHERNET_STATISTIC     = 0x44,

//
// USBATM1.2 request codes
//
	USB_REQUEST_CODE_CDC_SET_ATM_DATA_FORMAT = 0x50,

	USB_REQUEST_CODE_CDC_GET_ATM_DEVICE_STATISTICS = 0x51,
	USB_REQUEST_CODE_CDC_SET_ATM_DEFAULT_VC        = 0x52,
	USB_REQUEST_CODE_CDC_GET_ATM_VC_STATISTICS     = 0x53,

//
// USBNCM1.0 request codes
//
	USB_REQUEST_CODE_CDC_GET_NTB_PARAMETERS    = 0x80,
	USB_REQUEST_CODE_CDC_GET_NET_ADDRESS       = 0x81,
	USB_REQUEST_CODE_CDC_SET_NET_ADDRESS       = 0x82,
	USB_REQUEST_CODE_CDC_GET_NTB_FORMAT        = 0x83,
	USB_REQUEST_CODE_CDC_SET_NTB_FORMAT        = 0x84,
	USB_REQUEST_CODE_CDC_GET_NTB_INPUT_SIZE    = 0x85,
	USB_REQUEST_CODE_CDC_SET_NTB_INPUT_SIZE    = 0x86,
	USB_REQUEST_CODE_CDC_GET_MAX_DATAGRAM_SIZE = 0x87,
	USB_REQUEST_CODE_CDC_SET_MAX_DATAGRAM_SIZE = 0x88,
	USB_REQUEST_CODE_CDC_GET_CRC_MODE          = 0x89,
	USB_REQUEST_CODE_CDC_SET_CRC_MODE          = 0x8a

};


enum {

//
// USBCDC1.2 notification codes
//
	USB_NOTIFICATION_CODE_CDC_NETWORK_CONNECTION      = 0x00,
	USB_NOTIFICATION_CODE_CDC_RESPONSE_AVAILABLE      = 0x01,
	USB_NOTIFICATION_CODE_CDC_CONNECTION_SPEED_CHANGE = 0x2a,

//
// USBPSTN1.2 notification codes
//
	USB_NOTIFICATION_CODE_AUX_JACK_HOOK_STATE = 0x08,
	USB_NOTIFICATION_CODE_RING_DETECT         = 0x09,

	USB_NOTIFICATION_CODE_SERIAL_STATE      = 0x20,
	USB_NOTIFICATION_CODE_CALL_STATE_CHANGE = 0x28,
	USB_NOTIFICATION_CODE_LINE_STATE_CHANGE = 0x29

};


enum {

//
// USBCDC1.2 requests
//
	USB_REQUEST_CDC_SEND_ENCAPSULATED_COMMAND = USB_MKRQID(USB_REQUEST_TYPE_CDC_INTERFACE_OUT, USB_REQUEST_CODE_CDC_SEND_ENCAPSULATED_COMMAND),
	USB_REQUEST_CDC_GET_ENCAPSULATED_RESPONSE = USB_MKRQID(USB_REQUEST_TYPE_CDC_INTERFACE_IN,  USB_REQUEST_CODE_CDC_GET_ENCAPSULATED_RESPONSE),

//
// USBPSTN1.2 request codes
//
	USB_REQUEST_CDC_SET_COMM_FEATURE   = USB_MKRQID(USB_REQUEST_TYPE_CDC_INTERFACE_OUT, USB_REQUEST_CODE_CDC_SET_COMM_FEATURE),
	USB_REQUEST_CDC_GET_COMM_FEATURE   = USB_MKRQID(USB_REQUEST_TYPE_CDC_INTERFACE_IN,  USB_REQUEST_CODE_CDC_GET_COMM_FEATURE),
	USB_REQUEST_CDC_CLEAR_COMM_FEATURE = USB_MKRQID(USB_REQUEST_TYPE_CDC_INTERFACE_OUT, USB_REQUEST_CODE_CDC_CLEAR_COMM_FEATURE),

	USB_REQUEST_CDC_SET_AUX_LINE_STATE = USB_MKRQID(USB_REQUEST_TYPE_CDC_INTERFACE_OUT, USB_REQUEST_CODE_CDC_SET_AUX_LINE_STATE),
	USB_REQUEST_CDC_SET_HOOK_STATE     = USB_MKRQID(USB_REQUEST_TYPE_CDC_INTERFACE_OUT, USB_REQUEST_CODE_CDC_SET_HOOK_STATE),
	USB_REQUEST_CDC_PULSE_SETUP        = USB_MKRQID(USB_REQUEST_TYPE_CDC_INTERFACE_OUT, USB_REQUEST_CODE_CDC_PULSE_SETUP),
	USB_REQUEST_CDC_SEND_PULSE         = USB_MKRQID(USB_REQUEST_TYPE_CDC_INTERFACE_OUT, USB_REQUEST_CODE_CDC_SEND_PULSE),
	USB_REQUEST_CDC_SET_PULSE_TIME     = USB_MKRQID(USB_REQUEST_TYPE_CDC_INTERFACE_OUT, USB_REQUEST_CODE_CDC_SET_PULSE_TIME),
	USB_REQUEST_CDC_RING_AUX_JACK      = USB_MKRQID(USB_REQUEST_TYPE_CDC_INTERFACE_OUT, USB_REQUEST_CODE_CDC_RING_AUX_JACK),

	USB_REQUEST_CDC_SET_LINE_CODING        = USB_MKRQID(USB_REQUEST_TYPE_CDC_INTERFACE_OUT, USB_REQUEST_CODE_CDC_SET_LINE_CODING),
	USB_REQUEST_CDC_GET_LINE_CODING        = USB_MKRQID(USB_REQUEST_TYPE_CDC_INTERFACE_IN,  USB_REQUEST_CODE_CDC_GET_LINE_CODING),
	USB_REQUEST_CDC_SET_CONTROL_LINE_STATE = USB_MKRQID(USB_REQUEST_TYPE_CDC_INTERFACE_OUT, USB_REQUEST_CODE_CDC_SET_CONTROL_LINE_STATE),
	USB_REQUEST_CDC_SEND_BREAK             = USB_MKRQID(USB_REQUEST_TYPE_CDC_INTERFACE_OUT, USB_REQUEST_CODE_CDC_SEND_BREAK),

	USB_REQUEST_CDC_SET_RINGER_PARMS    = USB_MKRQID(USB_REQUEST_TYPE_CDC_INTERFACE_OUT, USB_REQUEST_CODE_CDC_SET_RINGER_PARMS),
	USB_REQUEST_CDC_GET_RINGER_PARMS    = USB_MKRQID(USB_REQUEST_TYPE_CDC_INTERFACE_IN,  USB_REQUEST_CODE_CDC_GET_RINGER_PARMS),
	USB_REQUEST_CDC_SET_OPERATION_PARMS = USB_MKRQID(USB_REQUEST_TYPE_CDC_INTERFACE_OUT, USB_REQUEST_CODE_CDC_SET_OPERATION_PARMS),
	USB_REQUEST_CDC_GET_OPERATION_PARMS = USB_MKRQID(USB_REQUEST_TYPE_CDC_INTERFACE_IN,  USB_REQUEST_CODE_CDC_GET_OPERATION_PARMS),

	USB_REQUEST_CDC_SET_LINE_PARMS = USB_MKRQID(USB_REQUEST_TYPE_CDC_INTERFACE_OUT, USB_REQUEST_CODE_CDC_SET_LINE_PARMS),
	USB_REQUEST_CDC_GET_LINE_PARMS = USB_MKRQID(USB_REQUEST_TYPE_CDC_INTERFACE_IN,  USB_REQUEST_CODE_CDC_GET_LINE_PARMS),

	USB_REQUEST_CDC_DIAL_DIGITS = USB_MKRQID(USB_REQUEST_TYPE_CDC_INTERFACE_OUT, USB_REQUEST_CODE_CDC_DIAL_DIGITS),

//
// USBISDN1.2 requests
//
	USB_REQUEST_CDC_SET_UNIT_PARAMETER   = USB_MKRQID(USB_REQUEST_TYPE_CDC_INTERFACE_OUT, USB_REQUEST_CODE_CDC_SET_UNIT_PARAMETER),
	USB_REQUEST_CDC_GET_UNIT_PARAMETER   = USB_MKRQID(USB_REQUEST_TYPE_CDC_INTERFACE_IN,  USB_REQUEST_CODE_CDC_GET_UNIT_PARAMETER),
	USB_REQUEST_CDC_CLEAR_UNIT_PARAMETER = USB_MKRQID(USB_REQUEST_TYPE_CDC_INTERFACE_OUT, USB_REQUEST_CODE_CDC_CLEAR_UNIT_PARAMETER),

	USB_REQUEST_CDC_GET_PROFILE = USB_MKRQID(USB_REQUEST_TYPE_CDC_INTERFACE_IN, USB_REQUEST_CODE_CDC_GET_PROFILE),

//
// USBECM1.2 request codes
//
	USB_REQUEST_CDC_SET_ETHERNET_MULTICAST_FILTERS = USB_MKRQID(USB_REQUEST_TYPE_CDC_INTERFACE_OUT, USB_REQUEST_CODE_CDC_SET_ETHERNET_MULTICAST_FILTERS),

	USB_REQUEST_CDC_SET_ETHERNET_POWER_MANAGEMENT_PATTERN_FILTER = USB_MKRQID(USB_REQUEST_TYPE_CDC_INTERFACE_OUT, USB_REQUEST_CODE_CDC_SET_ETHERNET_POWER_MANAGEMENT_PATTERN_FILTER),
	USB_REQUEST_CDC_GET_ETHERNET_POWER_MANAGEMENT_PATTERN_FILTER = USB_MKRQID(USB_REQUEST_TYPE_CDC_INTERFACE_IN,  USB_REQUEST_CODE_CDC_GET_ETHERNET_POWER_MANAGEMENT_PATTERN_FILTER),

	USB_REQUEST_CDC_SET_ETHERNET_PACKET_FILTER = USB_MKRQID(USB_REQUEST_TYPE_CDC_INTERFACE_OUT, USB_REQUEST_CODE_CDC_SET_ETHERNET_PACKET_FILTER),
	USB_REQUEST_CDC_GET_ETHERNET_STATISTIC     = USB_MKRQID(USB_REQUEST_TYPE_CDC_INTERFACE_IN,  USB_REQUEST_CODE_CDC_GET_ETHERNET_STATISTIC),

//
// USBATM1.2 request codes
//
	USB_REQUEST_CDC_SET_ATM_DATA_FORMAT = USB_MKRQID(USB_REQUEST_TYPE_CDC_INTERFACE_OUT, USB_REQUEST_CODE_CDC_SET_ATM_DATA_FORMAT),

	USB_REQUEST_CDC_GET_ATM_DEVICE_STATISTICS = USB_MKRQID(USB_REQUEST_TYPE_CDC_INTERFACE_IN,  USB_REQUEST_CODE_CDC_GET_ATM_DEVICE_STATISTICS),
	USB_REQUEST_CDC_SET_ATM_DEFAULT_VC        = USB_MKRQID(USB_REQUEST_TYPE_CDC_INTERFACE_OUT, USB_REQUEST_CODE_CDC_SET_ATM_DEFAULT_VC),
	USB_REQUEST_CDC_GET_ATM_VC_STATISTICS     = USB_MKRQID(USB_REQUEST_TYPE_CDC_INTERFACE_IN,  USB_REQUEST_CODE_CDC_GET_ATM_VC_STATISTICS),

//
// USBNCM1.0 request codes
//
	USB_REQUEST_CDC_GET_NTB_PARAMETERS    = USB_MKRQID(USB_REQUEST_TYPE_CDC_INTERFACE_IN,  USB_REQUEST_CODE_CDC_GET_NTB_PARAMETERS),
	USB_REQUEST_CDC_GET_NET_ADDRESS       = USB_MKRQID(USB_REQUEST_TYPE_CDC_INTERFACE_IN,  USB_REQUEST_CODE_CDC_GET_NET_ADDRESS),
	USB_REQUEST_CDC_SET_NET_ADDRESS       = USB_MKRQID(USB_REQUEST_TYPE_CDC_INTERFACE_OUT, USB_REQUEST_CODE_CDC_SET_NET_ADDRESS),
	USB_REQUEST_CDC_GET_NTB_FORMAT        = USB_MKRQID(USB_REQUEST_TYPE_CDC_INTERFACE_IN,  USB_REQUEST_CODE_CDC_GET_NTB_FORMAT),
	USB_REQUEST_CDC_SET_NTB_FORMAT        = USB_MKRQID(USB_REQUEST_TYPE_CDC_INTERFACE_OUT, USB_REQUEST_CODE_CDC_SET_NTB_FORMAT),
	USB_REQUEST_CDC_GET_NTB_INPUT_SIZE    = USB_MKRQID(USB_REQUEST_TYPE_CDC_INTERFACE_IN,  USB_REQUEST_CODE_CDC_GET_NTB_INPUT_SIZE),
	USB_REQUEST_CDC_SET_NTB_INPUT_SIZE    = USB_MKRQID(USB_REQUEST_TYPE_CDC_INTERFACE_OUT, USB_REQUEST_CODE_CDC_SET_NTB_INPUT_SIZE),
	USB_REQUEST_CDC_GET_MAX_DATAGRAM_SIZE = USB_MKRQID(USB_REQUEST_TYPE_CDC_INTERFACE_IN,  USB_REQUEST_CODE_CDC_GET_MAX_DATAGRAM_SIZE),
	USB_REQUEST_CDC_SET_MAX_DATAGRAM_SIZE = USB_MKRQID(USB_REQUEST_TYPE_CDC_INTERFACE_OUT, USB_REQUEST_CODE_CDC_SET_MAX_DATAGRAM_SIZE),
	USB_REQUEST_CDC_GET_CRC_MODE          = USB_MKRQID(USB_REQUEST_TYPE_CDC_INTERFACE_IN,  USB_REQUEST_CODE_CDC_GET_CRC_MODE),
	USB_REQUEST_CDC_SET_CRC_MODE          = USB_MKRQID(USB_REQUEST_TYPE_CDC_INTERFACE_OUT, USB_REQUEST_CODE_CDC_SET_CRC_MODE),

};


enum {

//
// USBCDC1.2 notification codes
//
	USB_NOTIFICATION_CDC_NETWORK_CONNECTION      = USB_MKRQID(USB_REQUEST_TYPE_CDC_INTERFACE_IN, USB_NOTIFICATION_CODE_CDC_NETWORK_CONNECTION),
	USB_NOTIFICATION_CDC_RESPONSE_AVAILABLE      = USB_MKRQID(USB_REQUEST_TYPE_CDC_INTERFACE_IN, USB_NOTIFICATION_CODE_CDC_RESPONSE_AVAILABLE),
	USB_NOTIFICATION_CDC_CONNECTION_SPEED_CHANGE = USB_MKRQID(USB_REQUEST_TYPE_CDC_INTERFACE_IN, USB_NOTIFICATION_CODE_CDC_CONNECTION_SPEED_CHANGE),

//
// USBPSTN1.2 notification codes
//
	USB_NOTIFICATION_AUX_JACK_HOOK_STATE = USB_MKRQID(USB_REQUEST_TYPE_CDC_INTERFACE_IN, USB_NOTIFICATION_CODE_AUX_JACK_HOOK_STATE),
	USB_NOTIFICATION_RING_DETECT         = USB_MKRQID(USB_REQUEST_TYPE_CDC_INTERFACE_IN, USB_NOTIFICATION_CODE_RING_DETECT),

	USB_NOTIFICATION_SERIAL_STATE      = USB_MKRQID(USB_REQUEST_TYPE_CDC_INTERFACE_IN, USB_NOTIFICATION_CODE_SERIAL_STATE),
	USB_NOTIFICATION_CALL_STATE_CHANGE = USB_MKRQID(USB_REQUEST_TYPE_CDC_INTERFACE_IN, USB_NOTIFICATION_CODE_CALL_STATE_CHANGE),
	USB_NOTIFICATION_LINE_STATE_CHANGE = USB_MKRQID(USB_REQUEST_TYPE_CDC_INTERFACE_IN, USB_NOTIFICATION_CODE_LINE_STATE_CHANGE)

};


enum {

	USB_CDC_CAPS_DEFAULT = 0,

//
// Call management capabilities
//
	USB_CDC_CAPS_NO_CALL_MGMT  = 0 << 0,
	USB_CDC_CAPS_HAS_CALL_MGMT = 1 << 0,

	USB_CDC_CAPS_CALL_MGMT_ON_CI = 0 << 1,
	USB_CDC_CAPS_CALL_MGMT_ON_DI = 1 << 1,

//
// Abstract control model capabilities
//
	USB_CDC_CAPS_HAS_SFC_CFC_GFC     = 1 << 0,
	USB_CDC_CAPS_HAS_SLC_SCLS_GLC_SL = 1 << 1,
	USB_CDC_CAPS_HAS_SB              = 1 << 2,
	USB_CDC_CAPS_HAS_NC              = 1 << 3,

//
// Direct line control model capabilities
//
	USB_CDC_CAPS_HAS_PS_SP_SPT         = 1 << 0,
	USB_CDC_CAPS_HAS_SALS_RAJ_AJHS     = 1 << 1,
	USB_CDC_CAPS_DLC_EXTRA_PS_REQUIRED = 1 << 2,

//
// Telephone operational mode capabilities
//
	USB_CDC_CAPS_TELOP_NO_SIMPLE_MODE  = 0 << 0,
	USB_CDC_CAPS_TELOP_HAS_SIMPLE_MODE = 1 << 0,

	USB_CDC_CAPS_TELOP_NO_STANDALONE_MODE  = 0 << 1,
	USB_CDC_CAPS_TELOP_HAS_STANDALONE_MODE = 1 << 1,

	USB_CDC_CAPS_TELOP_NO_COMPCENTRIC_MODE  = 0 << 2,
	USB_CDC_CAPS_TELOP_HAS_COMPCENTRIC_MODE = 1 << 2,

//
// Telephone call and line state reporting capabilities
//
	USB_CDC_CAPS_HAS_IDT_REPORT           = 1 << 0,
	USB_CDC_CAPS_HAS_RB_B_FB_REPORT       = 1 << 1,
	USB_CDC_CAPS_HAS_CALLER_ID_REPORT     = 1 << 2,
	USB_CDC_CAPS_HAS_DISTINCT_RING_REPORT = 1 << 3,
	USB_CDC_CAPS_HAS_DTMF_DIGIT_REPORT    = 1 << 4,
	USB_CDC_CAPS_HAS_LS_CHANGE_REPORT     = 1 << 5,

//
// USB terminal function options
//
	USB_CDC_CAPS_NO_PROTOCOL_WRAPPER  = 0 << 0,
	USB_CDC_CAPS_HAS_PROTOCOL_WRAPPER = 1 << 0,

//
// Multichannel management capabilities
//
	USB_CDC_CAPS_HAS_NVMEM_STORAGE = 1 << 0,
	USB_CDC_CAPS_HAS_CUP           = 1 << 1,
	USB_CDC_CAPS_HAS_SUP           = 1 << 2,

//
// CAPI control management capabilities
//
	USB_CDC_CAPS_CAPI_SIMPLE      = 0 << 0,
	USB_CDC_CAPS_CAPI_INTELLIGENT = 1 << 0,

//
// Ethernet reporting capabilities
//
	USB_CDC_CAPS_ETHER_XMIT_OK                = 1 << 0,    // Frames transmitted without errors
	USB_CDC_CAPS_ETHER_RVC_OK                 = 1 << 1,    // Frames received without errors
	USB_CDC_CAPS_ETHER_XMIT_ERROR             = 1 << 2,    // Frames not transmitted, or transmitted with errors
	USB_CDC_CAPS_ETHER_RCV_ERROR              = 1 << 3,    // Frames received with errors that are not delivered to the USB host.
	USB_CDC_CAPS_ETHER_RCV_NO_BUFFER          = 1 << 4,    // Frame missed, no buffers
	USB_CDC_CAPS_ETHER_DIRECTED_BYTES_XMIT    = 1 << 5,    // Directed bytes transmitted without errors
	USB_CDC_CAPS_ETHER_DIRECTED_FRAMES_XMIT   = 1 << 6,    // Directed frames transmitted without errors
	USB_CDC_CAPS_ETHER_MULTICAST_BYTES_XMIT   = 1 << 7,    // Multicast bytes transmitted without errors
	USB_CDC_CAPS_ETHER_MULTICAST_FRAMES_XMIT  = 1 << 8,    // Multicast frames transmitted without errors
	USB_CDC_CAPS_ETHER_BROADCAST_BYTES_XMIT   = 1 << 9,    // Broadcast bytes transmitted without errors
	USB_CDC_CAPS_ETHER_BROADCAST_FRAMES_XMIT  = 1 << 10,   // Broadcast frames transmitted without errors
	USB_CDC_CAPS_ETHER_DIRECTED_BYTES_RCV     = 1 << 11,   // Directed bytes received without errors
	USB_CDC_CAPS_ETHER_DIRECTED_FRAMES_RCV    = 1 << 12,   // Directed frames received without errors
	USB_CDC_CAPS_ETHER_MULTICAST_BYTES_RCV    = 1 << 13,   // Multicast bytes received without errors
	USB_CDC_CAPS_ETHER_MULTICAST_FRAMES_RCV   = 1 << 14,   // Multicast frames received without errors
	USB_CDC_CAPS_ETHER_BROADCAST_BYTES_RCV    = 1 << 15,   // Broadcast bytes received without errors
	USB_CDC_CAPS_ETHER_BROADCAST_FRAMES_RCV   = 1 << 16,   // Broadcast frames received without errors
	USB_CDC_CAPS_ETHER_RCV_CRC_ERROR          = 1 << 17,   // Frames received with circular redundancy check (CRC) or frame check sequence (FCS) error
	USB_CDC_CAPS_ETHER_TRANSMIT_QUEUE_LENGTH  = 1 << 18,   // Length of transmit queue
	USB_CDC_CAPS_ETHER_RCV_ERROR_ALIGNMENT    = 1 << 19,   // Frames received with alignment error
	USB_CDC_CAPS_ETHER_XMIT_ONE_COLLISION     = 1 << 20,   // Frames transmitted with one collision
	USB_CDC_CAPS_ETHER_XMIT_MORE_COLLISIONS   = 1 << 21,   // Frames transmitted with more than one collision
	USB_CDC_CAPS_ETHER_XMIT_DEFERRED          = 1 << 22,   // Frames transmitted after deferral
	USB_CDC_CAPS_ETHER_XMIT_MAX_COLLISIONS    = 1 << 23,   // Frames not transmitted due to collisions
	USB_CDC_CAPS_ETHER_RCV_OVERRUN            = 1 << 24,   // Frames not received due to overrun
	USB_CDC_CAPS_ETHER_XMIT_UNDERRUN          = 1 << 25,   // Frames not transmitted due to underrun
	USB_CDC_CAPS_ETHER_XMIT_HEARTBEAT_FAILURE = 1 << 26,   // Frames transmitted with heartbeat failure
	USB_CDC_CAPS_ETHER_XMIT_TIMES_CRS_LOST    = 1 << 27,   // Times carrier sense signal lost during transmission
	USB_CDC_CAPS_ETHER_XMIT_LATE_COLLISIONS   = 1 << 28,   // Late collisions detected

//
// ATM networking function capabilities
//
	USB_CDC_CAPS_HAS_CONCAT_ATM                     = 1 << 1,
	USB_CDC_CAPS_HAS_ATM_HEADER_TEMPLATE_CONCAT_ATM = 1 << 2,
	USB_CDC_CAPS_HAS_AAL5_SDU                       = 1 << 3,

	USB_CDC_CAPS_HAS_DS_CELLS_RECEIVED            = 1 << 0,
	USB_CDC_CAPS_HAS_US_CELLS_SENT                = 1 << 1,
	USB_CDC_CAPS_HAS_DS_CELLS_HEC_ERROR_CORRECTED = 1 << 2,
	USB_CDC_CAPS_HAS_VC_DS_CELLS_RECEIVED         = 1 << 3,
	USB_CDC_CAPS_HAS_VC_US_CELLS_SENT             = 1 << 4,

//
// OBEX Service ID function capabilities
//
	USB_CDC_CAPS_HAS_OBEX_ALT_SERVER = 0 << 0,
	USB_CDC_CAPS_HAS_OBEX_ALT_CLIENT = 1 << 0,

//
// NCM function capabilities
//
	USB_CDC_CAPS_HAS_NCM_SEP_FILTER = 1 << 0,
	USB_CDC_CAPS_HAS_GNA_SNA        = 1 << 1,
	USB_CDC_CAPS_HAS_SEC_GER        = 1 << 2,
	USB_CDC_CAPS_HAS_SMDS_GMDS      = 1 << 3,
	USB_CDC_CAPS_HAS_SCM_GCM        = 1 << 4

};


#define USB_CDC(functions...)                                \
	5,                                                   \
	USB_DESCRIPTOR_CDC_CS_INTERFACE,                     \
	USB_DESCRIPTOR_CDC_FUNC_HEADER,                      \
	BYTE(USB_CDC_VERSION, 0), BYTE(USB_CDC_VERSION, 1),  \
	functions


#define USB_CDC_FUNC_CALL_MGMT(capabilities, data_intf)  \
	5,                                               \
	USB_DESCRIPTOR_CDC_CS_INTERFACE,                 \
	USB_DESCRIPTOR_CDC_FUNC_CALL_MGMT,               \
	(capabilities),                                  \
	(data_intf)


#define USB_CDC_FUNC_ABSTRACT_CONTROL_MGMT(capabilities)  \
	4,                                                \
	USB_DESCRIPTOR_CDC_CS_INTERFACE,                  \
	USB_DESCRIPTOR_CDC_FUNC_ABSTRACT_CONTROL_MGMT,    \
	(capabilities)


#define USB_CDC_FUNC_DIRECT_LINE_MGMT(capabilities)  \
	4,                                           \
	USB_DESCRIPTOR_CDC_CS_INTERFACE,             \
	USB_DESCRIPTOR_CDC_FUNC_DIRECT_LINE_MGMT,    \
	(capabilities)


#define USB_CDC_FUNC_TELEPHONE_RINGER(numvolsteps, numringpatterns)  \
	5,                                                           \
	USB_DESCRIPTOR_CDC_CS_INTERFACE,                             \
	USB_DESCRIPTOR_CDC_FUNC_TELEPHOBE_RINGER,                    \
	(numvolsteps),                                               \
	(numringpatterns)


#define USB_CDC_FUNC_TELEPHONE_LINE_STATE_REPORT(capabilities)     \
	4,                                                         \
	USB_DESCRIPTOR_CDC_CS_INTERFACE,                           \
	USB_DESCRIPTOR_CDC_FUNC_TELEPHOBE_CALL_LINE_STATE_REPORT,  \
	(capabilities)


#define USB_CDC_FUNC_UNION(master_intf, slave_intfs...)  \
	4 + PP_NARG(slave_intfs),                        \
	USB_DESCRIPTOR_CDC_CS_INTERFACE,                 \
	USB_DESCRIPTOR_CDC_FUNC_UNION,                   \
	(master_intf),                                   \
	slave_intfs


#define USB_CDC_FUNC_COUNTRY_SELECT_COUNTRY_CODE(country_code) \
	, BYTE(country_code, 0), BYTE(country_code, 1)

#define USB_CDC_FUNC_COUNTRY_SELECT(iso3166_release_id, country_codes...)  \
	4 + 2 * PP_NARG(country_codes),                                    \
	USB_DESCRIPTOR_CDC_CS_INTERFACE,                                   \
	USB_DESCRIPTOR_CDC_FUNC_COUNTRY_SELECT,                            \
	(iso3166_release_id)                                               \
	PP_FOREACH(USB_CDC_FUNC_COUNTRY_SELECT_COUNTRY_CODE, country_codes)


#define USB_CDC_FUNC_TELEPHONE_OPMODES(capabilities)  \
	4,                                            \
	USB_DESCRIPTOR_CDC_CS_INTERFACE,              \
	USB_DESCRIPTOR_CDC_FUNC_TELEPHONE_OPMODES,    \
	(capabilities)


#define USB_CDC_FUNC_USB_TERMINAL(term_id, intf_in, intf_out, options, children...)  \
	7 + PP_NARG(children),                                                       \
	USB_DESCRIPTOR_CDC_CS_INTERFACE,                                             \
	USB_DESCRIPTOR_CDC_FUNC_USB_TERMINAL,                                        \
	(term_id),                                                                   \
	(intf_in),                                                                   \
	(intf_out),                                                                  \
	(options),                                                                   \
	children


#define USB_CDC_FUNC_NETWORK_CHANNEL_TERMINAL(term_id, namestr, channel_idx, phys_intf)  \
	7,                                                                               \
	USB_DESCRIPTOR_CDC_CS_INTERFACE,                                                 \
	USB_DESCRIPTOR_CDC_FUNC_NETWORK_CHANNEL_TERMINAL,                                \
	(term_id),                                                                       \
	(namestr),                                                                       \
	(channel_idx),                                                                   \
	(phys_intf)


#define USB_CDC_FUNC_PROTOCOL_UNIT(unit_id, protocol, children...)  \
	5 + PP_NARG(children),                                      \
	USB_DESCRIPTOR_CDC_CS_INTERFACE,                            \
	USB_DESCRIPTOR_CDC_FUNC_PROTOCOL_UNIT,                      \
	(unit_id),                                                  \
	(protocol),                                                 \
	children


#define USB_CDC_FUNC_EXTENSION_UNIT(unit_id, extcode, namestr, children...)  \
	6 + PP_NARG(children),                                               \
	USB_DESCRIPTOR_CDC_CS_INTERFACE,                                     \
	USB_DESCRIPTOR_CDC_FUNC_EXTENSION_UNIT,                              \
	(unit_id),                                                           \
	(extcode),                                                           \
	(namestr),                                                           \
	children


#define USB_CDC_FUNC_MULTICHANNEL_MGMT(capabilities)  \
	4,                                            \
	USB_DESCRIPTOR_CDC_CS_INTERFACE,              \
	USB_DESCRIPTOR_CDC_FUNC_MULTICHANNEL_MGMT,    \
	(capabilities)


#define USB_CDC_FUNC_CAPI_CONTROL_MGMT(capabilities)  \
	4,                                            \
	USB_DESCRIPTOR_CDC_CS_INTERFACE,              \
	USB_DESCRIPTOR_CDC_FUNC_CAPI_CONTROL_MGMT,    \
	(capabilities)


#define USB_CDC_FUNC_ETHERNET_NETWORKING(macaddrstr, etherstats, mtu, num_mc_filters, num_pwr_filters)   \
	13,                                                                                              \
	USB_DESCRIPTOR_CDC_CS_INTERFACE,                                                                 \
	USB_DESCRIPTOR_CDC_FUNC_ETHERNET_NETWORKING,                                                     \
	(macaddrstr),                                                                                    \
	BYTE((etherstats), 0),     BYTE((etherstats), 1), BYTE((etherstats), 2), BYTE((etherstats), 3),  \
	BYTE((mtu), 0),            BYTE((mtu), 1),                                                       \
	BYTE((num_mc_filters), 0), BYTE((num_mc_filters), 1),                                            \
	(num_pwr_filters)


#define USB_CDC_FUNC_ATM_NETWORKING(endsystemstr, datacaps, atmstats, type2mtu, type3mtu, maxvc)  \
	12,                                                                                       \
	USB_DESCRIPTOR_CDC_CS_INTERFACE,                                                          \
	USB_DESCRIPTOR_CDC_FUNC_ATM_NETWORKING,                                                   \
	(endsystemstr),                                                                           \
	(datacaps),                                                                               \
	(atmstats),                                                                               \
	BYTE((type2mtu), 0), BYTE((type2mtu), 1),                                                 \
	BYTE((type3mtu), 0), BYTE((type3mtu), 1),                                                 \
	BYTE((maxvc), 0),    BYTE((maxvc), 1)


#define USB_CDC_FUNC_WIRELESS_HANDSET_CONTROL_MODEL()            \
	5,                                                       \
	USB_DESCRIPTOR_CDC_CS_INTERFACE,                         \
	USB_DESCRIPTOR_CDC_FUNC_WIRELESS_HANDSET_CONTROL_MODEL,  \
	BYTE(USB_CDC_WMC_VERSION, 0), BYTE(USB_CDC_WMC_VERSION, 1)


#define USB_CDC_FUNC_MOBILE_DIRECT_LINE_MODEL(                                        \
		uuid0, uuid1, uuid2,  uuid3,  uuid4,  uuid5,  uuid6,  uuid7,          \
		uuid8, uuid9, uuid10, uuid11, uuid12, uuid13, uuid14, uuid15)         \
	21,                                                                           \
	USB_DESCRIPTOR_CDC_CS_INTERFACE,                                              \
	USB_DESCRIPTOR_CDC_FUNC_MOBILE_DIRECT_LINE_MODEL,                             \
	BYTE((USB_CDC_WMC_VERSION), 0), BYTE((USB_CDC_WMC_VERSION), 1)                \
	(uuid0), (uuid1), (uuid2),  (uuid3),  (uuid4),  (uuid5),  (uuid6),  (uuid7),  \
	(uuid8), (uuid9), (uuid10), (uuid11), (uuid12), (uuid13), (uuid14), (uuid15)


#define USB_CDC_FUNC_MDLM_DETAIL(guid_descriptor_type, data...)  \
	4 + PP_NARG(data),                                       \
	USB_DESCRIPTOR_CDC_CS_INTERFACE,                         \
	USB_DESCRIPTOR_CDC_FUNC_MDLM_DETAIL,                     \
	(guid_descriptor_type),                                  \
	data


#define USB_CDC_FUNC_DEVICE_MGMT_MODEL(maxcmd)                       \
	7,                                                           \
	USB_DESCRIPTOR_CDC_CS_INTERFACE,                             \
	USB_DESCRIPTOR_CDC_FUNC_DEVICE_MGMT_MODEL,                   \
	BYTE(USB_CDC_WMC_VERSION, 0), BYTE(USB_CDC_WMC_VERSION, 1),  \
	(maxcmd)


#define USB_CDC_FUNC_OBEX()               \
	5,                                \
	USB_DESCRIPTOR_CDC_CS_INTERFACE,  \
	USB_DESCRIPTOR_CDC_FUNC_OBEX,     \
	BYTE(USB_CDC_WMC_VERSION, 0), BYTE(USB_CDC_WMC_VERSION, 1)


#define USB_CDC_FUNC_COMMAND_SET(cmdset,                                              \
		uuid0, uuid1, uuid2,  uuid3,  uuid4,  uuid5,  uuid6,  uuid7,          \
		uuid8, uuid9, uuid10, uuid11, uuid12, uuid13, uuid14, uuid15)         \
	22,                                                                           \
	USB_DESCRIPTOR_CDC_CS_INTERFACE,                                              \
	USB_DESCRIPTOR_CDC_FUNC_COMMAND_SET,                                          \
	BYTE(USB_CDC_WMC_VERSION, 0), BYTE(USB_CDC_WMC_VERSION, 1),                   \
	(cmdset),                                                                     \
	(uuid0), (uuid1), (uuid2),  (uuid3),  (uuid4),  (uuid5),  (uuid6),  (uuid7),  \
	(uuid8), (uuid9), (uuid10), (uuid11), (uuid12), (uuid13), (uuid14), (uuid15)


#define USB_CDC_FUNC_COMMAND_SET_DETAIL(guid_descriptor_type, data...)  \
	4 + PP_NARG(data),                                              \
	USB_DESCRIPTOR_CDC_CS_INTERFACE,                                \
	USB_DESCRIPTOR_CDC_FUNC_COMMAND_SET_DETAIL,                     \
	(guid_descriptor_type),                                         \
	data


#define USB_CDC_FUNC_TELEPHONE_CONTROL_MODEL(maxcmd)                 \
	7,                                                           \
	USB_DESCRIPTOR_CDC_CS_INTERFACE,                             \
	USB_DESCRIPTOR_CDC_FUNC_TELEPHONE_CONTROL_MODEL,             \
	BYTE(USB_CDC_WMC_VERSION, 0), BYTE(USB_CDC_WMC_VERSION, 1),  \
	(maxcmd)


#define USB_CDC_FUNC_OBEX_SERVICE_ID(role, version,                                    \
		uuid0, uuid1, uuid2,  uuid3,  uuid4,  uuid5,  uuid6,  uuid7,           \
		uuid8, uuid9, uuid10, uuid11, uuid12, uuid13, uuid14, uuid15)          \
	22,                                                                            \
	USB_DESCRIPTOR_CDC_CS_INTERFACE,                                               \
	USB_DESCRIPTOR_CDC_FUNC_OBEX_SERVICE_ID,                                       \
	(role),                                                                        \
	(uuid0), (uuid1), (uuid2),  (uuid3),  (uuid4),  (uuid5),  (uuid6),  (uuid7),   \
	(uuid8), (uuid9), (uuid10), (uuid11), (uuid12), (uuid13), (uuid14), (uuid15),  \
	BYTE((version), 0), BYTE((version), 1)


#define USB_CDC_FUNC_NCM(capabilities)                              \
	6,                                                          \
	USB_DESCRIPTOR_CDC_CS_INTERFACE,                            \
	USB_DESCRIPTOR_CDC_FUNC_NCM,                                \
	BYTE(USB_CDC_WMC_VERSION, 0), BYTE(USB_CDC_WMC_VERSION, 1)  \
	(capabilities)



//
// Default OBEX server/client UUID, defined by the Bluetooth SIG
//
#define USB_CDC_WMC_DEFAULT_OBEX_SERVER_UUID            \
	0x02, 0xae, 0xb3, 0x20, 0xf6, 0x49, 0x11, 0xda, \
	0x97, 0x4d, 0x08, 0x00, 0x20, 0x0c, 0x9a, 0x66


#endif

