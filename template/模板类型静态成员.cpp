#include <iostream>

using namespace std;

template <typename T>
class A {
public:
	static int a;// ������ģ������T�ľ�̬��Ա
	static T s2;
};

template <typename T>
// ģ����ľ�̬��Ա������ʼ��,����������T�Ķ���һ��ͨ�õ�ֵ
int A<T>::a = 111;

template <>
int A<int>::a = 222;//Ҳ�����ػ�,����T����,ֻ��T��int��Ч


// s2ֻ���ػ�
template <>
float A<float>::s2 = 222.212f;

template <>
char A<char>::s2 = 'c';

template <>
int A<int>::s2 = 101;

int main()
{
	// ����������T�Ķ���һ��ͨ�õ�ֵ 111
	cout << A<int>::a << endl;
	cout << A<float>::a << endl;

	cout << A<float>::s2 << endl;
	cout << A<char>::s2 << endl;
	cout << A<int>::s2 << endl;
	cin.get();
	return 0;
}