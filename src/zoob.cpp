#include "zoob.h"

bool Zoob::get(unsigned val) const
{
	return val % 11 == 7;
}

const char *Zoob::name() const
{
	static const char *name = "Zoob";
	return name;
}

const char *Zoob::desc() const
{
	static const char *desc = "is equivalent to 7, modulo 11";
	return desc;
}
