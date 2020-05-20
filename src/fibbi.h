#ifndef _FIBBI_H
#define _FIBBI_H

class Fibbi;

#include <vector>

#include "buzzword.h"

class Fibbi: public Buzzword {
public:
	bool get(unsigned) const override;
	const char *name() const;
	const char *desc() const;

protected:
	static std::vector<unsigned> fibbi_cache;
};

#endif
