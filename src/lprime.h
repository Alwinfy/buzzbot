#include "array.h"
#include "buzzword.h"

#ifndef _LPRIME_H
#define _LPRIME_H

class LPrime {
public:
	LPrime();
	
	const int _get(const int);
	const int _isp(const int);
private:
	const bool isprime(const int);
	void next();
	
	static Array<int> cache;
};

#endif
