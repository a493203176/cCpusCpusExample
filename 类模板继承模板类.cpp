//#include <iostream>
//
//using namespace std;
//
//template <typename T>
//class A 
//{
//public:
//	void print() {
//		cout << "我是普通类,a的值:"<<a << endl;
//	}
//	A(T _a) :a(_a) {
//
//	}
//private:
//	T  a;
//};
//
// 类模板继承模板类
//template<typename T>
//class B : public A<int>
//{
//public:
//	void printB() {
//		cout << "我是模板类,a值" << a << endl;
//	}
//	B(T _a,int _b) :a(_a),A<int>(_b) {
//
//	}
//private:
//	T  a;
//};
//
//int main(void)
//{
//	B<int> b(1, 1);
//	b.printB();
//	b.print();
//	cin.get();
//	return 0;
//}