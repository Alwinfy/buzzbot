#ifndef _ZOOB_H
#define _ZOOB_H

class Zoob;

#include "buzzword.h"

class Zoob: public Buzzword {
public:
	bool get(unsigned) const override;
	const char *name() const;
	const char *desc() const;
};

#endif
