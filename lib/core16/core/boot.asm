

#include <p18cxxx.inc>


	radix dec

	extern __core_reset
	extern __core_vector_hi
	extern __core_vector_lo



_core_reset_vector: code 0x0000
	nop
	goto __core_reset



_core_interrupt_vector_0: code 0x0008
	goto __core_vector_hi



_core_interrupt_vector_1: code 0x0018
	goto __core_vector_lo



	end

