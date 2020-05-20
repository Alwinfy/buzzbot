#include <algorithm>

#include "fibbi.h"

std::vector<unsigned> Fibbi::fibbi_cache{0, 1};

bool Fibbi::get(unsigned val) const
{
	while(fibbi_cache.back() < val)
		fibbi_cache.push_back(fibbi_cache.back() + fibbi_cache[fibbi_cache.size() - 2]);
	return std::binary_search(fibbi_cache.begin(), fibbi_cache.end(), val);
}

const char *Fibbi::name() const
{
	static const char *name = "Fibbi";
	return name;
}

const char *Fibbi::desc() const
{
	static const char *desc = "is a Fibonacci number";
	return desc;
}
