#include "lprime.h"
#include "buzzword.h"

#ifndef _CRASH_H
#define _CRASH_H

class Crash: public Buzzword, private LPrime {
public:
	bool get(int);
	
	const char *name() const;
	const char *desc() const;
};

#endif
