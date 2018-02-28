#ifndef BINNODE
#define BINNODE
#define BinNodePos(T) BinNode<T>*
#include "../../Stack/Stack/Stack.h"
#include "../../queue/queue/queue.h"
//typedef enum{ RB_RED,RB_BLACK} RBColor;
/*template <typename T> int stature(BinNodePos(T) p){
	if(p) return p->height;
	else return -1;
}//���ź�û�а취�������ൽBinNode�У���Ϊ-1��Ӧ�����ǿսڵ�*///���ܷ���֮ǰBinNodeδ����
template <typename T> struct BinNode{
	T data;
	BinNodePos(T) parent;BinNodePos(T) lc;BinNodePos(T) rc;
	int height;
	//int npl;
	//RBColor color;
	BinNode(){ parent=NULL;lc=NULL;rc=NULL;height=0;}
	BinNode(T e,BinNodePos(T) p=NULL,BinNodePos(T) l=NULL,BinNodePos(T) r=NULL,int h=0){
		data=e;
		parent=p;
		lc=l;
		rc=r;
		height=h;
	}
	int size(){//���ذ�����ǰ�ڵ�������Ľڵ�ĸ���
		int s=1;
		if(lc) s+=lc->size();//�ݹ��¼���������ڵ�ĸ���
		if(rc) s+=rc->size();//�ݹ������������Ů��Ϊ��ʱ����1
		return s;
	}
	bool isRoot(){ 
		if(parent) return false;
		else       return true;
	}
	bool isRightChild(){
		if((parent!=NULL)&&(this==parent->rc)) return true;
		else                                  return false;
	}
	bool isLeftChild(){
        if((parent!=NULL)&&(this==parent->lc)) return true;
		else                                  return false;
	}
	bool hasParent(){ return !isRoot()}
	bool hasChild(){ if(lc||rc) return true;else return false;}
	bool hasBothChild(){ if(lc&&rc) return true;else return false;}
	bool hasLeftChild(){ if(lc) return true;else return false;}
	bool hasRightChild(){ if(rc) return true;else return false;}
	bool isLeaf(){ return !hasChild()}

	bool balanced(){
		return stature(rc)==stature(lc);
	}
	int balFactor(){
		return stature(lc)-stature(rc);
	}
	bool avlBalanced(){
		if( (balFactor()<=1)&&(balFactor()>=-1) ) return true;
		else return false;

	}
	BinNodePos(T)& sibling(){ 
		if(isLeftChild())  return parent->rc;
		else               return parent->lc;
	}
	BinNodePos(T)& uncle(){
		if(parent.isLeftChild()) return parent->parent->rc;
		else                     return parent->parent->lc;
	}
	BinNodePos(T)& fromParentTo(){
			if(isRightChild()) return parent->rc;
			if(isLeftChild())  return parent->lc;
	}

	BinNodePos(T)& tailerChild(){//������������ȼ�����
		if(stature(lc)<stature(rc)) return rc;
		else if(stature(rc)<stature(lc)) return lc;
		else {
		if(hasLeftChild()) return lc;
		else if(hasRightChild()) return rc;
		}
	}
	BinNodePos(T) insertAsLC(T const &e){ return lc=new BinNode(e,this);}//�����һ��˫������
	BinNodePos(T) insertAsRC(T const &e){ return rc=new BinNode(e,this);}
	BinNodePos(T) succ(){
		BinNodePos(T) s=new BinNode<T>;
		if(rc){//�������������
			s=rc;
			while(s->hasLeftChild()){//����Ϊs������ʱ������sΪ��
				s=s->lc;
			}
		}
		else{
			s=this;
			while(s->isRightChild()){//����������
				s=s->parent;
			}
			s=s->parent;//������һ��
		}
		return s;
	}
	template <typename VST> void travelPre(BinNodePos(T) p,VST &visit){//�����ڽڵ������һ����
       /*if(!p) return;
	   visit(p->data);
	   travelPre(p->lc,visit);
	   travelPre(p->rc,visit);*///�ĳɵ���ʽ��ٳ�������Ч��

       /*Stack <BinNodePos(T)> S;//β�ݹ��һ��Ľ�����
	   if(p) S.push(p);
	   while(!S.empty()){
		   p=S.pop();visit(p->data);//ע��Ҫ����p
		   if(p->hasRightChild()) S.push(p->rc);
		   if(p->hasLeftChild())  S.push(p->lc);
	   }*/
	   Stack<BinNodePos(T)> S;
	   while(true){
		   visitAlongLeftBranch<T,VST>(p,visit,S);
		   if(S.empty()) break;//�ڵ������һ���ڵ㣬���ҽ����������˳�ѭ��
		   p=S.pop();          
	   }
	}
	template <typename VST> void travelIn(BinNodePos(T) p,VST &visit){
		Stack<BinNodePos(T)> S;
		while(true){
			goAlongLeftBranch(p,visit,S);
			if(S.empty()) break;
			p=S.pop();
			visit(p->data);
			p=p->rc;
		}
	}
	template <typename VST> void travelPost(BinNodePos(T) p,VST &visit){
		Stack<BinNodePos(T)> s;
		if(p) s.push(p);
		while(!s.empty()){
            if(s.top()!=p->parent) gotoHVFL(s);//���ջ��Ԫ�ز��Ǹ�ĸ�Ǿ����������ֵܣ�����һ������
			p=s.pop();//
			visit(p->data);
		}
	}
	template <typename VST> void travelLevel(BinNodePos(T) p,VST &visit){
		Queue<BinNodePos(T)> q;
		q.enqueue(p);
		while(!q.empty()){
			p=q.dequeue();visit(p->data);
			if(p->hasLeftChild()) q.enqueue(p->lc);
			if(p->hasRightChild()) q.enqueue(p->rc);
		}
	}
	BinNodePos(T) zig(){
		BinNodePos(T) succ=this->lc;

		this->lc->parent=this->parent;
		if(this->parent){		
		if(this->isLeftChild()) this->parent->lc=this->lc;
		else if(this->isRightChild()) this->parent->rc=this->lc;
		}
		if(this->lc->rc) this->lc->rc->parent=this;
		this->lc=this->lc->rc;
		

		succ->rc=this;
		this->parent=succ;//����ǵ�ַ
		return succ;	
	}
	BinNodePos(T) zag(){
		BinNodePos(T) succ=this->rc;
		this->rc->parent=this->parent;
		if(this->parent){
			if(this->isLeftChild()) this->parent->lc=this->rc;
			else if(this->isRightChild()) this->parent->rc=this->rc;
		}
		if(this->rc->lc) this->rc->lc->parent=this;
		this->rc=this->rc->lc;
		

		succ->lc=this;
		this->parent=succ;
		return succ;
	}
     

};
template <typename T> void gotoHVFL(Stack<BinNodePos(T)> &s){
	BinNodePos(T) x=s.top();//highest leaf visible from left
	while(x){
		if(x->hasLeftChild()){//���������ѯ
			if(x->hasRightChild()) s.push(x->rc);
			s.push(x->lc);
		}else{
			s.push(x->rc);//��Ҫ�ѿսڵ���ջ�����޷��жϳ���
		}
		x=s.top();
	}
		s.pop();

}
template <typename T,typename VST> void goAlongLeftBranch(BinNodePos(T) p,VST &visit,Stack<BinNodePos(T)> &S){
	while(p){//�����û�з��ʣ�ֻ�Ǽ�¼·��
		S.push(p);
		p=p->lc;
	}
}
template <typename T,typename VST> void visitAlongLeftBranch(BinNodePos(T) p,VST &visit,Stack<BinNodePos(T)> &S){
	while(p){//c++��û�к���Ƕ��  ��������Ĺ��ߺ���
		visit(p->data);
		if(p->hasRightChild()) S.push(p->rc);
		p=p->lc;
	}
}
template <typename T> int stature(BinNodePos(T) p){
	if(p) return p->height;
	else return -1;
}//���ź�û�а취�������ൽBinNode�У���Ϊ-1��Ӧ�����ǿսڵ�
#endif