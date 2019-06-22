// array.h - header definitions for Array

#include "error.h"

#define DEF_BUFSIZE 256

#ifndef _ARRAY_H
#define _ARRAY_H

template<class T> class Array {
public:
	T &operator[](int) const;
	T *operator+(int) const;
	
	Array(const int = 0, const int = 0);
	~Array();
	
	void readt(T *, T &); // reads until a terminator matches
	void readc(T *, const int); // reads a certain count
	
	void set(const T &, int);
	const T &get(int = -1) const;
	const T *begin() const;
	const T *end() const;
	
	void insert(const T &, int = -1);
	void remove(int = -1);
	
	const int size() const;
#ifdef DEBUG
	void print() const;
#endif
	
protected:
	int count;
	T *data;
	
private:
	int cbuf;
	int bufsize;
	
	void reallocate();
	void check(int &) const;
};

// since it's a template, this is fine
template<class T> Array<T>::Array(const int init_size, const int buffer): bufsize(buffer) // creates the array
{
	if(bufsize <= 0)
		bufsize = DEF_BUFSIZE;
	
	count = init_size;
	data = NULL;
	cbuf = 0;
	
	while(cbuf <= count)
		reallocate();
	
}
template<class T> Array<T>::~Array() // deletes the array
{
	delete[] data;
}
template<class T> void Array<T>::reallocate()
{
	cbuf += bufsize;
#ifdef DEBUG
//	printf("Reallocating array with new size %d... ", cbuf);
#endif
	T *newdata = new T[cbuf];
	for(int i=0;i<count;i++)
		newdata[i] = data[i];
	if(data)
		delete data;
	data = newdata;
#ifdef DEBUG
//	printf("done.\n");
#endif
}

// bulk init functions
template<class T> void readt(T *arr, T &term)
{
	if(arr == NULL)
		error("Array::readt was passed a null pointer!");
	while(*arr != term)
		insert(*(arr++), -1);
}
template<class T> void readc(T *arr, const int count)
{
	if(arr == NULL)
		error("Array::readt was passed a null pointer!");
	for(int i=0;i<count;i++)
		insert(*(arr++), -1);
}

// non-lengthmod functions
template<class T> const T &Array<T>::get(int index) const
{
	check(index);
	return data[index];
}
template<class T> void Array<T>::set(const T &datum, int index)
{
	check(index);
	data[index] = datum;
}
template<class T> const T *Array<T>::begin() const
{
	return data;
}
template<class T> const T *Array<T>::end() const
{
	return data + count;
}

// lengthmod functions
template<class T> void Array<T>::insert(const T &datum, int index)
{
	count++;
	check(index);
	if(count >= cbuf)
		reallocate();
	
	for(int i = count; i > index; i--)
		data[i] = data[i - 1];
	data[index] = datum;
}
template<class T> void Array<T>::remove(int index)
{
	check(index);
	count--;
	
	for(int i = index; i < count; i++)
		data[i] = data[i + 1];
}

// where the heck does this go
template<class T> const int Array<T>::size() const
{
	return count;
}
#ifdef DEBUG
template<class T> void Array<T>::print() const
{
	for(int i=0;i<count;i++)
		printf(" %d", data[i]);
	printf("\n");
}
#endif

// checc function
template<class T> void Array<T>::check(int &index) const
{
	if(index >= count || index < -count)
		error("Array access attempted at %d with array size %d", index, count);
	if(index < 0)
		index += count;
}

template<class T> T &Array<T>::operator[](int index) const
{
	check(index);
	return data[index];
}

template<class T> T *Array<T>::operator+(int index) const
{
	check(index);
	return data + index;
}

#endif
