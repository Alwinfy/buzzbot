#ifndef _ZIP_H
#define _ZIP_H

class Zip;

#include "lprime.h"
#include "buzzword.h"

class Zip: public Buzzword, private LPrime {
public:
	bool get(unsigned) const override;
	
	const char *name() const;
	const char *desc() const;

protected:
	unsigned gcd(unsigned, unsigned) const;
};

#endif
