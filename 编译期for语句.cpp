#include <iostream>

using namespace std;

// 主模板
template <int N>// 非类型的参数
struct For
{
	static inline void print()
	{
		cout << "for循环执行" << N << "次" << endl;
		For<N - 1>::print(); //这句触发递归的核心,从而产生循环
	}
};

// 利用全特化终止递归
template <>
struct For<0>
{
	static inline void  print()
	{
		cout << "for循环执行" << 0 << "次" << endl;
	}
};

int main(void)
{
	// 编译期的for循环
	For<10>::print();
	cin.get();
	return 0;
}