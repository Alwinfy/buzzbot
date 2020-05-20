#include <cmath>

#include "sump.h"

bool Sump::get(unsigned val) const
{
	for(unsigned i=0,c=0;c<val;i++,c=i*i*i)
		if(issqr(val-c))
			return true;
	return false;
//	return issqr(val);
}

const char *Sump::name() const
{
	static const char *name = "Sump";
	return name;
}
const char *Sump::desc() const
{
	static const char *desc = "equals the sum of a perfect square and nonnegative perfect cube";
	return desc;
}

bool Sump::issqr(unsigned val) const
{
	for(int i=(sizeof(unsigned)<<2);i>1;i>>=1)
		if(!(val & ((1 << i) - 1)))
			val <<= i;
	
	if(val & 2)
		return false;
	
	unsigned tmp = floor(sqrt(val) + 0.5);
	return tmp * tmp == val;
}
