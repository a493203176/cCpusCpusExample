#include <iostream>

using namespace std;

// �ⲿ��ģ��
template <typename T1>
class Outer
{
public:
	// �ڲ���ģ��
	template<typename T2> 
	class Innter {
	private:
		T2 i;
	public:
		void print();
	};

public:
	void print() {
		cout << "Outer�ⲿ��" << endl;
	}
private:
	T1 o;
};

// ��Ҫ���������޶�,ͬʱ��Ҫ����ģ������
template <typename T1>
template <typename T2>
void Outer<T1>::Innter<T2>::print(void)
{
	cout << "Innter�ڲ���" << endl;
}

int main(void)
{
	// �ⲿ��
	Outer<int> a;
	a.print();

	// �ڲ���
	Outer<int>::Innter<int> i;
	i.print();

	cin.get();
	return 0;
}