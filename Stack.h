#ifndef STACK
#define STACK
#include "../../list/list/list.h"
template <typename T> class Stack:public List<T>{
public:
	void push(T & e){ insertAsLast(e);}
	T pop(){ return remove(last());}
	T& top(){ return last()->data;}
	//bool empty(){ return getSize()==0;}ע��̳���empty,getSize��һϵ�нӿ�
	//Ҳ�ɲ���list��

};
#endif