#include <cstdio>
#include <cstdlib>
#include <cstdarg>

#include "error.h"

void error(const char *str, ...)
{
	va_list args;
	va_start(args, str);
	fprintf(stderr, "Error: ");
	vfprintf(stderr, str, args);
	fprintf(stderr, "\n");
	va_end(args);
	exit(-1);
}

