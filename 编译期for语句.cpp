#include <iostream>

using namespace std;

// ��ģ��
template <int N>// �����͵Ĳ���
struct For
{
	static inline void print()
	{
		cout << "forѭ��ִ��" << N << "��" << endl;
		For<N - 1>::print(); //��䴥���ݹ�ĺ���,�Ӷ�����ѭ��
	}
};

// ����ȫ�ػ���ֹ�ݹ�
template <>
struct For<0>
{
	static inline void  print()
	{
		cout << "forѭ��ִ��" << 0 << "��" << endl;
	}
};

int main(void)
{
	// �����ڵ�forѭ��
	For<10>::print();
	cin.get();
	return 0;
}