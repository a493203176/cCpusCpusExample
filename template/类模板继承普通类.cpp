#include <iostream>

using namespace std;

class A 
{
public:
	void print() {
		cout << "������ͨ��,a��ֵ:"<<a << endl;
	}
	A(int _a) :a(_a) {

	}
private:
	int  a;
};

// ��ͨ��̳�ģ����
template<typename T>
class B : public A
{
public:
	void printB() {
		cout << "����ģ����,aֵ" << a << endl;
	}
	B(T _a,int _b) :a(_a),A(_b) {

	}
private:
	T  a;
};

int main(void)
{
	B<float> b(1.1,101);
	b.print();
	b.printB();
	cin.get();
	return 0;
}