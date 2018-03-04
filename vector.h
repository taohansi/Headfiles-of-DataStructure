#ifndef VECOTR
#define VECOTR
#define DEFAULT_CAPACITY 10//ͨ��define���ó�ʼ����
//��ʱ�Ļ������ݽṹ�����еĲ�������ЩӦ�ý����ϲ����
//���ϲ�����֤������ȷ��
//#include "../../pq_complHeap/pq_complHeap/pq_complHeap.h"ͷ�ļ��������໥����
template <typename T>
class Vector{
protected:
	int size;
	int capacity;
	T* element;
    void copyFrom(T const*ptr,int lo,int hi){
		capacity=2*(hi-lo);
		element=new T[capacity];
		for(size=0;lo<hi;lo++,size++)
			element[size]=ptr[lo];

	}//ͨ��һ���������������
	void swap(T &a, T &b){
		T hold=a;
		a=b;
		b=hold;
	}
	int bubble(int lo,int hi){
		int last=lo;
		for(int i=lo+1;i<hi;i++){//��ɨ��Ԫ����Ϊǰ�������õط�ֹԽ��
			if(element[i-1]>element[i]) {
				swap(element[i-1],element[i]);//�ȶ��������㷨������ͬԪ��
				last=i;                       //�����ű㲻�ύ��λ��
			}
		}
		return last;
	}
	void merge(int lo,int mi,int hi){
		T* A=new T[mi-lo];
		T* B=element;
        for(int i=0, k=lo;i<mi-lo;i++,k++) A[i]=element[k];
		int p=0; int q=mi; int j=lo;
		while((p<(mi-lo))&&(q<hi)){
			if(A[p]<=B[q]){
               element[j]=A[p];
			   p++;j++;
			}else if(B[q]<A[p]){
				element[j]=B[q];
				q++;j++;
			}
		}
		if(p<(mi-lo)){
			for(int i=p;i<(mi-lo);i++,j++) element[j]=A[i];
		}
		delete []A;
		
	}
	int max(int lo,int hi){
		int min=lo;
		for(int i=lo;i<hi;i++){
			if(element[min]<=element[i]) min=i;
		}
        return min;
	}
	void insert(int lo,int hi,T e){
		int pos=search(e,lo,hi)+1;
		for(int i=hi-1;i>=pos;i--){
			element[i+1]=element[i];
		}
		element[pos]=e;
	}
public:

	Vector( int c=DEFAULT_CAPACITY, int s=0,T v=T()){//����Ϊc����ģΪs������Ԫ�س�ʼΪv
	    capacity=c; size=s;
		element=new T[c];
		for(int i=0;i<size;i++){
			element[i]=v;
	}

}

	Vector(T const*ptr,int n){ copyFrom(ptr,0,n);
	}
	Vector(T const*ptr,int lo,int hi){copyFrom(ptr,lo,hi);
	}
	Vector(Vector<T> &V){copyFrom(V.element,0,V.size);
	}
	Vector(Vector<T> &V, int lo,int hi){copyFrom(V.element,lo,hi);
	}
	~Vector(){delete []element;}
	Vector<T>& operator=(Vector<T> const &V){
		if(element!=NULL) delete []element;
		copyFrom(V.element,0,V.size);
        return *this;
	}
	int getSize() {return size;}
	int getCapacity(){return capacity;}

