#include "cackle.h"

bool Cackle::get(int val)
{
	if(val < 8)
		return false;
	if(_get(val) == val) return false;
	int cval = 0, oval = 0, count = 0, primes = 0;
	while(val > 1)
	{
		cval = _get(val);
		if(cval != oval)
		{
			primes += (count & 1);
			count = 0;
			oval = cval;
		}
		val /= cval;
		count++;
	}
	return (count & 1) + primes == 1;
}

const char *Cackle::name() const
{
	static const char *name = "Cackle";
	return name;
}
const char *Cackle::desc() const
{
	static const char *desc = "is the product of a square greater than 1 and a prime";
	return desc;
}
