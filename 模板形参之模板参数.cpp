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

// 定义成这样,才能表示T是个模板
template <template <typename X>typename  T>
class B 
{
	T<int> a; // 需要T是一个模板,才能这样写T<int>
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
	// 用模板实例化
	B<A> b;
	b.print();

	cin.get();
	return 0;
}