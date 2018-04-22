#include "banbuz.h"

#ifndef _BANG_H
#define _BANG_H

class Bang: public BanBuz {
public:
	bool get(int);
	const char *name() const;
	const char *desc() const;
};

#endif
