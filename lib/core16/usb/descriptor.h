

#ifndef USB_DESCRIPTOR_H
#define USB_DESCRIPTOR_H


enum {

	USB_DESCRIPTOR_DEVICE           = 0x01,
	USB_DESCRIPTOR_CONFIGURATION    = 0x02,
	USB_DESCRIPTOR_STRING           = 0x03,
	USB_DESCRIPTOR_INTERFACE        = 0x04,
	USB_DESCRIPTOR_ENDPOINT         = 0x05,
	USB_DESCRIPTOR_DEVICE_QUALIFIER = 0x06,
	USB_DESCRIPTOR_OTHER_SPEED      = 0x07

};


enum {

	USB_CLASS_NONE   = 0x00,
	USB_CLASS_VENDOR = 0xff

};


enum {

	USB_SUBCLASS_NONE   = 0x00,
	USB_SUBCLASS_VENDOR = 0xff

};


enum {

	USB_PROTOCOL_NONE   = 0x00,
	USB_PROTOCOL_VENDOR = 0xff

};


enum {

	USB_VERSION = 0x0200

};


enum {

	USB_LANG_AF_ZA    = 0x0436,     // Afrikaans
	USB_LANG_SQ_AL    = 0x041c,     // Albanian
	USB_LANG_AR_SA    = 0x0401,     // Arabic (Saudi Arabia)
	USB_LANG_AR_IQ    = 0x0801,     // Arabic (Iraq)
	USB_LANG_AR_EG    = 0x0c01,     // Arabic (Egypt)
	USB_LANG_AR_LY    = 0x1001,     // Arabic (Libya)
	USB_LANG_AR_DZ    = 0x1401,     // Arabic (Algeria)
	USB_LANG_AR_MA    = 0x1801,     // Arabic (Morocco)
	USB_LANG_AR_TN    = 0x1c01,     // Arabic (Tunisia)
	USB_LANG_AR_OM    = 0x2001,     // Arabic (Oman)
	USB_LANG_AR_YE    = 0x2401,     // Arabic (Yemen)
	USB_LANG_AR_SY    = 0x2801,     // Arabic (Syria)
	USB_LANG_AR_JO    = 0x2c01,     // Arabic (Jordan)
	USB_LANG_AR_LB    = 0x3001,     // Arabic (Lebanon)
	USB_LANG_AR_KW    = 0x3401,     // Arabic (Kuwait)
	USB_LANG_AR_AE    = 0x3801,     // Arabic (U.A.E.)
	USB_LANG_AR_BH    = 0x3c01,     // Arabic (Bahrain)
	USB_LANG_AR_QA    = 0x4001,     // Arabic (Qatar)
	USB_LANG_HY_AM    = 0x042b,     // Armenian
	USB_LANG_AS_IN    = 0x044d,     // Assamese
	USB_LANG_AZ_AZ_LT = 0x042c,     // Azeri (Latin)
	USB_LANG_AZ_AZ_CY = 0x082c,     // Azeri (Cyrillic)
	USB_LANG_AZ_AZ    = 0x082c,     // Azeri (Cyrillic)
	USB_LANG_EU_ES    = 0x042d,     // Basque
	USB_LANG_BE_BY    = 0x0423,     // Belarussian
	USB_LANG_BN_IN    = 0x0445,     // Bengali
	USB_LANG_BG_BG    = 0x0402,     // Bulgarian
	USB_LANG_MY_MM    = 0x0455,     // Burmese
	USB_LANG_CA_ES    = 0x0403,     // Catalan
	USB_LANG_ZH_TW    = 0x0404,     // Chinese (Taiwan)
	USB_LANG_ZH_CN    = 0x0804,     // Chinese (PRC)
	USB_LANG_ZH_HK    = 0x0c04,     // Chinese (Hong Kong SAR, PRC)
	USB_LANG_ZH_SG    = 0x1004,     // Chinese (Singapore)
	USB_LANG_ZH_MO    = 0x1404,     // Chinese (Macau SAR)
	USB_LANG_HR_HR    = 0x041a,     // Croatian
	USB_LANG_CS_CZ    = 0x0405,     // Czech
	USB_LANG_DA_DK    = 0x0406,     // Danish
	USB_LANG_NL_NL    = 0x0413,     // Dutch (Netherlands)
	USB_LANG_NL_BE    = 0x0813,     // Dutch (Belgium)
	USB_LANG_EN_US    = 0x0409,     // English (United States)
	USB_LANG_EN_GB    = 0x0809,     // English (United Kingdom)
	USB_LANG_EN_AU    = 0x0c09,     // English (Australian)
	USB_LANG_EN_CA    = 0x1009,     // English (Canadian)
	USB_LANG_EN_NZ    = 0x1409,     // English (New Zealand)
	USB_LANG_EN_IE    = 0x1809,     // English (Ireland)
	USB_LANG_EN_ZA    = 0x1c09,     // English (South Africa)
	USB_LANG_EN_JM    = 0x2009,     // English (Jamaica)
	USB_LANG_EN_CB    = 0x2409,     // English (Caribbean)
	USB_LANG_EN_BZ    = 0x2809,     // English (Belize)
	USB_LANG_EN_TT    = 0x2c09,     // English (Trinidad)
	USB_LANG_EN_ZW    = 0x3009,     // English (Zimbabwe)
	USB_LANG_EN_PH    = 0x3409,     // English (Philippines)
	USB_LANG_ET_EE    = 0x0425,     // Estonian
	USB_LANG_FO_FO    = 0x0438,     // Faeroese
	USB_LANG_FA_IR    = 0x0429,     // Farsi
	USB_LANG_FI_FI    = 0x040b,     // Finnish
	USB_LANG_FR_FR    = 0x040c,     // French (Standard)
	USB_LANG_FR_BE    = 0x080c,     // French (Belgian)
	USB_LANG_FR_CA    = 0x0c0c,     // French (Canadian)
	USB_LANG_FR_CH    = 0x100c,     // French (Switzerland)
	USB_LANG_FR_LU    = 0x140c,     // French (Luxembourg)
	USB_LANG_FR_MC    = 0x180c,     // French (Monaco)
	USB_LANG_KA_GE    = 0x0437,     // Georgian
	USB_LANG_DE_DE    = 0x0407,     // German (Standard)
	USB_LANG_DE_CH    = 0x0807,     // German (Switzerland)
	USB_LANG_DE_AT    = 0x0c07,     // German (Austria)
	USB_LANG_DE_LU    = 0x1007,     // German (Luxembourg)
	USB_LANG_DE_LI    = 0x1407,     // German (Liechtenstein)
	USB_LANG_EL_GR    = 0x0408,     // Greek
	USB_LANG_GU_IN    = 0x0447,     // Gujarati
	USB_LANG_HE_IL    = 0x040d,     // Hebrew
	USB_LANG_HI_IN    = 0x0439,     // Hindi
	USB_LANG_HU_HU    = 0x040e,     // Hungarian
	USB_LANG_IS_IS    = 0x040f,     // Icelandic
	USB_LANG_ID_ID    = 0x0421,     // Indonesian
	USB_LANG_IT_IT    = 0x0410,     // Italian (Standard)
	USB_LANG_IT_CH    = 0x0810,     // Italian (Switzerland)
	USB_LANG_JA_JP    = 0x0411,     // Japanese
	USB_LANG_KN_IN    = 0x044b,     // Kannada
	USB_LANG_KS_IN    = 0x0860,     // Kashmiri (India)
	USB_LANG_KK_KZ    = 0x043f,     // Kazakh
	USB_LANG_KOK_IN   = 0x0457,     // Konkani
	USB_LANG_KO_KR    = 0x0412,     // Korean
	USB_LANG_LV_LV    = 0x0426,     // Latvian
	USB_LANG_LT_LT    = 0x0427,     // Lithuanian
	USB_LANG_MK_MK    = 0x042f,     // Macedonian
	USB_LANG_MS_MY    = 0x043e,     // Malay (Malaysian)
	USB_LANG_MS_BN    = 0x083e,     // Malay (Brunei Darussalam)
	USB_LANG_ML_IN    = 0x044c,     // Malayalam
	USB_LANG_MNI_IN   = 0x0458,     // Manipuri
	USB_LANG_MR_IN    = 0x044e,     // Marathi
	USB_LANG_NE_IN    = 0x0861,     // Nepali (India)
	USB_LANG_NB_NO    = 0x0414,     // Norwegian (Bokmal)
	USB_LANG_NN_NO    = 0x0814,     // Norwegian (Nynorsk)
	USB_LANG_OR_IN    = 0x0448,     // Oriya
	USB_LANG_PL_OK    = 0x0415,     // Polish
	USB_LANG_PT_BR    = 0x0416,     // Portuguese (Brazil)
	USB_LANG_PT_PT    = 0x0816,     // Portuguese (Standard)
	USB_LANG_PA_IN    = 0x0446,     // Punjabi
	USB_LANG_RO_RO    = 0x0418,     // Romanian
	USB_LANG_RU_RU    = 0x0419,     // Russian
	USB_LANG_SA_IN    = 0x044f,     // Sanskrit
	USB_LANG_SR_RS_CY = 0x0c1a,     // Serbian (Cyrillic)
	USB_LANG_SR_RS_LT = 0x081a,     // Serbian (Latin)
	USB_LANG_SD_IN    = 0x0459,     // Sindhi
	USB_LANG_SK_SK    = 0x041b,     // Slovak
	USB_LANG_SL_SI    = 0x0424,     // Slovenian
	USB_LANG_ES_ES_TD = 0x040a,     // Spanish (Traditional Sort)
	USB_LANG_ES_MX    = 0x080a,     // Spanish (Mexican)
	USB_LANG_ES_ES    = 0x0c0a,     // Spanish (Modern Sort)
	USB_LANG_ES_GT    = 0x100a,     // Spanish (Guatemala)
	USB_LANG_ES_CR    = 0x140a,     // Spanish (Costa Rica)
	USB_LANG_ES_PA    = 0x180a,     // Spanish (Panama)
	USB_LANG_ES_DO    = 0x1c0a,     // Spanish (Dominican Republic)
	USB_LANG_ES_VE    = 0x200a,     // Spanish (Venezuela)
	USB_LANG_ES_CO    = 0x240a,     // Spanish (Colombia)
	USB_LANG_ES_PE    = 0x280a,     // Spanish (Peru)
	USB_LANG_ES_AR    = 0x2c0a,     // Spanish (Argentina)
	USB_LANG_ES_EC    = 0x300a,     // Spanish (Ecuador)
	USB_LANG_ES_CL    = 0x340a,     // Spanish (Chile)
	USB_LANG_ES_UY    = 0x380a,     // Spanish (Uruguay)
	USB_LANG_ES_PY    = 0x3c0a,     // Spanish (Paraguay)
	USB_LANG_ES_BO    = 0x400a,     // Spanish (Bolivia)
	USB_LANG_ES_SV    = 0x440a,     // Spanish (El Salvador)
	USB_LANG_ES_HN    = 0x480a,     // Spanish (Honduras)
	USB_LANG_ES_NI    = 0x4c0a,     // Spanish (Nicaragua)
	USB_LANG_ES_PR    = 0x500a,     // Spanish (Puerto Rico)
	USB_LANG_ST_ZA    = 0x0430,     // Sutu
	USB_LANG_SW_KE    = 0x0441,     // Swahili (Kenya)
	USB_LANG_SV_SE    = 0x041d,     // Swedish
	USB_LANG_SV_FI    = 0x081d,     // Swedish (Finland)
	USB_LANG_TA_IN    = 0x0449,     // Tamil
	USB_LANG_TT_RU    = 0x0444,     // Tatar (Tatarstan)
	USB_LANG_TE_IN    = 0x044a,     // Telugu
	USB_LANG_TH_TH    = 0x041e,     // Thai
	USB_LANG_TR_TR    = 0x041f,     // Turkish
	USB_LANG_UK_UA    = 0x0422,     // Ukrainian
	USB_LANG_UR_PK    = 0x0420,     // Urdu (Pakistan)
	USB_LANG_UR_IN    = 0x0820,     // Urdu (India)
	USB_LANG_UZ_UZ_LT = 0x0443,     // Uzbek (Latin)
	USB_LANG_UZ_UZ_CY = 0x0843,     // Uzbek (Cyrillic)
	USB_LANG_UZ_UZ    = 0x0843,     // Uzbek (Cyrillic)
	USB_LANG_VI_VN    = 0x042a      // Vietnamese

};


