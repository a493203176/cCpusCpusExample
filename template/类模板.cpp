#include <iostream>

using namespace std;

template <typename T>
class Math
{
public:
	Math() {}
	T sum(T a, T b);
};

template <typename T>
T Math<T>::sum(T a, T b)
{
	return a + b;
}

int main()
{
	//模板类,实例化类模板
	Math<int> i;
	Math<float > f;
	Math<double > d;
	cout << i.sum(1, 2) << endl;
	cout << f.sum(1.11f, 2.233f) << endl;
	cout << d.sum(1.11, 2.233) << endl;
	cin.get();
	return 0;
}