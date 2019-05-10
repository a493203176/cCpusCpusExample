#include <iostream>

using namespace std;

template <int N>
class Sum
{
public:
	enum { // 用枚举类型,因为用变量,它不会再编译期导致的( C++类成员变量初始化不能放在类定义中)
		value = N + Sum<N - 1>::value
	};
};

// 需要特化0,特化到哪里,定义就停在哪里,如果特化到-1,则结果到-1
template <>
class Sum<0>
{
public:
	enum {
		value = 0
	};
};

int main(void)
{
	cout << Sum<100>::value << endl;
	cin.get();
	return 0;
}