#ifndef AVLTREE
#define AVLTREE
#include "../../bst/bst/bst.h"
template <typename T> class AVL: public BST<T>{
public:
	virtual BinNodePos(T) insert(const T& e){
		/*�����һ�β���ʹ��H->H+1���Ӷ�
		���ڵ����ϵĸ��ڵ㶼�п����ʺϣ���
		�޸���͵�ʧ��ڵ������H+1->H��������
		�ڵ��ִ��µ���������*/
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
	/*ɾ�����ֻ��ʹһ�����ڵ�ʧ��
	  ��Ϊ����ýڵ�ʧ�⣬��ɾ����Ȼ
	  �����ڸø��ڵ�϶̵ķ�֧����
	  �����߶����ɽϸߵķ�֧��������*/
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