//#include <iostream>
//
//using namespace std;
//
//template <typename T>
//class A
//{
//public:
//	void print() {
//		cout << "我是普通类,a的值:" << a << endl;
//	}
//	A(T _a) :a(_a) {
//
//	}
//private:
//	T  a;
//};
//
//// 类模板继承类型参数
//template<typename T,typename T2>
//class B : public T2
//{
//public:
//	void printB() {
//		cout << "我是模板类,a值" << a << endl;
//	}
//	B(T _a, T2 _b) :a(_a), T2(_b) {
//
//	}
//private:
//	T  a;
//};
//
//int main(void)
//{
//	B<int,A<int>> b(1,111 );
//	b.printB();
//	b.print();
//	cin.get();
//	return 0;
//}