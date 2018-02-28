#ifndef BSTREE
#define BSTREE
#include "../../binTree/binTree/binTree.h"
template <typename T> class BST: public BinTree<T> {
public:
	virtual BinNodePos(T) search(const T& e){
		_hot=NULL;
		return searchIn(_root,e,_hot);
	}
	virtual BinNodePos(T) insert(const T& e){
		BinNodePos(T) pos=search(e);
		if(!_root) {insertAsRoot(e); return root();}
		if(pos) return pos;
		if(_hot->data<e) pos= _hot->insertAsRC(e);
		else             pos= _hot->insertAsLC(e);
		_size++;
		updateHeightAbove(_hot);//注意pos的height不需要更新，因为初始化height为0
		return pos;
	}
	virtual bool remove(const T& e){
		BinNodePos(T) pos=search(e);
		if(!pos) return false;
		removeAt(pos,_hot);
		_size--;
		if(_hot)updateHeightAbove(_hot);
		return true;
	}
protected:
	BinNodePos(T) _hot;//命中节点的父亲
	BinNodePos(T) connect34(//直接连接三个节点与四颗子树
		BinNodePos(T) a,BinNodePos(T) b, BinNodePos(T) c,
		BinNodePos(T) T0,BinNodePos(T) T1, BinNodePos(T) T2, BinNodePos(T) T3){
			a->lc=T0; if(T0) T0->parent=a; 
			a->rc=T1; if(T1) T1->parent=a; updateHeight(a);
			c->lc=T2; if(T2) T2->parent=c; 
			c->rc=T3; if(T3) T3->parent=c; updateHeight(c);
			b->lc=a; a->parent=b;
			b->rc=c; c->parent=b;
			updateHeight(c);
			return b;///注意这里没有连接b与父节点，所以调用函数外部需要连接节点
	}
	BinNodePos(T) rotateAt( BinNodePos(T) v){
		if(!v) return NULL;
		BinNodePos(T) p=v->parent;//parent
		BinNodePos(T) g=p->parent;//grandParent
		BinNodePos(T) root=NULL;
		if(v->isLeftChild()){//zig
			if(p->isLeftChild()) root=g->zig();//zig zig
			else if(p->isRightChild()){ p->zig(); root=g->zag();} //zig zag
		}
		else if(v->isRightChild()){//zag
			if(p->isRightChild()) root=g->zag();
			else if(p->isLeftChild()){ p->zag(); root=g->zig();}
		}
		updateHeight(g);updateHeight(v);updateHeight(p);
		return root;
	}
	static BinNodePos(T) searchIn(BinNodePos(T) v,const T& e,BinNodePos(T)& hot){
		while(true){//歧义。static函数，返回变量是static
			if(!v||(v->data==e)) return v;
			hot=v;
			if(e<(v->data)) v=v->lc;
			else if((v->data)<=e) v=v->rc;
		}
	}
	 BinNodePos(T) removeAt(BinNodePos(T) & x,BinNodePos(T) & hot){
		/*要分清真正的地址与地址的副本
          但保险起见，还是采用引用实体的办法*/
		BinNodePos(T) temp=x;                                           
		BinNodePos(T) succ=NULL;
		if(!(x->hasLeftChild()) ){ if(!(x==_root)) x->fromParentTo()=x->rc; succ=x->rc; }
		else if( !(x->hasRightChild()) ){ if(!(x==_root)) x->fromParentTo()=x->lc; succ=x->lc; }
		else {//含有两个子树的情况
			temp=temp->succ();
			Swap(x->data,temp->data);
			if(temp->parent!=x){ temp->fromParentTo()=temp->rc; succ=temp->rc;}
			else               { temp->fromParentTo()=temp->rc; succ=temp->rc;}
		}
		hot=temp->parent;
		if(succ) succ->parent=hot;
		if(temp==_root){
			if(_root->hasLeftChild()) _root=_root->lc;
			else if(_root->hasRightChild()) _root=_root->rc;
			updateRoot();
		}
		else{
			release(temp->data); release(temp);
		}
		return succ;
	}

};
#endif