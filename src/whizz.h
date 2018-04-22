#include "lprime.h"
#include "buzzword.h"

#ifndef _WHIZZ_H
#define _WHIZZ_H

class Whizz: public Buzzword, public LPrime {
public:
	bool get(int);
	
	const char *name() const;
	const char *desc() const;
};

#endif
