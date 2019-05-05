#include <iostream>

using namespace std;

// 外部类模板
template <typename T1>
class Outer
{
public:
	// 内部类模板
	template<typename T2> 
	class Innter {
	private:
		T2 i;
	public:
		void print();
	};

public:
	void print() {
		cout << "Outer外部类" << endl;
	}
private:
	T1 o;
};

// 需要两级类名限定,同时需要两级模板声明
template <typename T1>
template <typename T2>
void Outer<T1>::Innter<T2>::print(void)
{
	cout << "Innter内部类" << endl;
}

int main(void)
{
	// 外部类
	Outer<int> a;
	a.print();

	// 内部类
	Outer<int>::Innter<int> i;
	i.print();

	cin.get();
	return 0;
}