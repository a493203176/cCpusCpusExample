#include <iostream>

using namespace std;

// ��ģ��
template <bool> // �����Ͳ���
struct If;

// ȫ�ػ�
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
	// ������if�ṹ
	If<true>::Fun();
	If<false>::Fun();
	
	cin.get();
	return 0;
}