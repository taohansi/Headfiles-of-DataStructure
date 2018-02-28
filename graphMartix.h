#ifndef GRAPHMARTIX
#define GRAPHMARTIX//F:\mycode\mooc_code\HeadFiles\graph\graph
#include "../../graph/graph/graph.h"
#include "../../vector/vector/vector.h"
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
	Edge(Te const& d,int w){
		data=d;
		weight=w;
		type=UNDETERMINED;
	}
};
template <typename Tv,typename Te> class GraphMartix:public Graph<Tv,Te>{
private:
    Vector< Vertex<Tv> > V;
	Vector< Vector< Edge<Te>* > > E;//���д��<Edge<Te>����ҪΪEdge���Ϲ��캯���������ڴ����ĸ���
	                                //��Ϊ�ڴ���ӽ���ʡȥ�ܶ�delete
public:
	GraphMartix(){ n=e=0;}
	~GraphMartix(){
		for(int j=0;j<n;j++)
			for(int k=0;k<n;k++){
				delete E[j][k];//��Ϊ��[]������
			}
	}
	virtual Tv& vertex(int i){ return V[i].data;}
	virtual int inDegree(int i){ return V[i].inDegree;}
	virtual int outDegree(int i){return V[i].outDegree;}
	virtual VStatus& status(int i){ return V[i].status;}
	virtual int& dTime(int i){ return V[i].dTime;}
	virtual int& fTime(int i){ return V[i].fTime;}
	virtual int& parent(int i){return V[i].parent;}
	virtual int& priority(int i){return V[i].priority;}
	virtual int nextNbr(int i,int j){//�Ѿ�ö�ٵ��ھ�j,֮����ھ�
		j=j-1;
		while(j>-1){
			if(exists(i,j)) break;
			j--;
		}
	    return j;
	}
	virtual int firstNbr(int i){ return nextNbr(i,n);}
    //�߲���
	virtual bool exists(int i,int j){ return (0<=i)&&(i<n)&&(0<=j)&&(j<n)&&(E[i][j]!=NULL);}
	virtual EType& type(int i,int j){ return E[i][j]->type;}
	virtual Te& edge(int i,int j){ return E[i][j]->data;}
	virtual int& weight(int i,int j){ return E[i][j]->weight;}
	virtual void insert(Te const& edge,int w,int i,int j){//(i,j)�����dataΪedge��Ȩ��Ϊweight
		if(exists(i,j)) return ;//�������ر�
		E[i][j]=new Edge<Te>(edge,w);
		e++;
		V[i].outDegree++;
		V[j].inDegree++;
	}
	virtual Te remove(int i,int j){//ɾ��i��j��ı�
		Te eBak=edge(i,j);//����data
        delete E[i][j]; E[i][j]=NULL;
		e--;
		V[i].outDegree--;
		V[j].inDegree--;
		return eBak;
	}
	virtual int insert(Tv const &vertex){
        for(int i=0;i<n;i++) E[i].insert(NULL);
		n++;
		E.insert( Vector<Edge<Te>* >(n,n, ( Edge<Te>* )NULL));
		int pos=V.insert(Vertex<Tv>(vertex));//���ر��
		return pos;
	}
	virtual Tv remove(int j){
		/*for(int i=0;i<n;i++) E[i].remove(j);
		E.remove(j);
		V.remove(j);
		n--;*///û�п��ǵ�����Լ����ȵı仯
		for(int i=0;i<n;i++){
			if(exists(j,i)){
				delete E[j][i]; V[i].inDegree--;
			}
		}//������Ϊ�˸������
	    E.remove(j);n--;
		for(int i=0;i<n;i++){
			if(exists(i,j)){
				delete E[i][j]; V[i].outDegree--;
				E[i].remove(j);
			}
		}
		Tv vBak=vertex(j);
        V.remove(j);
		return vBak;
	}
};

#endif