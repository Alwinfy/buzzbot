#include "prod.h"

bool Prod::get(int val) // returns whether is prime
{
	int n = 0;
	if(val < 8) return false;
	while((val /= _get(val)) != 1) n++;
	return n && (~n & 1);
}

const char *Prod::name() const
{
	static const char *name = "Prod";
	return name;
}

const char *Prod::desc() const
{
	static const char *desc = "is not prime, but has an odd number of (not necessarily distinct) prime factors";
	return desc;
}
