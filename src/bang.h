#include "banbuz.h"

#ifndef _BANG_H
#define _BANG_H

class Bang: public BanBuz {
public:
	Bang();
	const char *name() const;
	const char *desc() const;
};

#endif