enum {

	USB_EP_ATTR_CONTROL     = 0 << 0,
	USB_EP_ATTR_ISOCHRONOUS = 1 << 0,
	USB_EP_ATTR_BULK        = 2 << 0,
	USB_EP_ATTR_INTERRUPT   = 3 << 0

};




#define USB_DESCRIPTOR_TABLE_BEGIN  \
	const code byte *__usb_descriptor_table(data word *__len, byte __dtype, byte __did) {

#define USB_DESCRIPTOR_TABLE_END  \
		return NULL; }



#define USB_DESCRIPTOR_BEGIN(datatype, __type, __id)   \
	if (__dtype == (__type) && __did == (__id)) {  \
		static const code datatype tmp[]={

#define USB_DESCRIPTOR_END                         \
		};                                 \
		*__len = sizeof(tmp);              \
		return (const code byte*)&tmp[0];  \
	}

#define USB_DESCRIPTOR(datatype, __type, __id, data...)  \
	USB_DESCRIPTOR_BEGIN(datatype, __type, __id)     \
		data                                     \
	USB_DESCRIPTOR_END



#define USB_DEVICE(vendor, product, release, vendor_str, product_str, serial_str, configurations)  \
	USB_DESCRIPTOR_BEGIN(byte, USB_DESCRIPTOR_DEVICE, 0)                                       \
		18,                                                                                \
		USB_DESCRIPTOR_DEVICE,                                                             \
		BYTE(USB_VERSION, 0), BYTE(USB_VERSION, 1),                                        \
		0x00, 0x00, 0x00,                                                                  \
		USB_BUFFER_SIZE,                                                                   \
		BYTE(vendor,  0), BYTE(vendor,  1),                                                \
		BYTE(product, 0), BYTE(product, 1),                                                \
		BYTE(release, 0), BYTE(release, 1),                                                \
		(vendor_str),                                                                      \
		(product_str),                                                                     \
		(serial_str),                                                                      \
		(configurations)                                                                   \
	USB_DESCRIPTOR_END


