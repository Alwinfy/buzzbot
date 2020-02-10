#include "lprime.h"
#include "buzzword.h"

#ifndef _CACKLE_H
#define _CACKLE_H

class Cackle: public Buzzword, public LPrime {
public:
	bool get(int);
	
	const char *name() const;
	const char *desc() const;
};

#endif
