#include "crash.h"

bool Crash::get(int val) // returns whether is prime
{
	return _isp(val);
}

const char *Crash::name() const
{
	static const char *name = "Crash";
	return name;
}

const char *Crash::desc() const
{
	static const char *desc = "is prime";
	return desc;
}
