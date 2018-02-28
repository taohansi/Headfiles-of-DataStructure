#ifndef BINNODE
#define BINNODE
#define BinNodePos(T) BinNode<T>*
#include "../../Stack/Stack/Stack.h"
#include "../../queue/queue/queue.h"
//typedef enum{ RB_RED,RB_BLACK} RBColor;
/*template <typename T> int stature(BinNodePos(T) p){
	if(p) return p->height;
	else return -1;
}//很遗憾没有办法把它归类到BinNode中，因为-1对应到的是空节点*///不能放在之前BinNode未声明
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
	int size(){//返回包含当前节点的子树的节点的个数
		int s=1;
		if(lc) s+=lc->size();//递归纪录左右子树节点的个数
		if(rc) s+=rc->size();//递归基，当左右子女均为空时返回1
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

	BinNodePos(T)& tailerChild(){//定义左儿子优先级更高
		if(stature(lc)<stature(rc)) return rc;
		else if(stature(rc)<stature(lc)) return lc;
		else {
		if(hasLeftChild()) return lc;
		else if(hasRightChild()) return rc;
		}
	}
	BinNodePos(T) insertAsLC(T const &e){ return lc=new BinNode(e,this);}//完成了一次双向连接
	BinNodePos(T) insertAsRC(T const &e){ return rc=new BinNode(e,this);}
	BinNodePos(T) succ(){
		BinNodePos(T) s=new BinNode<T>;
		if(rc){//右子树的最左边
			s=rc;
			while(s->hasLeftChild()){//不能为s则跳出时条件是s为空
				s=s->lc;
			}
		}
		else{
			s=this;
			while(s->isRightChild()){//往左上行走
				s=s->parent;
			}
			s=s->parent;//再右行一步
		}
		return s;
	}
	template <typename VST> void travelPre(BinNodePos(T) p,VST &visit){//定义于节点更具有一般性
       /*if(!p) return;
	   visit(p->data);
	   travelPre(p->lc,visit);
	   travelPre(p->rc,visit);*///改成迭代式真假程序运行效率

       /*Stack <BinNodePos(T)> S;//尾递归的一般改进方法
	   if(p) S.push(p);
	   while(!S.empty()){
		   p=S.pop();visit(p->data);//注意要更新p
		   if(p->hasRightChild()) S.push(p->rc);
		   if(p->hasLeftChild())  S.push(p->lc);
	   }*/
	   Stack<BinNodePos(T)> S;
	   while(true){
		   visitAlongLeftBranch<T,VST>(p,visit,S);
		   if(S.empty()) break;//在弹出最后一个节点，并且将其访问完后，退出循环
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
            if(s.top()!=p->parent) gotoHVFL(s);//如果栈顶元素不是父母那就是他的右兄弟，进行一次深入
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
		this->parent=succ;//存的是地址
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
		if(x->hasLeftChild()){//优先向左查询
			if(x->hasRightChild()) s.push(x->rc);
			s.push(x->lc);
		}else{
			s.push(x->rc);//需要把空节点入栈否则无法判断出口
		}
		x=s.top();
	}
		s.pop();

}
template <typename T,typename VST> void goAlongLeftBranch(BinNodePos(T) p,VST &visit,Stack<BinNodePos(T)> &S){
	while(p){//但这个没有访问，只是纪录路径
		S.push(p);
		p=p->lc;
	}
}
template <typename T,typename VST> void visitAlongLeftBranch(BinNodePos(T) p,VST &visit,Stack<BinNodePos(T)> &S){
	while(p){//c++中没有函数嵌套  先序遍历的工具函数
		visit(p->data);
		if(p->hasRightChild()) S.push(p->rc);
		p=p->lc;
	}
}
template <typename T> int stature(BinNodePos(T) p){
	if(p) return p->height;
	else return -1;
}//很遗憾没有办法把它归类到BinNode中，因为-1对应到的是空节点
#endif