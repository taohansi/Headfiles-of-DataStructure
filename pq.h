#ifndef PRIORITYQUEUE
#define PRIORITYQUEUE
template <typename T> struct PQ{
	virtual void insert(T)=0;//ע��Ӧ���ǽ��������в��룬�����ñȽ�ʱ����Ϊ�Ƚϵ����أ��Ὣ���������ȼ����бȽ�
	virtual T getMax()=0;//����ֻ��ջ����һ����ڽ��в���
	virtual T delMax()=0;
};
#endif