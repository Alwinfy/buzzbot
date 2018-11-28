#include "buzz.h"

Buzz::Buzz(): BanBuz(7) {}
const char *Buzz::name() const
{
	static const char *name = "Buzz";
	return name;
}
const char *Buzz::desc() const
{
	static const char *desc = "divides 7 or has the number 7 in its base 10 representation";
	return desc;
}
