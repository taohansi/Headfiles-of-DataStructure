#ifndef VECOTR
#define VECOTR
#define DEFAULT_CAPACITY 10//通过define设置初始容量
//何时的划分数据结构所进行的操作，有些应该交给上层操作
//即上层来保证它的正确性
//#include "../../pq_complHeap/pq_complHeap/pq_complHeap.h"头文件不允许相互包含
template <typename T>
class Vector{
protected:
	int size;
	int capacity;
	T* element;
    void copyFrom(T const*ptr,int lo,int hi){
		capacity=2*(hi-lo);
		element=new T[capacity];
		for(size=0;lo<hi;lo++,size++)
			element[size]=ptr[lo];

	}//通过一个辅助函数来解决
	void swap(T &a, T &b){
		T hold=a;
		a=b;
		b=hold;
	}
	int bubble(int lo,int hi){
		int last=lo;
		for(int i=lo+1;i<hi;i++){//将扫描元素作为前驱，更好地防止越界
			if(element[i-1]>element[i]) {
				swap(element[i-1],element[i]);//稳定的排序算法，当相同元素
				last=i;                       //紧接着便不会交换位置
			}
		}
		return last;
	}
	void merge(int lo,int mi,int hi){
		T* A=new T[mi-lo];
		T* B=element;
        for(int i=0, k=lo;i<mi-lo;i++,k++) A[i]=element[k];
		int p=0; int q=mi; int j=lo;
		while((p<(mi-lo))&&(q<hi)){
			if(A[p]<=B[q]){
               element[j]=A[p];
			   p++;j++;
			}else if(B[q]<A[p]){
				element[j]=B[q];
				q++;j++;
			}
		}
		if(p<(mi-lo)){
			for(int i=p;i<(mi-lo);i++,j++) element[j]=A[i];
		}
		delete []A;
		
	}
	int max(int lo,int hi){
		int min=lo;
		for(int i=lo;i<hi;i++){
			if(element[min]<=element[i]) min=i;
		}
        return min;
	}
	void insert(int lo,int hi,T e){
		int pos=search(e,lo,hi)+1;
		for(int i=hi-1;i>=pos;i--){
			element[i+1]=element[i];
		}
		element[pos]=e;
	}
public:

	Vector( int c=DEFAULT_CAPACITY, int s=0,T v=T()){//容量为c、规模为s、所有元素初始为v
	    capacity=c; size=s;
		element=new T[c];
		for(int i=0;i<size;i++){
			element[i]=v;
	}

}

	Vector(T const*ptr,int n){ copyFrom(ptr,0,n);
	}
	Vector(T const*ptr,int lo,int hi){copyFrom(ptr,lo,hi);
	}
	Vector(Vector<T> &V){copyFrom(V.element,0,V.size);
	}
	Vector(Vector<T> &V, int lo,int hi){copyFrom(V.element,lo,hi);
	}
	~Vector(){delete []element;}
	Vector<T>& operator=(Vector<T> const &V){
		if(element!=NULL) delete []element;
		copyFrom(V.element,0,V.size);
        return *this;
	}
	int getSize() {return size;}
	int getCapacity(){return capacity;}

