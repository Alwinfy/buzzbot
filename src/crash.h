#ifndef _CRASH_H
#define _CRASH_H

class Cackle;

#include "lprime.h"
#include "buzzword.h"

class Crash: public Buzzword, private LPrime {
public:
	bool get(unsigned) const override;
	
	const char *name() const;
	const char *desc() const;
};

#endif
