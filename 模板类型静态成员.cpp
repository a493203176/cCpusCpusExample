#include <iostream>

using namespace std;

template <typename T>
class A {
public:
	static int a;// 不依赖模板类型T的静态成员
	static T s2;
};

template <typename T>
// 模板类的静态成员变量初始化,对任意类型T的都有一份通用的值
int A<T>::a = 111;

template <>
int A<int>::a = 222;//也可以特化,给出T类型,只对T是int生效


// s2只能特化
template <>
float A<float>::s2 = 222.212f;

template <>
char A<char>::s2 = 'c';

template <>
int A<int>::s2 = 101;

int main()
{
	// 对任意类型T的都有一份通用的值 111
	cout << A<int>::a << endl;
	cout << A<float>::a << endl;

	cout << A<float>::s2 << endl;
	cout << A<char>::s2 << endl;
	cout << A<int>::s2 << endl;
	cin.get();
	return 0;
}