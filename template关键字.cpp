//#include <iostream>
//
//using namespace std;
//
//template <typename T>
//class A
//{
//public:
//	// 告诉编译器T::iterator 是一个类型
//	typename T::iterator * iter;//必须有typename,不然歧义
//};
//
//class B
//{
//public:
//	typedef int iterator; // 内嵌类型
//};
//
//int main()
//{
//	// 模板类
//	A<B> a;
//
//	cout << typeid(a.iter).name() << endl;
//
//	//cout<< typeid(a.iter).name()
//
//	cin.get();
//	return 0;
//}