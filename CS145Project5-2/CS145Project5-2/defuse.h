/**
 * defuse.h
 */

#ifndef _DEFUSE_H_
#define _DEFUSE_H_
#include "avr.h"

#define LOWER_WIRES 2
#define UPPER_WIRES_P1 7

unsigned char CheckWires();
void defuse_init();

#endif /* _DEFUSE_H_ */