#include <iostream>

using namespace std;

template <int N>
class Sum
{
public:
	enum { // ��ö������,��Ϊ�ñ���,�������ٱ����ڵ��µ�( C++���Ա������ʼ�����ܷ����ඨ����)
		value = N + Sum<N - 1>::value
	};
};

// ��Ҫ�ػ�0,�ػ�������,�����ͣ������,����ػ���-1,������-1
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