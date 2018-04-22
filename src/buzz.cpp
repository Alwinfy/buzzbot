#include "buzz.h"

bool Buzz::get(int n)
{
	return BanBuz::_get(n, 7);
}
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
