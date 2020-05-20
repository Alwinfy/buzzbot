#include "zip.h"

bool Zip::get(unsigned val) const
{
	if(val < 3)
		return val == 1;
	unsigned perst = 0, cur = 0;
	unsigned cval, oval = 1;
	while(val > 1)
	{
		cval = get_lp(val);
		if(cval != oval)
		{
			perst = gcd(cur, perst);
			cur = 0;
			oval = cval;
		}
		val /= cval;
		cur++;
	}
	return gcd(cur, perst) > 1;
}

unsigned Zip::gcd(unsigned a, unsigned b) const
{
	if(b == 0)
		return a;
	return gcd(b, a % b);
}

const char *Zip::name() const
{
	static const char *name = "Zip";
	return name;
}
const char *Zip::desc() const
{
	static const char *desc = "equals the expression x^y, for unsignedeger x and y, x > 0, y > 1";
	return desc;
}
