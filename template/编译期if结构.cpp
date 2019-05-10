#include <iostream>

using namespace std;

// 主模板
template <bool> // 非类型参数
struct If;

// 全特化
template <>
struct If<true>
{
	static void Fun() {
		cout << "If<true> Func(()" << endl;
	}
};

template <>
struct If<false>
{
	static void Fun() {
		cout << "If<false> Func(()" << endl;
	}
};

int main(void)
{
	// 编译器if结构
	If<true>::Fun();
	If<false>::Fun();
	
	cin.get();
	return 0;
}