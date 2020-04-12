#include "banbuz.h"

#ifndef _WHIRR_H
#define _WHIRR_H

class Whirr: public BanBuz {
public:
	Whirr();
	const char *name() const;
	const char *desc() const;
};

#endif