#define USB_CONFIGURATION(config_no, config_id, interfaces, config_str, attributes, power, config...)  \
	USB_DESCRIPTOR_BEGIN(byte, USB_DESCRIPTOR_CONFIGURATION, config_no)                            \
		9,                                                                                     \
		USB_DESCRIPTOR_CONFIGURATION,                                                          \
		BYTE(9 + PP_NARG(config), 0),                                                          \
		BYTE(9 + PP_NARG(config), 1),                                                          \
		(interfaces),                                                                          \
		(config_id),                                                                           \
		(config_str),                                                                          \
		(attributes),                                                                          \
		(power),                                                                               \
		config                                                                                 \
	USB_DESCRIPTOR_END


#define USB_LANGUAGE(lcids...)                                         \
	USB_DESCRIPTOR_BEGIN(word, USB_DESCRIPTOR_STRING, 0)           \
		USB_DESCRIPTOR_STRING * 256 + 2 * PP_NARG(lcids) + 2,  \
		lcids                                                  \
	USB_DESCRIPTOR_END


#define USB_STRING(id, str...)                                       \
	USB_DESCRIPTOR_BEGIN(word, USB_DESCRIPTOR_STRING, id)        \
		USB_DESCRIPTOR_STRING * 256 + 2 * PP_NARG(str) + 2,  \
		str                                                  \
	USB_DESCRIPTOR_END


