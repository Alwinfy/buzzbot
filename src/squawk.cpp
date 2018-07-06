#include "squawk.h"

bool Squawk::get(int val)
{
	int oldp = 1, newp, count = 0;
	if(val == 0) return true;
	while(~val & 1)
		val >>= 1;
	while(val > 1)
	{
		newp = _get(val);
		if(oldp != newp)
		{
			if((count & 1) && (oldp & 2))
				return false;
			count = 0;
			oldp = newp;
		}
		count++;
		val /= newp;
	}
	return !((count & 1) && (oldp & 2));
}

const char *Squawk::name() const
{
	static const char *name = "Squawk";
	return name;
}

const char *Squawk::desc() const
{
	static const char *desc = "equals the sum of two (not necessarily distinct) nonnegative perfect squares";
	return desc;
}
