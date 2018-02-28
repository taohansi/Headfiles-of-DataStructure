#ifndef ENTRY
#define ENTRY
template <typename K,typename V> struct Entry{
	K key; V value;
	Entry( K k=K(),V v=V()){
		key=k;
		value=v;
	}//ע���·�Ҫ����Entry������
	Entry( Entry<K,V>const&  entry): key(entry.key), value(entry.value){}//�������������K,V�Ŀ������������Ǹ�ֵ����
	bool operator < (Entry<K,V>const& e){ return key<e.key;}//���ʽ���Ӽ��
	bool operator > (Entry<K,V>const& e){ return key>e.key;}
	bool operator ==(Entry<K,V>const& e){ return key==e.key;}
	bool operator !=(Entry<K,V>const& e){ return key!=e.key;}
	
};
#endif