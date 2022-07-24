

#include <p18cxxx.inc>


	RADIX DEC


;
; Make sure the configuration is linked
;
	GLOBAL _config
	CODE
_config:


;
; Watchdog timer configuration
;
#ifdef CONFIG_CPU_WDT
	CONFIG WDT = CONFIG_CPU_WDT
#else
	CONFIG WDT = OFF
#endif


;
; External reset pin configuration
;
#ifdef CONFIG_CPU_MCLRE
	CONFIG MCLRE = CONFIG_CPU_MCLRE
#else
	CONFIG MCLRE = ON
#endif


;
; Degugger configuration
;
#ifdef CONFIG_CPU_DEBUG
	CONFIG DEBUG = CONFIG_CPU_DEBUG
#else
	CONFIG DEBUG = OFF
#endif


;
; Low-voltage programming configuration
;
#ifdef CONFIG_CPU_LVP
	CONFIG LVP = CONFIG_CPU_LVP
#else
	CONFIG LVP = OFF
#endif


;
; External clock PLL divisor configuration
;
#ifdef CONFIG_CPU_PLLDIV
	CONFIG PLLDIV = CONFIG_CPU_PLLDIV
#else
	CONFIG PLLDIV = 1
#endif


;
; CPU clock divisor configuration
;
#ifdef CONFIG_CPU_CPUDIV
	CONFIG CPUDIV = CONFIG_CPU_CPUDIV
#else
	CONFIG CPUDIV = OSC1_PLL2
#endif


;
; USB clock divisor configuration
;
#ifdef CONFIG_CPU_USBDIV
	CONFIG USBDIV = CONFIG_CPU_USBDIV
#else
	CONFIG USBDIV = 1
#endif


;
; Main oscillator configuration
;
#ifdef CONFIG_CPU_FOSC
	CONFIG FOSC = CONFIG_CPU_FOSC
#else
	CONFIG FOSC = HS
#endif


;
; Stack oveflow detector configuration
;
#ifdef CONFIG_CPU_STVREN
	CONFIG STVREN = CONFIG_CPU_STVREN
#else
	CONFIG STVREN = OFF
#endif


;
; Extender instructions disabled, doesn't work with SDCC
;
	CONFIG XINST  = OFF


	END

