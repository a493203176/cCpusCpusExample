#include <iostream>

using namespace std;


//����	C2991	�ض��� ģ�� ������T��	
template<class T>
inline T add(T a, T b)
{
	// �ŵ�ģ��������������,������T����
	//typedef string T;
	T tmp = a + b;
	return tmp;
}

template<class T1,class T2,class T3> 
inline T3 add(T1 a, T2 b)
{
	// �ŵ�ģ��������������,������T����
	//typedef string T;
	T3 tmp = a + b;
	return tmp;
}

int main()
{
	cout << add<int,int,int>(1, 2) << endl;
	cout << add<float,int,float>(1.666f, 2) << endl;
	cout << add<double,int,double>(1.0, 2.0) << endl;
	cin.get();
	return 0;
}