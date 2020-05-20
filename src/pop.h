#ifndef _POP_H
#define _POP_H

class Pop;

#include "lprime.h"
#include "buzzword.h"

class Pop: public Buzzword, private LPrime {
public:
	bool get(unsigned) const override;
	
	const char *name() const;
	const char *desc() const;
};

#endif
