#ifndef PRIORITYQUEUE
#define PRIORITYQUEUE
template <typename T> struct PQ{
	virtual void insert(T)=0;//注意应该是将词条进行插入，而采用比较时，因为比较的重载，会将词条的优先级进行比较
	virtual T getMax()=0;//仅仅只有栈顶这一个入口进行操作
	virtual T delMax()=0;
};
#endif