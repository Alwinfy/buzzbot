#include "lprime.h"
#include "buzzword.h"

#ifndef _ZIP_H
#define _ZIP_H

class Zip: public Buzzword, public LPrime {
public:
	bool get(int);
	
	const char *name() const;
	const char *desc() const;
protected:
	int gcd(int, int);
};

#endif
