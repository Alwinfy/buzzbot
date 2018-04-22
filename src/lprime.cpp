#include "lprime.h"
//#include <cstdio>

Array<int> LPrime::cache = Array<int>();

LPrime::LPrime()
{
	if(cache.size() == 0)
		cache.insert(2);
}


const bool LPrime::isprime(const int n)
{
	for(int i=0;i<cache.size();i++)
	{
		if(n == cache[i])
			return true;
		if(n % cache[i] == 0)
			return false;
		if(cache[i] > n)
			break;
	}
	return true;
}

const int LPrime::_isp(const int val)
{
	if(val < 2)
		return false;
	return _get(val) == val;
}

const int LPrime::_get(const int val)
{
	for(int c = 1 + cache[-1]; val > cache[-1] * cache[-1];c++)
		if(isprime(c))
			cache.insert(c);
//	printf("Cache is currently"); for(int i=0;i<cache.size();i++) printf(" %d", cache[i]); puts("");
	for(int i=0;cache[i]*cache[i]<=val;i++)
		if(val % cache[i] == 0)
			return cache[i];
	return val;
}
