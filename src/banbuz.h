#include "buzzword.h"

#ifndef _BANBUZ_H
#define _BANBUZ_H

class BanBuz: public Buzzword {
public:
	bool get(int);
protected:
	BanBuz(int);
	int digit;
};

#endif
