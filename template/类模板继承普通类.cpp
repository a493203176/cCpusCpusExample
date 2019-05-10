#include <iostream>

using namespace std;

class A 
{
public:
	void print() {
		cout << "我是普通类,a的值:"<<a << endl;
	}
	A(int _a) :a(_a) {

	}
private:
	int  a;
};

// 普通类继承模板类
template<typename T>
class B : public A
{
public:
	void printB() {
		cout << "我是模板类,a值" << a << endl;
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