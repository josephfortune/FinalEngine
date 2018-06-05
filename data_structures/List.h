/* Written by Joseph Fortune 6/4/2017
 * There is no safety checks done here. If you add objects beyond the buffer limit, it will overflow.
 * Use with caution */

/* List is just a collection of objects that can be traversed by index, but order doesn't matter. After an add/remove operation,
   There is no garantee of where an object will be. */
#ifndef LIST_H
#define LIST_H

#include <cstdlib>

template <class T>
class List 
{
	public:
	List(int size) 
	{ 
		n = 0; 
		buffer = (T*)malloc(size * sizeof(T));
	}

	~List()	{ free(buffer);	}

	void add(T obj)
	{
		buffer[n] = obj;
		n++;
	}
	
	void remove(int index)
	{
		buffer[index] = buffer[n-1];
		n--;
	}

	T *buffer;
	int n;
};

#endif

