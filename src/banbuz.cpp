#include "banbuz.h"

bool banbuz_get(unsigned value, unsigned digit) {
	if(value % digit == 0) return true;
	do {
		if(value % BANBUZ_BASE == digit)
			return true;
		value /= BANBUZ_BASE;
	} while(value);
	return false;
}
