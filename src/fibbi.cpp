#include "fibbi.h"

Fibbi::Fibbi()
{
	fibbies.insert(0);
	fibbies.insert(1);
}

bool Fibbi::get(int val)
{
	while(fibbies[-1] < val)
		fibbies.insert(fibbies[-1] + fibbies[-2]);
	return s.bsearch(&fibbies, val) != NULL;
}

const char *Fibbi::name() const
{
	static const char *name = "Fibbi";
	return name;
}

const char *Fibbi::desc() const
{
	static const char *desc = "is a Fibonacci number";
	return desc;
}
