

#ifndef __THUNK_H
#define __THUNK_H


#ifdef AUTOMAGIC
#define _thunk_alloc(name) automagic(thunk_alloc,   name)
#define _thunk(pri, func)  automagic(thunk_connect, pri, func)
#else
#define _thunk_alloc(name) extern void _thunk_##name()
#define _thunk(pri, func)
#endif

#define _thunk_call(name) _thunk_##name()


#endif

