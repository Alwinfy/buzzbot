#include "whizz.h"

bool Whizz::get(int val)
{
	int N;
	while(val > 1)
	{
		N = _get(val);
		val /= N;
		if(N > 1 && val % N == 0)
			return false;
		val /= N;
	}
	return true;
}

const char *Whizz::name() const
{
	static const char *name = "Whizz";
	return name;
}
const char *Whizz::desc() const
{
	static const char *desc = "doesn't have any factors that are perfect squares greater than 1";
	return desc;
}
