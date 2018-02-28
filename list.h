#ifndef LIST
#define LIST
#define listNodePos(T) listNode<T>*//统一采用地址形式更加简洁
#include "../../algorithm/algorithm/algorithm.h"
template <typename T> struct listNode{
	T data;
	listNodePos(T) pred;
	listNodePos(T) succ;
	listNode(){
	}//创建头尾指针时应用
	listNode(T e,listNodePos(T) p=NULL,listNodePos(T) s=NULL){
		data=e;
		pred=p;
		succ=s;
	}
	listNodePos(T) insertAsPred (T const &e){
		listNodePos(T) x=new listNode(e,pred,this);//创建新节点
		pred->succ=x;
		this->pred=x;
		return x;
	}
	listNodePos(T) insertAsSucc(T const &e){
		listNodePos(T) x=new listNode(e,this,succ);
		succ->pred=x;
		this->succ=x;
		return x;
	}
};

template <typename T> class List{
private:
	int size;
	listNodePos(T) header;//哨兵
	listNodePos(T) tailer;//注意此时只是声明，并没有创建
protected:
	void init(){
		header=new listNode<T>;//new返回的是地址（指针）
		tailer=new listNode<T>;
		header->succ=tailer;
		tailer->pred=header;
		size=0;   
	}
	int clear(){
		int oldSize=size;
		while(size!=0) remove(first());//不需要size-- size交给remove处理
        return oldSize;
	}
	void copyNodes(listNodePos(T) p,int n){//复制包括p的及其之后n个元素
		init();
		for(;n>0;n--){
			insertAsLast(p->data);
			p=p->succ;
		}
	}
public:
	List(){ init(); }
	~List(){ clear();delete header; delete tailer;}
	List(List<T> &L){ copyNodes(L.first(),L.size);}//header->succ 当然可以但提供了first接口
	List(List<T> &L,int pos,int n){copyNodes(L[pos],n);}
	List(listNodePos(T) p,int n){ copyNodes(p,n);}
	List(T* ptr,int n){
		init();
		for(int i=0;i<n;i++) insertAsLast(ptr[i]);
	}
	int getSize(){ return size;}
	bool empty(){ return size<=0;}//返回一个判空表达式
	listNodePos(T) first(){ return header->succ;}//访问首节点
	listNodePos(T) last() { return tailer->pred;}
	T& operator[](int pos){
		listNodePos(T) fir=first();
		for(int i=0;i<pos;i++){
			fir=fir->succ;
		}
		return fir->data;
	}
	listNodePos(T) find(T const &e){ return find(e,size,tailer);}
	listNodePos(T) find(T const &e,int n,listNodePos(T) p){//寻找前驱n个元素是否有e
		for(;n>0;n--){
			p=p->pred;
			if((p->data)==e) return p;
		}
		return NULL;
	}
	listNodePos(T) insertBefore(listNodePos(T) p,T const &e){
		size++;
		return p->insertAsPred(e);
	}
	listNodePos(T) insertAfter(listNodePos(T) p,T const &e){
		size++;
		return p->insertAsSucc(e);
	}
	listNodePos(T) insertAsFirst(T const&e){
		size++;
		return header->insertAsSucc(e);
	}
	listNodePos(T) insertAsLast(T const&e){
		size++;
		return tailer->insertAsPred(e);
	}
	T remove(listNodePos(T) p) {
		T e=p->data;
		p->pred->succ=p->succ;
		p->succ->pred=p->pred;
		delete p;
		size--;
		return e;
	}
	int deduplicate(){//无序去重
		int oldSize=size;
		listNodePos(T) p=first();
		for(int i=0;i<size;p=p->succ){
			listNodePos(T) q=find(p->data,i,p);
			if(q!=NULL) remove(q);//size--; 注意并不需要，因为删除操作的大小处理已经交给了remove	
			else i++;//注意前驱个数发生了变化
		}
		return oldSize-size;

	}
	template <typename VST> void traverse( VST &visit){
		listNodePos(T) p=first();
		for(int i=0;i<size;i++){
			visit(p->data);
			p=p->succ;
		}
	}
	int uniquify(){
		int oldSize=size;
		listNodePos(T) p=first();listNodePos(T) q;
		for(int i=0;i<size;){
			q=p->succ;
			if(q->data==p->data) remove(q);
			else{ p=p->succ;i++;}
		}
		return oldSize-size;
	}
	listNodePos(T) search(T const&e,int n,listNodePos(T) p){//返回不大于它的元素，越界时返回界前元素
		for(int i=0;i<n;i++){
			p=p->pred;
			if(p->data<=e) return p;
		}
		return p->pred;
	}
	void reverse(){//因为双向链表的的缘故也可两头交换往中间逼近
		listNodePos(T) p=first()->succ;//也可不交换数据，改变链表方向，注意需要交换哨兵
		for(int i=1;i<size;i++){
			insertAsFirst(p->data);
			listNodePos(T) q=p->succ;
			remove(p);
			p=q;//p所指的数据区被释放，但p变量仍然是存在的
		}
	}
	void insertSort(){ insertSort(first(),size);}
	void insertSort(listNodePos(T) p,int n){
		p=p->succ;listNodePos(T) q;
		for(int i=1;i<n;i++){
			insertAfter(search(p->data,i,p),p->data);
			q=p->succ;
			remove(p);
			p=q;
		}
	}
};
#endif