#include "lprime.h"
#include "buzzword.h"

#ifndef _PROD_H
#define _PROD_H

class Prod: public Buzzword, private LPrime {
public:
	bool get(int);
	
	const char *name() const;
	const char *desc() const;
};

#endif
