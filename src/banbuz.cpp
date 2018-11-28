#include "banbuz.h"

BanBuz::BanBuz(int d): digit(d) {}
bool BanBuz::get(int val)
{
	if(val < 0)
		val = -val;
	if(val % digit == 0)
		return true;
	do
		if(val % 10 == digit)
			return true;
	while(val /= 10);
	return false;
}
