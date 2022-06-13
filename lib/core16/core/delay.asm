

#include <p18cxxx.inc>


	radix dec


	global _usleep
	global _msleep
	global _sleep

	udata

_counter_ms  res 1
_counter_s   res 1

	code

;
; 8MHz
;
;_usleep:
;	nop
;	decf WREG
;	bz _usleep_done
;	nop
;	goto $+4
;	goto _usleep
;_usleep_done:
;	return
;


;
; 4MHz
;
_usleep:
	nop
	decfsz WREG, F
	goto _usleep
	return



_msleep:
	movwf _counter_ms

_msleep_loop:
	movlw 249
	call _usleep

	movlw 249
	call _usleep

	movlw 249
	call _usleep

	movlw 249
	call _usleep

	decfsz _counter_ms, F
	goto _msleep_loop

	return



_sleep:
	movwf _counter_s

_sleep_loop:
	movlw 250
	call _msleep

	movlw 250
	call _msleep

	movlw 250
	call _msleep

	movlw 250
	call _msleep

	decfsz _counter_s, F
	goto _sleep_loop

	return


	end

