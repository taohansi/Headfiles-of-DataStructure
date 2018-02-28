#ifndef QUEUE
#define QUEUE
#include "../../list/list/list.h"
template <typename T> class Queue :public List<T>{
public:
	void enqueue(T &e){insertAsLast(e);}
	T dequeue(){ return remove(first());}
	T& front(){ return first()->data;}
	T& rear() { return last()->data;}
};
#endif