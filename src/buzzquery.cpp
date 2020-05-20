#include <cstdio>
#include <cassert>

#include "all.h"

const int LINE_SIZE = 4096;
const int MAX_QUERY = 10000000;

int main(int argc, char *argv[])
{
	int N, offset, pos;
	size_t len = LINE_SIZE;
	bool running = true, first;
	char query, *line;
	
	line = new char[LINE_SIZE];
	
	setvbuf(stdout, NULL, _IOFBF, 0);
	
	while(running && getline(&line, &len, stdin) != -1)
	{
		pos = 0;
		if(!sscanf(line, "%c %n", &query, &pos)) query = ' ';
		switch(query)
		{
		case 'q':
			running = false;
			break;
		case 'h':
			for(const auto &bw: ALL_WORDS)
				printf("%s %s\n", bw->name(), bw->desc());
			break;
		case 'c':
			first = true;
			while(sscanf(line + pos, "%d %n", &N, &offset) > 0)
			{
				pos += offset;
				if(N <= 0 || N > MAX_QUERY)
				{
					printf("Error ");
					continue;
				}
				if(first)
					first = false;
				else
					putchar(' ');
				for(const auto &bw: ALL_WORDS)
					if(bw->get(N))
						printf("%s", bw->name());
			}
			putchar('\n');
			break;
		default:
			puts("Error");
		}
		fflush(stdout);
	}
	
	return 0;
}
