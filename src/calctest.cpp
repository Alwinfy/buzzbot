#include <vector>
#include <cstdio>
#include <cassert>

#include "all.h"

const int LINE_SIZE = 4096;
const int MAX_QUERY = 10000000;

int main(int argc, char *argv[]) {
	unsigned target, j;
	int *counts = new int[ALL_WORDS.size()];
	assert(argc > 1);
	assert(sscanf(argv[1], "%d", &target));
	printf("%d\n", target);
	for(unsigned i=1; i<=target; i++, j = 0) {
		for(const auto &bw: ALL_WORDS) {
			counts[j++] += bw->get(i);
		}
	}
	j = 0;
	for(const auto &bw: ALL_WORDS)
		printf("%s %d\n", bw->name(), counts[j++]);

	delete[] counts;
	return 0;
}
