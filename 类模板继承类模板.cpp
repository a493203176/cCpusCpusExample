#include <iostream>

using namespace std;

template <typename T>
class A 
{
public:
	void print() {
		cout << "������ͨ��,a��ֵ:"<<a << endl;
	}
	A(T _a) :a(_a) {

	}
private:
	T  a;
};

// ��ģ��̳���ģ��
template<typename T,typename T2>
class B : public A<T2>
{
public:
	void printB() {
		cout << "����ģ����,aֵ" << a << endl;
	}
	B(T _a,T2 _b) :a(_a),A<T2>(_b) {

	}
private:
	T  a;
};

int main(void)
{
	B<int, int> b(1, 1);
	b.printB();
	b.print();
	cin.get();
	return 0;
}