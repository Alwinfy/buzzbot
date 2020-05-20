#include "cackle.h"

bool Cackle::get(unsigned val) const
{
	if(val < 8)
		return false;
	if(is_prime(val)) return false;
	unsigned cval = 0, oval = 0, count = 0, primes = 0;
	while(val > 1)
	{
		cval = get_lp(val);
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
