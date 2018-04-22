#include "pop.h"

bool Pop::get(int val)
{
	if(val < 6)
		return false;
	int n = _get(val);
	return val != n && val != n * n && _isp(val / n);
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
