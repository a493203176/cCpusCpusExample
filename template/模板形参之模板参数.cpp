#include <iostream>

using namespace std;

template <typename T>
class A
{
public:
	void print();
private :
	T a;
};

template <typename T>
void A<T>::print()
{
	cout << "A" << endl;
}

// ���������,���ܱ�ʾT�Ǹ�ģ��
template <template <typename X>typename  T>
class B 
{
	T<int> a; // ��ҪT��һ��ģ��,��������дT<int>
public :
	void print(void);
};

template <template <typename X>typename  T>
void B<T>::print(void)
{
	cout << "B" << endl;
	a.print();
}

int main(void)
{
	// ��ģ��ʵ����
	B<A> b;
	b.print();

	cin.get();
	return 0;
}