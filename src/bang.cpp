#include "bang.h"

bool Bang::get(int n)
{
	return BanBuz::_get(n, 5);
}
const char *Bang::name() const
{
	static const char *name = "Bang";
	return name;
}
const char *Bang::desc() const
{
	static const char *desc = "divides 5 or has the number 5 in its base 10 representation";
	return desc;
}
