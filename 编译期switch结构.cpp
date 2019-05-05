#include <iostream>

using namespace std;

// 主模板
template <int> 
struct SwtichT
{
	static void Fun() {
		cout << "执行default语句" << endl;
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
	// 编译期switch结构
	SwtichT<1>::Fun();
	SwtichT<2>::Fun();
	SwtichT<4>::Fun();
	cin.get();
	return 0;
}