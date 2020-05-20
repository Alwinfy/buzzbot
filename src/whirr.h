#ifndef _WHIRR_H
#define _WHIRR_H

class Whirr;

#include "banbuz.h"

class Whirr: public BanBuz<6> {
public:
	const char *name() const;
};

#endif
