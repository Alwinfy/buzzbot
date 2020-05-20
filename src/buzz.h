#ifndef _BUZZ_H
#define _BUZZ_H

class Buzz;

#include "banbuz.h"

class Buzz: public BanBuz<7> {
public:
	const char *name() const override;
};

#endif
