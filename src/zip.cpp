#include "zip.h"

bool Zip::get(int val)
{
	if(val < 3)
		return false;
	int perst = 0, cur = 0;
	int cval, oval = 1;
	while(val > 1)
	{
		cval = _get(val);
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

int Zip::gcd(int a, int b)
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
	static const char *desc = "it equals the expression x^y, for integer x and y, and x, y > 2";
	return desc;
}
