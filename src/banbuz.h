#ifndef _BANBUZ_H
#define _BANBUZ_H

template<unsigned Digit>
class BanBuz;

#include <string>

#include "buzzword.h"

extern bool banbuz_get(unsigned value, unsigned digit);

static const unsigned BANBUZ_BASE = 10;

template<unsigned Digit>
class BanBuz : public Buzzword {
public:
	bool get(unsigned value) const override {
		return banbuz_get(value, Digit);
	}

	
	const char *desc() const override {
		static const std::string desc = ("divides " + std::to_string(Digit) + " or has the number " + std::to_string(Digit) + " in its base " + std::to_string(BANBUZ_BASE) + " representation").c_str();
		return desc.c_str();
	}

};

#endif
