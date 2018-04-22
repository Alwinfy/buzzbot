#include "lprime.h"
#include "buzzword.h"

#ifndef _SQUAWK_H
#define _SQUAWK_H

class Squawk: public Buzzword, public LPrime {
public:
	bool get(int);
	
	const char *name() const;
	const char *desc() const;
};

#endif
