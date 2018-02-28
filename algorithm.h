#ifndef ALGORITHM
#define ALGORITHM
template <typename T> void Swap(T &a,T &b){
	T c(a);
	a=b;
	b=c;
}
template <typename T> int Compare(T &a,T &b){
	if(a>b) return 1;
	else if(a==b) return 0;
	else if(a<b) return -1;
}
template <typename T> T Max(T const &a,T const &b){
	if(a>=b) return a;
	else     return b;
}
template<typename T> struct cleanner{ 
	static void clean(T x){}//����ָ���ʲô������
};
template<typename T> struct cleanner<T*>{
	static void clean(T* x){ if(x) delete x;}
};//����ģ����Խ�������ȼ�Խ�ߵ��ص㣬�������ָ������ȵ��ý�����ȡ
template <typename T> void release(T x){cleanner<T>::clean(x);}
#endif
