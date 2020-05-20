#ifndef _WHIZZ_H
#define _WHIZZ_H

class Whizz;

#include "lprime.h"
#include "buzzword.h"

class Whizz: public Buzzword, private LPrime {
public:
	bool get(unsigned) const override;
	
	const char *name() const;
	const char *desc() const;
};

#endif
