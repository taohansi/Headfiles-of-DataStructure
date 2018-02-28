#ifndef GRAPH
#define GARPH
#include "../../queue/queue/queue.h"
typedef enum{ UNDISCOVERED,DISCOVERED,VISITED} VStatus;
typedef enum{ UNDETERMINED, TREE, CROSS, FORWARD, BACKWARD} EType;
template <typename Tv,typename Te>
class Graph{//不给出实现给出大量的虚函数使继承类来实现
private:    //需要实现否则编译无法通过
	void reset(){
		for(int i=0;i>n;i++){
			status(i)=UNDISCOVERED; dTime(i)=fTime(i)=-1;
			parent(i)=-1;priority(i)=INT_MAX;
			for(int j=0;j<n;j++){
				if(exists(i,j)) type(i,j)=UNDETERMINED;
			}
		}
	}
	void BFS(int v,int& clock){
		Queue<int> Q; status(v)=DISCOVERED; Q.enqueue(v);
		while(!Q.empty()){
			int top=Q.dequeue();
			clock++;
			dTime(top)=clock;
			int nbr=firstNbr();
			while(nbr>-1){
				if(status(nbr)==UNDISCOVERED){
				status(nbr)=DISCOVERED; Q.enqueue(nbr);
				type(top,nbr)=TREE; parent(nbr)=top;
				}else{
			    type(top,nbr)=CROSS;//如果已经访问过标记为跨边，注意(v,u)与(u,v)标记不同
				}
				nbr=nextNbr(top,nbr);
			}
            status(top)=VISITED;
		}

	}
	void DFS(int v,int& clock){
        status(v)=DISCOVERED;clock++;dTime(v)=clock;
		int pos=firstNbr(v);
		while(true){
			if((pos>-1)&&(status(pos)==UNDISCOVERED)){
                type(v,pos)=TREE;parent(pos)=v;
				DFS(pos,clock);
			}
			else if((pos>-1)&&(status(pos)==DISCOVERED)){
				type(v,pos)=BACKWARD;
			}
			else if((pos>-1)&&(status(pos)==VISITED)){//对于有向图的细分
				if(dTime(v)>dTime(pos)) type(v,pos)=CROSS;
				else if(dTime(v)<dTime(pos)) type(v,pos)=FORWARD;
			}
			else if(pos<=-1) return;
			pos=nextNbr(v,pos);
		}				
        status(v)=VISITED;fTime(v)=++clock;//如果该节点的邻居都已经访问完，则标记为visited
	}
public:
	int n;
	virtual int insert(Tv const& )=0;
	virtual Tv remove(int )=0;
	virtual Tv& vertex(int )=0;
	virtual int inDegree(int )=0;
    virtual int outDegree(int )=0;
	virtual int firstNbr(int )=0;
	virtual int nextNbr(int ,int )=0;
	virtual VStatus& status(int )=0;
	virtual int& dTime(int )=0;
	virtual int& fTime(int )=0;
	virtual int& parent(int )=0;
	virtual int& priority(int )=0;
	int e;
	virtual bool exists(int ,int )=0;
	virtual void insert(Te const&,int,int,int )=0;
	virtual Te remove (int ,int )=0;
	virtual EType& type(int,int )=0;
	virtual Te& edge(int,int )=0;
	virtual int& weight(int, int )=0;
	//遍历
	void bfs(int v){ 
		reset();
		int clock=0;
		for(int i=0;i<n;i++){
			if(status(v)==UNDISCOVERED)
               BFS(v,clock);
			v=(v+1)%n;
		}
	}
	void dfs(int v){
		reset();
		int clock=0;
		for(int i=0;i<n;i++){
			if(status(v)==UNDISCOVERED)
			   DFS(V,clock);
			v=(v+1)%n;
		}
	}
};
#endif