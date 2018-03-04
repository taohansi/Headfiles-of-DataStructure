#ifndef PQ_COMPLHEAP
#define PQ_COMPLHEAP
#include "../../vector/vector/vector.h"
#include "../../pq/pq/pq.h"
#include "../../algorithm/algorithm/algorithm.h"
template <typename T> class PQ_ComplHeap: public Vector<T>, public PQ<T>{//最大堆
protected:
	int Parent(int i){ return (i-1)/2;}
	int LChild(int i){ return 2*i+1;}
	int RChild(int i){ return 2*i+2;}
	bool parentValid(int i){ return i>0;}
	bool LChildValid(int i){ return inHeap(LChild(i));}
	bool RChildValid(int i){ return inHeap(RChild(i));}
	bool inHeap(int i){ return (i>=0)&&(i<size);}
	int properParent(int i){
		int lc=0; int rc=0;
		if(LChildValid(i)) lc=LChild(i);
		if(RChildValid(i)) rc=RChild(i);
		int index=i;
		if(lc&&(element[index]<element[lc])) index=lc;
		if(rc&&(element[index]<element[rc])) index=rc;
		return index;		
	}
	int percolateDown(int i){//对前n个元素的第i个元素开始下滤
		T temp=element[i];
		int j=properParent(i);
		while(i!=j){//这里之所以可以省掉到尾的条件，是因为这两个条件重合,注意写法
			Swap(element[i],element[j]);
			i=j;//更新i,j
			j=properParent(i);
		}
		return i;
	}
	int percolateUp(int i){
		int j=-1;
		T temp=element[i];
		while(parentValid(i)){
			j=Parent(i);
			if(element[j]>=temp) break;
			element[i]=element[j];
			i=j;
		}
		element[i]=temp;
		return i;//返回停止的地点
	}
	void heapify(int n){
		int ineral=(size-2)/2;
		for(int i=ineral;i>=0;i--)
			percolateDown(i);//O(T)=2O(T/2)+log(n);
	}
public:
	PQ_ComplHeap(T* a,int n){
		copyFrom(a,0,n);
		heapify(n);
	}
	virtual void insert(T e){
		Vector<T>::insert(e);//当类中有同名的函数时采用类名加::来进行区分
		percolateUp(size-1);
	}
	T getMax(){ return element[0];}
	T delMax(){
		T temp=element[0];
		element[0]=element[--size];
		percolateDown(0);
	    return temp;

	}
};
#endif