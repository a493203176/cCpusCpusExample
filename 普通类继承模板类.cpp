//#include <iostream>
//
//using namespace std;
//
//template <typename T>
//class A
//{
//public:
//	void printA() {
//		cout << "����ģ����,aֵ" <<a<< endl;
//	}
//	A(T _a):a(_a) {
//
//	}
//private:
//	T  a;
//};
//
//// ��ͨ��̳�ģ����
//class B : public A<float>
//{
//public:
//	void print() {
//		cout << "������ͨ��" << endl;
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