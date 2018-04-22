#include "buzzword.h"
#include "searcher.h"

#ifndef _FIBBI_H
#define _FIBBI_H

class Fibbi: public Buzzword {
public:
	Fibbi();
	bool get(int);
	const char *name() const;
	const char *desc() const;

protected:
	Array<int> fibbies;
	Searcher<int> s;
};

#endif
