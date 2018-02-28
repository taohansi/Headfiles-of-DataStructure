#ifndef BINTREE
#define BINTREE
#include "binNode.h"
#include "../../algorithm/algorithm/algorithm.h"
template <typename T> class BinTree{
protected:
	int _size;
	BinNodePos(T) _root;
	virtual int updateHeight(BinNodePos(T) x){//���µ�ǰ�ڵ�
		return x->height=1+Max(stature(x->lc),stature(x->rc));
	}
	void updateHeightAbove(BinNodePos(T) x){//���µ�ǰ�ڵ㼰������
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
	BinNodePos(T) insertAsRC(BinNodePos(T) p,T const &e){//�����Ĳ�����ʹ����������и�ֵ
		_size++;                                         //����Ǳ��������ı䲻��ı�����ֵ
		p->insertAsRC(e);                                //��ʵд��T &e ������ʽҲ�����ֵ�иı�
		updateHeightAbove(p);
		return p->rc;
	}
	BinNodePos(T) insertAsRoot(T const &e){//��e��Ϊ�����ĸ��ڵ�
		_size=1;
		return _root=new BinNode<T>(e);
	}
	BinNodePos(T) attachLC(BinNodePos(T) p,BinTree<T>* &S){//��������
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
		S->_root=NULL;S->_size=0;release(S);S=NULL;//��T���ڲ���Ա��ָ���ͷ�
		return p;
	}
	int remove(BinNodePos(T) p){//ɾ����pΪ�׵�����
		p->fromParentTo()=NULL;
		updateHeightAbove(p);
		int n=removeAt(p);
		_size-=n;//ע��Ҫ���´�С
		return n;
	}
	BinTree<T>* secede(BinNodePos(T) p){
		p->fromParentTo()=NULL;
		BinTree<T>* S=new BinTree<T>;//�������ͼ���
		updateHeightAbove(p->parent);
		_size-=p->size();//ע������Լ��Ĵ�С
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
	//�����ĺô����ڽ������Խṹת��Ϊ���Խṹ
};
	template <typename T> int removeAt(BinNodePos(T) p){//ɾ���ڵ㼰������
		if(!p) return 0;
		int n=1+removeAt(p->lc)+removeAt(p->rc);
		release(p);
		return n;
	}

#endif