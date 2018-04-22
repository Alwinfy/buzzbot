#include "buzzword.h"

#ifndef _SUMP_H
#define _SUMP_H

class Sump: public Buzzword {
public:
	bool get(int);
	const char *name() const;
	const char *desc() const;

protected:
	bool issqr(int);
};

#endif
