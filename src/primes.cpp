#include <cstdio>

#include "crash.h"

int main(int argc, char *argv[])
{
	Crash p;
	int N = 0;
	
	printf("Enter a number: ");
	while(scanf("%d", &N) && (!feof(stdin) || (puts(""), false)))
	{
		printf("%d is ", N);
		fflush(stdout);
		printf("%s\n", (p.get(N) ? "prime" : "not prime"));
//		p->print();
	
		printf("Enter a number: ");
	}
	//for(unsigned x: LPrime::primes) printf("%u\n", x);
	
	return 0;
}
