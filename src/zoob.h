#include "buzzword.h"

#ifndef _ZOOB_H
#define _ZOOB_H

class Zoob: public Buzzword {
public:
	Zoob();
	bool get(int);
	const char *name() const;
	const char *desc() const;
};

#endif
