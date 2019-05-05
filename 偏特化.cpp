//#include <iostream>
//
//using namespace std;
//
//template <typename T1,typename T2>
//class A
//{
//public:
//	void sum(T1 a, T2 b)
//	{
//		cout << "A(T1,T2): " << a + b << endl;
//	}
//};
//
//// 类的偏特化
//template <typename T1>
//class A<T1,float>
//{
//public:
//	void sum(T1 a, float b)
//	{
//		cout << "A(T1,float): " << a + b << endl;
//	}
//};
//
//template< typename T1, typename T2>
//void print(T1 a, T2 b)
//{
//	cout << "print(T1,T2): " << a + b << endl;
//}
//
//
//template< typename T1>
//void print(T1 a, float b)
//{
//	cout << "print(T1,float): " << a + b << endl;
//}
//
//int main()
//{
//	A<int, int> a;
//	a.sum(1,2.2333);
//
//	A<int, float> b;
//	b.sum(1,2.3233);
//
//	// 没有执行偏特化
//	print<int, int>(1, 2);
//	print<int, float>(1, 2.0f);
//	cin.get();
//	return 0;
//}