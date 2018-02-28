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
	static void clean(T x){}//不是指针就什么都不做
};
template<typename T> struct cleanner<T*>{
	static void clean(T* x){ if(x) delete x;}
};//运用模板类越具体优先级越高的特点，因此遇到指针会优先调用进行析取
template <typename T> void release(T x){cleanner<T>::clean(x);}
#endif
