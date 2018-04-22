#include "array.h"

#ifndef _SEARCHER_H
#define _SEARCHER_H

template<class T> class Searcher {
public:
	const T *lsearch(const Array<T> *, const T) const;
	const T *bsearch(const Array<T> *, const T) const; // WARNING: assumes already sorted
};

template<class T> const T *Searcher<T>::lsearch(const Array<T> *array, const T term) const
{
	for(int i=0;i<array->size();i++)
		if(term == (*array)[i])
			return (*array) + i;
	return NULL;
}

template<class T> const T *Searcher<T>::bsearch(const Array<T> *array, const T term) const
{
	int	top	= array->size(),
		bottom	= 0,
		mid;
	
	while(top != bottom)
	{
		mid = (top + bottom) / 2;
#ifdef DEBUG
//		printf("Top at %d, bottom at %d, mid at %d\n", top, bottom, mid);
#endif
		if((*array)[mid] == term)
			return (*array) + mid;
		if((*array)[mid] < term)
			bottom = mid + 1;
		else
			top = mid;
	}
	return NULL;
}

#endif
