

#ifndef __SIGNAL_H
#define __SIGNAL_H


#define _signal_c_base(base, code)  _signal_##base
#define _signal_s_base(base, code)  __signal_##base
#define _signal_code(base, code)    (code)
#define _signal_offset(base, code)  ((code) >> 3)
#define _signal_bit(base, code)     ((code) & 0x07)


#define _signal_alloc(name, number)\
	byte _signal_##name[1 + ((number) - 1) / 8]

#define _signal_raise(alias...)\
	{\
		_asm\
			\n\
			banksel _signal_s_base(alias) + _signal_offset(alias)\n\
			bsf _signal_s_base(alias) + _signal_offset(alias), _signal_bit(alias)\n\
		_endasm;\
	}

#define _signal_clear(alias...)\
	{\
		_asm\
			\n\
			banksel _signal_s_base(alias) + _signal_offset(alias)\n\
			bcf _signal_s_base(alias) + _signal_offset(alias), _signal_bit(alias)\n\
		_endasm;\
	}

#define _signal_test(alias...)\
	(_signal_c_base(alias)[_signal_offset(alias)] & (1 << _signal_bit(alias)))

#define _signal_wait(alias...)\
	while (_signal_test(alias) == 0);



#ifdef AUTOMAGIC

#define _signal(pri, alias...)\
	automagic(signal, pri, _signal_c_base(alias), _signal_offset(alias), _signal_bit(alias))

#else

#define _signal(pri, alias...)

#endif


// __signal_c_base(alias)[__signal_offset(alias)] |= (1 << __signal_bit(alias));
// __signal_c_base(alias)[__signal_offset(alias)] &= ~(1 << __signal_bit(alias));


#endif

