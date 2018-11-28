#include "banbuz.h"

#ifndef _BUZZ_H
#define _BUZZ_H

class Buzz: public BanBuz {
public:
	Buzz();
	const char *name() const;
	const char *desc() const;
};

#endif