#define USB_INTERFACE(iface_no, alternate, endpoints, class, subclass, protocol, iface_str)  \
	9,                                                                                   \
	USB_DESCRIPTOR_INTERFACE,                                                            \
	(iface_no),                                                                          \
	(alternate),                                                                         \
	(endpoints),                                                                         \
	(class),                                                                             \
	(subclass),                                                                          \
	(protocol),                                                                          \
	(iface_str)


#define USB_ENDPOINT(address, attributes, packet_size, interval)  \
	7,                                                        \
	USB_DESCRIPTOR_ENDPOINT,                                  \
	(address),                                                \
	(attributes),                                             \
	BYTE(packet_size, 0),                                     \
	BYTE(packet_size, 1),                                     \
	(interval)


#define USB_DEVICE_QUALIFIER(configurations)                            \
	USB_DESCRIPTOR_BEGIN(byte, USB_DESCRIPTOR_DEVICE_QUALIFIER, 0)  \
		10,                                                     \
		USB_DESCRIPTOR_DEVICE_QUALIFIER,                        \
		BYTE(USB_VERSION, 0), BYTE(USB_VERSION, 1),             \
		0x00, 0x00, 0x00,                                       \
		USB_BUFFER_SIZE,                                        \
		(configurations),                                       \
		0x00                                                    \
	USB_DESCRIPTOR_END


#define USB_OTHER_SPEED(config_no, config_id, interfaces, config_str, attributes, power, config...)  \
	USB_DESCRIPTOR_BEGIN(byte, USB_DESCRIPTOR_OTHER_SPEED, config_no)                            \
		9,                                                                                   \
		USB_DESCRIPTOR_OTHER_SPEED,                                                          \
		BYTE(9 + PP_NARG(config), 0),                                                        \
		BYTE(9 + PP_NARG(config), 1),                                                        \
		(interfaces),                                                                        \
		(config_id),                                                                         \
		(config_str),                                                                        \
		(attributes),                                                                        \
		(power),                                                                             \
		config                                                                               \
	USB_DESCRIPTOR_END


#endif
