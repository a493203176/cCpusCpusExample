//#include <iostream>
//
//using namespace std;
//
//template <typename T>
//class A 
//{
//public:
//	void print() {
//		cout << "������ͨ��,a��ֵ:"<<a << endl;
//	}
//	A(T _a) :a(_a) {
//
//	}
//private:
//	T  a;
//};
//
// ��ģ��̳�ģ����
//template<typename T>
//class B : public A<int>
//{
//public:
//	void printB() {
//		cout << "����ģ����,aֵ" << a << endl;
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