	T& operator[](int pos){
		return element[pos];
	}//�������ñ�֤�˼��ܽ�����ֵ����Ҳ�ܽ�����ֵ����
	bool empty(){ if(size!=0) return false;}
	int find(T const &e,int lo,int hi){
		for(int i=hi-1;i>=lo;i--){
			if(element[i]==e)
				return i;//����������Ԫ��
		}
		return i;//���ص���Խ����λ��
	}//����λ��
	int find(T const &e){ find(e,0,size);}
	int insert(int pos,T const&e){
		expand();
		for(int i=size-1;i>=pos;i--){
			element[i+1]=element[i];
		}
		element[pos]=e;
		size++;
		return pos;
	}//����λ��
	int insert(T const&e){
		return insert(size,e);
	}
	T remove(int pos){
		T ans=element[pos];
        remove(pos,pos+1);
		return ans;
	}//���ر�ɾ��Ԫ��
	int remove(int lo, int hi){
		if(hi>size) return -1;
        if(lo==hi) return 0;//����������ȵļ������
		for(;hi<size;lo++,hi++) element[lo]=element[hi];
		size=lo;//��������ʱ��hi�ƶ������������⣬loҲ�ƶ����������⼴size�ڱ�
		shrink();
		return hi-lo;
	}
	void expand(){
		if(size<capacity) return;//ע���ж�
		if(capacity<DEFAULT_CAPACITY) capacity=DEFAULT_CAPACITY;//��vector�Ĳ���Ӧ��������size
		capacity=2*capacity;
		T* ptr=element;//��ָ��ptrָ��element��ָ��������
		element=new T[capacity];
		for(int i=0;i<size;i++) element[i]=ptr[i];
		delete []ptr;

		
	}
	void shrink(){
		if(capacity<2*DEFAULT_CAPACITY) return;
		if(size*4>capacity) return;//��25%Ϊ��
		T* ptr=element;
		capacity=capacity/2;//��������
		element=new T[capacity];
		for(int i=0;i<size;i++) element[i]=ptr[i];
		delete []ptr;
	}
	void unsort(){ unsort(0,size);}//���Է���Ľ��в���
	void unsort(int lo,int hi){//������
		for(int i=hi-1;i>=lo;i--){
			swap(element[i],element[rand()%(hi-lo)+lo]);
		}
	}//�������������һ���÷���
	int deduplicate(){//������ͬɾ�������Ԫ��
       /* int oldsize=size;
		for(int i=1;i<size;i++){
			int pos=find(element[i],0,i);
			if(pos>=0){remove(pos);i--;}
		}
		return oldsize-size; // �������ÿ�ζ���Ҫi++��whileѭ��
		                     // �ɶ��Ը���*/
	   int oldsize=size;
       int i=1;
	   while(i<size){
		   int pos=find(element[i],0,i);
		   if(pos>=0) remove(i);
		   else i++;
	   }
	   return oldsize-size;
	}//ɾ���ظ�Ԫ��
	template <typename VST >void traverse(VST &visit){//�������뺯������
		for(int i=0;i<size;i++) visit(element[i]);//�����е�ÿ��Ԫ�ض����иú�������
	}
	int disordered(){//������������Եĸ���
		int sum=0;
		for(int i=0;i<size-1;i++){
			if(element[i]>element[i+1]) sum++;
		}
		return sum;
	}
	int uniquify(){//��������ɾ���ظ�Ԫ�أ�������ͬɾ�������Ԫ��
		int i=0;
		int j=1;
		while(j<size){
			if(element[j]!=element[i]){
				element[i+1]=element[j];//������ɾ����������ֱ�ӽ�Ԫ��ǰ��
				i++;
			}
			j++;
		}
		size=i+1;
		shrink();//ע��ѹ��
		return j-size;
	}
	int search(T &e,int lo,int hi){
		/*while(lo<hi){
			int mi=(lo+hi)/2;
			if(e<element[mi]) hi=mi;
			else if(element[mi]<e) lo=mi+1;
			else return mi;
		}
		return -1;// ���αȽϰ汾*/
		while(lo<hi){
            int mi=(lo+hi)/2;
			(e<element[mi])? hi=mi:lo=mi+1;//��Ȼ�Ƿ��������䣬��������������[lo,mi)(mi,hi)
		}//��element[lo==hi]�˳�����ʱΪ����e����СԪ��
		return lo-1;
	}
	void bubbleSort(){ bubbleSort(0,size);}
	void bubbleSort(int lo,int hi){
		while(lo<bubble(lo,hi)){
			hi=bubble(lo,hi);//hi����Ϊ���һ�ν����Ĺ���
		}
	}
	void mergeSort(){ mergeSort(0,size);}
	void mergeSort(int lo,int hi){
		if((hi-lo)==1) return;//if(!(lo<hi)) return;
		int mi=(lo+hi)/2;
		mergeSort(lo,mi);mergeSort(mi,hi);
		merge(lo,mi,hi);
	}
	void selectionSort(){ selectionSort(0,size);}//ѡ������
	void selectionSort(int lo,int hi){
		while(lo<hi){
			int pos=max(lo,hi);
			swap(element[hi-1],element[pos]);
			hi--;
		}
	}
	/*void heapSort(){ heapSort(0��size);}
	void heapSort(int lo,int hi){
		PQ_ComplHeap<int> H(element+lo,hi-lo);
		for(int j=hi;j>lo;j--){
			element[j]=H.delMax();
		}

	}*/
	void insertSort(){ insertSort(0,size);}
	void insertSort(int lo,int hi){
		for(int i=lo+1;i<hi;i++){
			insert(lo,i,element[i]);
		}
	}
	void shellSort(){ shellSort(0,size);}
	void shellSort(int lo,int hi){
		int sedgewick[9]={0,1,5,19,41,109,209,505,929};//ע������ֻ�г��˲�������
		int index=0;int j;
		for(;sedgewick[index+1]<hi;index++);
		for(int D=sedgewick[index];index>0;index--,D=sedgewick[index]){//�õ����D
		  for(int i=lo+D;i<hi;i=i+D){//���ÿ��ŷ�ʽ
			int temp=element[i];
			for(j=i-D;temp<element[j];j=j-D){
				element[j+D]=element[j];
			}
			element[j+D]=temp;
		  }
	    }
	}
	
};
	
#endif 