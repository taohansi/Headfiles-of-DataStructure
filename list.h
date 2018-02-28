#ifndef LIST
#define LIST
#define listNodePos(T) listNode<T>*//ͳһ���õ�ַ��ʽ���Ӽ��
#include "../../algorithm/algorithm/algorithm.h"
template <typename T> struct listNode{
	T data;
	listNodePos(T) pred;
	listNodePos(T) succ;
	listNode(){
	}//����ͷβָ��ʱӦ��
	listNode(T e,listNodePos(T) p=NULL,listNodePos(T) s=NULL){
		data=e;
		pred=p;
		succ=s;
	}
	listNodePos(T) insertAsPred (T const &e){
		listNodePos(T) x=new listNode(e,pred,this);//�����½ڵ�
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
	listNodePos(T) header;//�ڱ�
	listNodePos(T) tailer;//ע���ʱֻ����������û�д���
protected:
	void init(){
		header=new listNode<T>;//new���ص��ǵ�ַ��ָ�룩
		tailer=new listNode<T>;
		header->succ=tailer;
		tailer->pred=header;
		size=0;   
	}
	int clear(){
		int oldSize=size;
		while(size!=0) remove(first());//����Ҫsize-- size����remove����
        return oldSize;
	}
	void copyNodes(listNodePos(T) p,int n){//���ư���p�ļ���֮��n��Ԫ��
		init();
		for(;n>0;n--){
			insertAsLast(p->data);
			p=p->succ;
		}
	}
public:
	List(){ init(); }
	~List(){ clear();delete header; delete tailer;}
	List(List<T> &L){ copyNodes(L.first(),L.size);}//header->succ ��Ȼ���Ե��ṩ��first�ӿ�
	List(List<T> &L,int pos,int n){copyNodes(L[pos],n);}
	List(listNodePos(T) p,int n){ copyNodes(p,n);}
	List(T* ptr,int n){
		init();
		for(int i=0;i<n;i++) insertAsLast(ptr[i]);
	}
	int getSize(){ return size;}
	bool empty(){ return size<=0;}//����һ���пձ��ʽ
	listNodePos(T) first(){ return header->succ;}//�����׽ڵ�
	listNodePos(T) last() { return tailer->pred;}
	T& operator[](int pos){
		listNodePos(T) fir=first();
		for(int i=0;i<pos;i++){
			fir=fir->succ;
		}
		return fir->data;
	}
	listNodePos(T) find(T const &e){ return find(e,size,tailer);}
	listNodePos(T) find(T const &e,int n,listNodePos(T) p){//Ѱ��ǰ��n��Ԫ���Ƿ���e
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
	int deduplicate(){//����ȥ��
		int oldSize=size;
		listNodePos(T) p=first();
		for(int i=0;i<size;p=p->succ){
			listNodePos(T) q=find(p->data,i,p);
			if(q!=NULL) remove(q);//size--; ע�Ⲣ����Ҫ����Ϊɾ�������Ĵ�С�����Ѿ�������remove	
			else i++;//ע��ǰ�����������˱仯
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
	listNodePos(T) search(T const&e,int n,listNodePos(T) p){//���ز���������Ԫ�أ�Խ��ʱ���ؽ�ǰԪ��
		for(int i=0;i<n;i++){
			p=p->pred;
			if(p->data<=e) return p;
		}
		return p->pred;
	}
	void reverse(){//��Ϊ˫������ĵ�Ե��Ҳ����ͷ�������м�ƽ�
		listNodePos(T) p=first()->succ;//Ҳ�ɲ��������ݣ��ı�������ע����Ҫ�����ڱ�
		for(int i=1;i<size;i++){
			insertAsFirst(p->data);
			listNodePos(T) q=p->succ;
			remove(p);
			p=q;//p��ָ�����������ͷţ���p������Ȼ�Ǵ��ڵ�
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