#include "whirr.h"

Whirr::Whirr(): BanBuz(6) {}
const char *Whirr::name() const
{
	static const char *name = "Whirr";
	return name;
}
const char *Whirr::desc() const
{
	static const char *desc = "divides 6 or has the number 6 in its base 10 representation";
	return desc;
}
