#ifndef _LPRIME_H
#define _LPRIME_H

class LPrime;

#include <vector>
#include <map>

#include "buzzword.h"

class LPrime {
public:
	unsigned get_lp(unsigned n) const;
	bool is_prime(unsigned n) const;
	static std::vector<unsigned>		primes;

private:
	static void cache_to(unsigned);
	static void put_nonprime(unsigned, unsigned);

	static std::map<unsigned, unsigned>	expect;
	static unsigned				greatest;
};

#endif
