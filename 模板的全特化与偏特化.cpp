//#include <iostream>
//
//using namespace std;
//
//// 类模板
//template <typename T1,typename T2>
//class A
//{
//private:
//	T1 a;
//	T2 a2;
//public:
//	void print() {
//		cout << "A(T1,T2)" << endl;
//	}
//};
//
////类的全特化,结构与主模板无需一致,这就叫私人订制
//template <>
//class A<int,float>
//{
//public:
//	void print() {
//		cout << "A<int,float>" << endl;
//	}
//	void show() {
//		cout << "show A<int,float>" << endl;
//	}
//};
//
//
//template <>
//class A<float, float>
//{
//public:
//	void print() {
//		cout << "A<float,float>" << endl;
//	}
//	void show() {
//		cout << "show A<float,float>" << endl;
//	}
//};
//
//// 函数模板
//template<typename T1, typename T2>
//void test(T1 a, T2 b)
//{
//	cout << "test(T1,T2)" << endl;
//}
//
//// 函数全特化
//template<>
//void test(int a, float b)
//{
//	cout << "test(int,float)" << endl;
//}
//
//
//int main()
//{
//	// 模板类
//	A<int, int> a;
//	a.print();
//	//a.show(); 没有成员函数,这就是特化的区别
//
//	// 全特化
//	A<int, float> b;
//	b.print();
//	b.show();
//
//	A<float, float> c;
//	c.print();
//	c.show();
//
//	// 模板函数
//	test(1, 2);
//	test(1, 1.0f);
//	test<int,float>(1, 2);
//	test<int, double>(1, 2);
//	cin.get();
//	return 0;
//}