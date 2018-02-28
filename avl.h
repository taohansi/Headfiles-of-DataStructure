#ifndef AVLTREE
#define AVLTREE
#include "../../bst/bst/bst.h"
template <typename T> class AVL: public BST<T>{
public:
	virtual BinNodePos(T) insert(const T& e){
		/*插入的一次操作使得H->H+1，从而
		父节点以上的父节点都有可能适合，但
		修改最低的失衡节点后又由H+1->H所以以上
		节点又从新调整过来了*/
		BinNodePos(T) pos=search(e);
		if(pos) return NULL;
		if(!_root) {insertAsRoot(e); return root();}
		if(_hot->data<e) pos=_hot->insertAsRC(e);
		else if(e<_hot->data) pos=_hot->insertAsLC(e);
		_size++;
		BinNodePos(T) temp=pos;
		while(pos){
			if( !(pos->avlBalanced()) ){
				rotateAt(pos->tailerChild()->tailerChild());
				break;
			}else updateHeight(pos);
			pos=pos->parent;            
		}
		updateRoot();
		return temp;
	}
	virtual bool remove (const T& e){
	/*删除最多只会使一个父节点失衡
	  因为如果该节点失衡，则删除必然
	  发生在该父节点较短的分支树上
	  但，高度是由较高的分支树决定的*/
		BinNodePos(T) pos=search(e);
		if(!pos) return false;
		pos=removeAt(pos,_hot);
		_size--;
		while(pos){
			if(!(pos->avlBalanced())){
				rotateAt(pos->tailerChild()->tailerChild());
				updateRoot();
			}else
			updateHeight(pos);
			pos=pos->parent;
		}
		if(_size==0) _root=NULL;
		return true;	
	}

};
#endif