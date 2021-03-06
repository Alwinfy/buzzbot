#ifndef _PROD_H
#define _PROD_H

class Prod;

#include "lprime.h"
#include "buzzword.h"

class Prod: public Buzzword, private LPrime {
public:
	bool get(unsigned) const override;
	
	const char *name() const;
	const char *desc() const;
};

#endif