	T& operator[](int pos){
		return element[pos];
	}//返回引用保证了既能进行左值操作也能进行右值操作
	bool empty(){ if(size!=0) return false;}
	int find(T const &e,int lo,int hi){
		for(int i=hi-1;i>=lo;i--){
			if(element[i]==e)
				return i;//返回秩最大的元素
		}
		return i;//返回的是越过的位置
	}//返回位置
	int find(T const &e){ find(e,0,size);}
	int insert(int pos,T const&e){
		expand();
		for(int i=size-1;i>=pos;i--){
			element[i+1]=element[i];
		}
		element[pos]=e;
		size++;
		return pos;
	}//返回位置
	int insert(T const&e){
		return insert(size,e);
	}
	T remove(int pos){
		T ans=element[pos];
        remove(pos,pos+1);
		return ans;
	}//返回被删除元素
	int remove(int lo, int hi){
		if(hi>size) return -1;
        if(lo==hi) return 0;//单独处理相等的极端情况
		for(;hi<size;lo++,hi++) element[lo]=element[hi];
		size=lo;//考虑跳出时，hi移动到了数据区外，lo也移动了数据区外即size哨兵
		shrink();
		return hi-lo;
	}
	void expand(){
		if(size<capacity) return;//注意判断
		if(capacity<DEFAULT_CAPACITY) capacity=DEFAULT_CAPACITY;//对vector的操作应该依赖于size
		capacity=2*capacity;
		T* ptr=element;//将指针ptr指向element所指的数据区
		element=new T[capacity];
		for(int i=0;i<size;i++) element[i]=ptr[i];
		delete []ptr;

		
	}
	void shrink(){
		if(capacity<2*DEFAULT_CAPACITY) return;
		if(size*4>capacity) return;//以25%为界
		T* ptr=element;
		capacity=capacity/2;//容量减半
		element=new T[capacity];
		for(int i=0;i<size;i++) element[i]=ptr[i];
		delete []ptr;
	}
	void unsort(){ unsort(0,size);}//可以方便的进行测试
	void unsort(int lo,int hi){//置乱器
		for(int i=hi-1;i>=lo;i--){
			swap(element[i],element[rand()%(hi-lo)+lo]);
		}
	}//产生随机向量的一个好方法
	int deduplicate(){//两者相同删除后面的元素
       /* int oldsize=size;
		for(int i=1;i<size;i++){
			int pos=find(element[i],0,i);
			if(pos>=0){remove(pos);i--;}
		}
		return oldsize-size; // 如果不是每次都需要i++用while循环
		                     // 可读性更好*/
	   int oldsize=size;
       int i=1;
	   while(i<size){
		   int pos=find(element[i],0,i);
		   if(pos>=0) remove(i);
		   else i++;
	   }
	   return oldsize-size;
	}//删除重复元素
	template <typename VST >void traverse(VST &visit){//遍历传入函数参数
		for(int i=0;i<size;i++) visit(element[i]);//对其中的每个元素都进行该函数调用
	}
	int disordered(){//返回相邻逆序对的个数
		int sum=0;
		for(int i=0;i<size-1;i++){
			if(element[i]>element[i+1]) sum++;
		}
		return sum;
	}
	int uniquify(){//有序向量删除重复元素，两者相同删除后面的元素
		int i=0;
		int j=1;
		while(j<size){
			if(element[j]!=element[i]){
				element[i+1]=element[j];//不调用删除操作而是直接将元素前移
				i++;
			}
			j++;
		}
		size=i+1;
		shrink();//注意压缩
		return j-size;
	}
	int search(T &e,int lo,int hi){
		/*while(lo<hi){
			int mi=(lo+hi)/2;
			if(e<element[mi]) hi=mi;
			else if(element[mi]<e) lo=mi+1;
			else return mi;
		}
		return -1;// 三次比较版本*/
		while(lo<hi){
            int mi=(lo+hi)/2;
			(e<element[mi])? hi=mi:lo=mi+1;//仍然是分三段区间，但查找两段区间[lo,mi)(mi,hi)
		}//在element[lo==hi]退出，此时为大于e的最小元素
		return lo-1;
	}
	void bubbleSort(){ bubbleSort(0,size);}
	void bubbleSort(int lo,int hi){
		while(lo<bubble(lo,hi)){
			hi=bubble(lo,hi);//hi更新为最后一次交换的过程
		}
	}
	void mergeSort(){ mergeSort(0,size);}
	void mergeSort(int lo,int hi){
		if((hi-lo)==1) return;//if(!(lo<hi)) return;
		int mi=(lo+hi)/2;
		mergeSort(lo,mi);mergeSort(mi,hi);
		merge(lo,mi,hi);
	}
	void selectionSort(){ selectionSort(0,size);}//选择排序
	void selectionSort(int lo,int hi){
		while(lo<hi){
			int pos=max(lo,hi);
			swap(element[hi-1],element[pos]);
			hi--;
		}
	}
	/*void heapSort(){ heapSort(0，size);}
	void heapSort(int lo,int hi){
		PQ_ComplHeap<int> H(element+lo,hi-lo);
		for(int j=hi;j>lo;j--){
			element[j]=H.delMax();
		}

	}*/
	void insertSort(){ insertSort(0,size);}
	void insertSort(int lo,int hi){
		for(int i=lo+1;i<hi;i++){
			insert(lo,i,element[i]);
		}
	}
	void shellSort(){ shellSort(0,size);}
	void shellSort(int lo,int hi){
		int sedgewick[9]={0,1,5,19,41,109,209,505,929};//注意这里只列出了部分序列
		int index=0;int j;
		for(;sedgewick[index+1]<hi;index++);
		for(int D=sedgewick[index];index>0;index--,D=sedgewick[index]){//拿到间隔D
		  for(int i=lo+D;i<hi;i=i+D){//采用快排方式
			int temp=element[i];
			for(j=i-D;temp<element[j];j=j-D){
				element[j+D]=element[j];
			}
			element[j+D]=temp;
		  }
	    }
	}
	
};
	
#endif 