#include <iostream>

using namespace std;

// ��ģ��
template <int> 
struct SwtichT
{
	static void Fun() {
		cout << "ִ��default���" << endl;
	}
};

template <>
struct SwtichT<1>
{
	static void Fun() {
		cout << "SwtichT<1>" << endl;
	}
};


template <>
struct SwtichT<2>
{
	static void Fun() {
		cout << "SwtichT<2>" << endl;
	}
};

int main(void)
{
	// ������switch�ṹ
	SwtichT<1>::Fun();
	SwtichT<2>::Fun();
	SwtichT<4>::Fun();
	cin.get();
	return 0;
}