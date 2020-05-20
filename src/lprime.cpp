#include "lprime.h"

// Comment below line out if you're gonna make a single query of large size.
// Below is optimal when you're going to make repeated/incremental queries.
#define LINEAR_LP

std::vector<unsigned>		LPrime::primes		= {
#ifdef LINEAR_LP
	1
#endif
};
std::map<unsigned, unsigned>	LPrime::expect		= {};
unsigned			LPrime::greatest	= 3;

unsigned LPrime::get_lp(unsigned n) const
{
	if(~n & 1) return 2;
	cache_to(n);
#ifdef LINEAR_LP
	return primes[n / 2];
#else
	for(unsigned p: primes) {
		if(n % p == 0)
			return p;
		if(p * p > n) break;
	}
	return n;
#endif
}

bool LPrime::is_prime(unsigned n) const {
	cache_to(n);
	return n != 1 && get_lp(n) == n;
}


void LPrime::cache_to(unsigned n) {
#ifdef LINEAR_LP
	for(; greatest<=n; greatest+=2) {
#else
	for(; greatest*greatest<=n; greatest+=2) {
#endif
		unsigned lp = expect.count(greatest) ? expect[greatest] : greatest;
		expect.erase(greatest);
#ifndef LINEAR_LP
		if(greatest == lp)
#endif
			primes.push_back(lp);
		put_nonprime(lp, greatest + 2 * lp);
	}
}

void LPrime::put_nonprime(unsigned prime, unsigned nonprime) {
	if(expect.count(nonprime)) {
		unsigned oprime = expect[nonprime];
		if(oprime < prime) {
			put_nonprime(prime, 2 * prime + nonprime);
			return;
		}
		expect[nonprime] = prime;
		put_nonprime(oprime, 2 * oprime + nonprime);
	}
	else expect[nonprime] = prime;
}
