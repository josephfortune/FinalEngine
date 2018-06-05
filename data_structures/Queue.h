/* Written by Joseph Fortune 6/4/2017
 * There is no safety checks done here. If you add objects beyond the buffer limit, they will be overwritten.
 * Use with caution */

#ifndef QUEUE_H
#define QUEUE_H

#include <cstdlib>

template <class T>
class Queue 
{
	public:
	Queue(int size) 
	{ 
		head = tail = 0; 
		buffer = (T*)malloc(size * sizeof(T));
		buff_size = size;
	}

	Queue() {}

	void add(T obj)	
	{ 
		buffer[tail] = obj;
		if (++tail >= buff_size)
			tail = 0;
		
	}
	
	T remove()	
	{ 
		int index = head;
		if (++head >= buff_size)
			head = 0;
		return buffer[index]; 
	}	

	bool empty() { return (head == tail); }

	private:
	T *buffer;
	int head, tail, buff_size;
};

#endif

