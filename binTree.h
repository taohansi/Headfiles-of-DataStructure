#ifndef BINTREE
#define BINTREE
#include "binNode.h"
#include "../../algorithm/algorithm/algorithm.h"
template <typename T> class BinTree{
protected:
	int _size;
	BinNodePos(T) _root;
	virtual int updateHeight(BinNodePos(T) x){//更新当前节点
		return x->height=1+Max(stature(x->lc),stature(x->rc));
	}
	void updateHeightAbove(BinNodePos(T) x){//更新当前节点及其以上
		while(x){
			int temp=x->height;
			if(temp==updateHeight(x)) break;
			x=x->parent;
		}
	}
	void updateRoot(){
			while(root()->parent)
				_root=_root->parent;
	}
public:
	BinTree(){ _size=0;_root=NULL;}
	~BinTree(){ }
	int getSize(){ return _size;}
	bool empty(){ return !_root;}
	BinNodePos(T) root(){ return _root;}
	BinNodePos(T) insertAsLC(BinNodePos(T) p,T const &e){
		_size++;
	    p->insertAsLC(e);
		updateHeightAbove(p);
		return p->lc;
	}
	BinNodePos(T) insertAsRC(BinNodePos(T) p,T const &e){//这样的参数可使常数对其进行赋值
		_size++;                                         //如果是变量则量改变不会改变它的值
		p->insertAsRC(e);                                //其实写成T &e 参数形式也不会对值有改变
		updateHeightAbove(p);
		return p->rc;
	}
	BinNodePos(T) insertAsRoot(T const &e){//将e作为空树的根节点
		_size=1;
		return _root=new BinNode<T>(e);
	}
	BinNodePos(T) attachLC(BinNodePos(T) p,BinTree<T>* &S){//子树接入
		p->lc=S->root();
		if(S->root()) S->root()->parent=p;
		_size+=S->getSize();
		updateHeightAbove(p);
		S->_root=NULL;S->_size=0;release(S);S=NULL;
		return p;
	}
	BinNodePos(T) attachRC(BinNodePos(T) p,BinTree<T>* &S){
		p->rc=S->root();
		if(S->root()) S->root()->parent=p;
		_size+=S->getSize();
		updateHeightAbove(p);
		S->_root=NULL;S->_size=0;release(S);S=NULL;//将T的内部成员及指针释放
		return p;
	}
	int remove(BinNodePos(T) p){//删除以p为底的子树
		p->fromParentTo()=NULL;
		updateHeightAbove(p);
		int n=removeAt(p);
		_size-=n;//注意要更新大小
		return n;
	}
	BinTree<T>* secede(BinNodePos(T) p){
		p->fromParentTo()=NULL;
		BinTree<T>* S=new BinTree<T>;//声明类型即可
		updateHeightAbove(p->parent);
		_size-=p->size();//注意更新自己的大小
		p->parent=NULL;
		S->_root=p;
		S->_size=p->size();
		return S;
	}
	template <typename VST> void travelPre(VST& visit){
		if(_root) _root->travelPre(_root,visit);
	}
	template <typename VST> void travelIn(VST& visit){
		if(_root) _root->travelIn(_root,visit);
	}
	template <typename VST> void travelPost(VST &visit){
		if(_root) _root->travelPost(_root,visit);
	}
	template <typename VST> void travelLevel(VST &visit){
		if(_root) _root->travelLevel(_root,visit);
	}
	//遍历的好处在于将半线性结构转换为线性结构
};
	template <typename T> int removeAt(BinNodePos(T) p){//删除节点及其子树
		if(!p) return 0;
		int n=1+removeAt(p->lc)+removeAt(p->rc);
		release(p);
		return n;
	}

#endif