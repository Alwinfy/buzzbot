#ifndef _BANG_H
#define _BANG_H

class Bang;

#include "banbuz.h"

class Bang: public BanBuz<5> {
public:
	const char *name() const override;
};

#endif
