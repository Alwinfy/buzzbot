#include "lprime.h"
#include "buzzword.h"

#ifndef _POP_H
#define _POP_H

class Pop: public Buzzword, public LPrime {
public:
	bool get(int);
	
	const char *name() const;
	const char *desc() const;
};

#endif
