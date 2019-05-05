//#include <iostream>
//
//using namespace std;
//
//template <typename T>
//void f1(T *)
//{
//	cout << typeid(T).name() << endl;
//}
//
//template <typename T,int N>// 类型参数T,非类型参数N
//void f2(T(&p)[N]) // 参数p为T[N]数组的引用
//{
//	cout <<N<<","<< typeid(T).name()<<"," <<p[2]<< endl;
//}
//
//
//class S
//{
//public:
//	void f(double *) {}
//};
//
//template <typename T1, typename T2,typename T3>// 
//void f3( T1( T2::*)(T3 *)) // T2一定是一个类,或者结构体
//{
//	cout << typeid(T1).name() << " " << typeid(T2).name() << " " << typeid(T3).name() << " " << endl;
//}
//
//template <int N> // 非类型参数N
//class X
//{
//public:
//	typedef int l; // 定义了一个类型
//	void f(int) {}
//};
//
//template <int N> // 非类型参数N
//void f4(void (X<N>::* p)(typename X<N>::l))// l是模板的类型
//{
//	cout << N << " " << typeid(X<N>::l).name() << endl;
//}
//// f4的参数X<N>的成员函数,该函数的返回类型为void,接受一个 X<N>::l参数
//
//template <typename T> 
//void f5(T t1)
//{
//	cout << typeid(T).name() <<","<< t1 << endl;
//}
//
//
//template <typename T>
//class M
//{
//};
//
//template <typename T>
//class N : public M<T>
//{
//};
//
//template <typename T>
//void f7(M<T>)
//{
//	cout << typeid(T).name() << endl;
//}
//
//template <typename T>
//void f8(T)
//{
//	cout << typeid(T).name() << endl;
//}
//
//// 加了引用,数组就不会加载成指针
//template <typename T>
//void f9(T &t)
//{
//	cout << typeid(T).name() << endl;
//}
//
//
///*
//	T & t  表示引用变量
//	T && t 表示可以右值引用参数,常量,放在=右边
//*/
//template <typename T>
//void f10(T && t)
//{
//	cout << typeid(T).name() << endl;
//}
//
//
//template <typename T>
//void f11()
//{
//	typename T::vType t; // 表示T类型中有个vType类型
//	cout << typeid(t).name() << endl;
//}
//
//class Y
//{
//public:
//	typedef float vType;
//};
//
//
//int main(void)
//{
//
//	int **** p = 0;
//	f1(p);// 被推导为int ***
//	//f1<int ***>(p); 由于自动推导,<int ***>可以被省略
//
//	int a[10] = {1,2,3,4};
//	char c[42] = "hello";
//	f2(a); // T被推导int, N被推导为10
//	f2(c); // T被推导char, N被推导为42
//
//	f3(&S::f);// 通过传入的参数,自动推导出来,很智能
//	
//	f4(&X<10>::f);
//
//	// 函数指针f6
//	void(*f6)(char) = &f5;// 推导成功,并将T替换为char
//	f6('A');
//
//	N<int> n;
//	M<long> m1;
//	f7(n);// 推导int
//	f7(m1); // 推导long
//
//	const char * p8 = "abc";
//
//	f8(p8); // char const * 
//	f9(p8); // char const * 
//	double pp[20];
//	f8(pp); // double * 
//	f9(pp); // double [20]
//
//
//	int aa = 99;// 即使左值,也是右值
//	f10(aa); // 	int
//	f10(100); // 传入右值 	int
//	f10(0.003);// 传入右值 	double
//	f10("asdf");// 传入右值 	char const [5]
//
//	f11<Y>();
//	cin.get();
//	return 0;
//}