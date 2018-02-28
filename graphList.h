#ifndef GRAPHLIST
#define GRAPHLIST
#include "../../vector/vector/vector.h"
#include "../../list/list/list.h"
#include "../../graph/graph/graph.h"
template <typename Tv> struct Vertex{
	Tv data;int inDegree;int outDegree; VStatus status;
	int dTime,fTime;
	int parent; int priority;
	Vertex(){
		data=0;
		inDegree=outDegree=0;
		status=UNDISCOVERED;
		dTime=fTime=0;
		parent=-1;
        priority=INT_MAX;
	}
	Vertex(Tv const &d){
		data=d;
		inDegree=outDegree=0;
		status=UNDISCOVERED;
		dTime=fTime=0;
		parent=-1;
        priority=INT_MAX;
	}
};
template <typename Te> struct Edge{
		Te data; int weight; EType type;
		int v;//关联顶点
	Edge(){
         data=0;
		 weight=-1;
		 type=UNDETERMINED;
	     v=-1;
		}
	Edge(Te const& d,int const& w){
		data=d;
		weight=w;
		type=UNDETERMINED;
		v=-1;
	}
};
template <typename Tv,typename Te> class GraphList:public Graph<Tv,Te>{
private:
	Vector< Vertex<Tv> > V;
	Vector< List< Edge<Te> > > E;//更加紧凑
public:
	GraphList(){ n=e=0;};         //不过需要添加默认构造函数
	~GraphList(){}
	listNodePos(Edge<Te>) find(int i,int j){
       	listNodePos(Edge<Te>) p=E[i].last();
		for(int i=0;i<E[i].getSize();i++){
			if((p->data).v==j) return p;
			p=p->pred;
		}
		return NULL;
	}
	virtual Tv& vertex(int i){ return V[i].data;}
	virtual int inDegree(int i){ return V[i].inDegree;}
	virtual int outDegree(int i){ return V[i].outDegree;}
	virtual VStatus& status(int i){ return V[i].status;}
	virtual int& dTime(int i){return V[i].dTime;}
	virtual int& fTime(int i){ return V[i].fTime;}
	virtual int& parent(int i){ return V[i].parent;}
	virtual int& priority(int i){ return V[i].priority;}
	virtual int nextNbr(int i,int j){
		listNodePos(Edge<Te>) p=E[i].last();
		if(j!=-1){
           p=find(i,j);
		   p=p->pred;
		}
		return (p->data).v;
	}
	virtual int firstNbr(int i){ return nextNbr(i,-1);}
	//边
	virtual bool exists(int i,int j){
		listNodePos(Edge<Te>) p=find(i,j);
		if(p) return true;
		else return false;
	} 
	virtual EType& type(int i,int j){
		listNodePos(Edge<Te>) p=find(i,j);
		return (p->data).type;
	}
	virtual Te& edge(int i,int j){
       	listNodePos(Edge<Te>) p=find(i,j);
		return (p->data).data;
	}
	virtual int& weight(int i,int j){ 
       	listNodePos(Edge<Te>) p=find(i,j);
		return (p->data).weight;
	}
	virtual void insert(Te const& edge,int w,int i,int j){
		if(exists(i,j)) return;
		E[i].insertAsLast(Edge<Te>(edge,w));
        listNodePos(Edge<Te>) p=E[i].last();
		(p->data).v=j;//出边表，如果是无向图还需插入
		e++;
		V[i].outDegree++;
		V[j].inDegree++;
	}
	virtual Te remove(int i,int j){
		listNodePos(Edge<Te>) p=find(i,j);
		Te eBak=(p->data).data;
		if(p) E[i].remove(p);
		e--;
		V[i].outDegree--;
		V[j].inDegree--;
		return eBak;
	}
	virtual int insert(Tv const &vertex){
		n++;
		int pos=V.insert(Vertex<Tv>(vertex));
		E.insert( List<Edge<Te>>() );
		return pos;
	}
	virtual Tv remove(int j){
		for(int i=0;i<E[i].getSize();i++){
            listNodePos(Edge<Te>) p=E[i].first();
			if((p->data).v!=-1){
				V[(p->data).v].inDegree--;
			}
		}
		E.remove(j);n--;
		for(int i=0;i<n;i++){
			listNodePos(Edge<Te>) p=find(i,j);
			if(p){
				E[i].remove(p);
				V[i].outDegree--;
			}
		}
		Tv vBak=vertex(j);
		V.remove(j);
		return vBak;
	}
};
#endif