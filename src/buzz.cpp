#include "buzz.h"

const char *Buzz::name() const
{
	static const char *name = "Buzz";
	return name;
}
