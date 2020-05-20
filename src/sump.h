#ifndef _SUMP_H
#define _SUMP_H

class Sump;

#include "buzzword.h"

class Sump: public Buzzword {
public:
	bool get(unsigned) const override;
	const char *name() const;
	const char *desc() const;

protected:
	bool issqr(unsigned) const;
};

#endif
