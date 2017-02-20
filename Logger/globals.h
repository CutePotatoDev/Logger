/*
 * globals.h
 *
 * Created: 2017-01-28 00:19:56
 */ 

#ifndef GLOBALS_H_
#define GLOBALS_H_

//Super nice macros  :O,.
//Macros are fun but still need deep check about performance and speed.

// MACROS FOR EASY PIN HANDLING FOR ATMEL GCC-AVR
//These macros are used indirectly by other macros , mainly for string concatination.
#define _SET(type,name,bit)          type ## name  |= _BV(bit)
#define _CLEAR(type,name,bit)        type ## name  &= ~ _BV(bit)
#define _TOGGLE(type,name,bit)       type ## name  ^= _BV(bit)
#define _GET(type,name,bit)          ((type ## name >> bit) &  1)
#define _PUT(type,name,bit,value)    type ## name = ( type ## name & ( ~ _BV(bit)) ) | ( ( 1 & (unsigned char)value ) << bit )

//These macros are used by end user.
#define OUTPUT(pin)         _SET(DDR,pin)
#define INPUT(pin)          _CLEAR(DDR,pin)
#define HIGH(pin)           _SET(PORT,pin)
#define LOW(pin)            _CLEAR(PORT,pin)
#define TOGGLE(pin)         _TOGGLE(PORT,pin)
#define READ(pin)           _GET(PIN,pin)

#define SET(name,bit)      _SET(,name,bit)
#define CLEAR(name,bit)    _CLEAR(,name,bit)

#endif /* GLOBALS_H_ */