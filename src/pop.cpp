#include "pop.h"

bool Pop::get(unsigned val) const
{
	if(val < 6)
		return false;
	unsigned n = get_lp(val);
	return val != n && val != n * n && is_prime(val / n);
}

const char *Pop::name() const
{
	static const char *name = "Pop";
	return name;
}

const char *Pop::desc() const
{
	static const char *desc = "equals the product of exactly two distinct primes";
	return desc;
}
