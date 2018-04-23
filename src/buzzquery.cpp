#include <cstdio>
#include <cassert>

#include "all.h"

const int LINE_SIZE = 4096;
const int MAX_QUERY = 1000000;

int main(int argc, char *argv[])
{
	int N, offset, pos, i;
	size_t len = LINE_SIZE;
	bool running = true, first;
	char query, *line;
	
	Buzzword *list[] = NEW_ALL;
	line = new char[LINE_SIZE];
	
	setvbuf(stdout, NULL, _IOFBF, 0);
	
	while(running && getline(&line, &len, stdin) != -1)
	{
		pos = 0;
		assert(sscanf(line, "%c %n", &query, &pos));
		switch(query)
		{
		case 'q':
			running = false;
			break;
		case 'h':
			for(i=0;list[i];i++)
				printf("%s %s\n", list[i]->name(), list[i]->desc());
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
				for(i=0;list[i];i++)
					if(list[i]->get(N))
						printf("%s", list[i]->name());
			}
			putchar('\n');
			break;
		default:
			puts("Error");
		}
		fflush(stdout);
	}
	
	for(i=0;list[i];i++)
		delete list[i];
	delete[] line;
	
	return 0;
}
