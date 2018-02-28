#ifndef ENTRY
#define ENTRY
template <typename K,typename V> struct Entry{
	K key; V value;
	Entry( K k=K(),V v=V()){
		key=k;
		value=v;
	}//注意下方要声明Entry的类型
	Entry( Entry<K,V>const&  entry): key(entry.key), value(entry.value){}//这样会调用类型K,V的拷贝函数而不是赋值函数
	bool operator < (Entry<K,V>const& e){ return key<e.key;}//表达式更加简洁
	bool operator > (Entry<K,V>const& e){ return key>e.key;}
	bool operator ==(Entry<K,V>const& e){ return key==e.key;}
	bool operator !=(Entry<K,V>const& e){ return key!=e.key;}
	
};
#endif