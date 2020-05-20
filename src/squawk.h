#ifndef _SQUAWK_H
#define _SQUAWK_H

class Squawk;

#include "lprime.h"
#include "buzzword.h"

class Squawk: public Buzzword, private LPrime {
public:
	bool get(unsigned) const override;
	
	const char *name() const;
	const char *desc() const;
};

#endif
