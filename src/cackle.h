#ifndef _CACKLE_H
#define _CACKLE_H

class Cackle;

#include "lprime.h"
#include "buzzword.h"

class Cackle: public Buzzword, private LPrime {
public:
	bool get(unsigned) const override;
	
	const char *name() const;
	const char *desc() const;
};

#endif
