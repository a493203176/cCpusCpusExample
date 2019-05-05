//#include <iostream>
//
//using namespace std;
//
//template <typename T>
//class A
//{
//public:
//	void printA() {
//		cout << "我是模板类,a值" <<a<< endl;
//	}
//	A(T _a):a(_a) {
//
//	}
//private:
//	T  a;
//};
//
//// 普通类继承模板类
//class B : public A<float>
//{
//public:
//	void print() {
//		cout << "我是普通类" << endl;
//	}
//	B(int _a,float _b) :a(_a), A<float>(_b) {
//
//	}
//private:
//	int  a;
//};
//
//int main(void)
//{
//	B b(1,2.222f);
//	b.print();
//	b.printA();
//
//
//	cin.get();
//	return 0;
//}