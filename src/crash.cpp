#include "crash.h"

bool Crash::get(unsigned val) const
{
	return is_prime(val);
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
