#include <iostream>
#include <future>
#include <thread>

using namespace std;
using namespace std::this_thread;
using namespace std::chrono;

// ��ʱ�Ĳ���
int sum(int a, int b)
{
	cout << "��ʼ����:" << endl;

	sleep_for(seconds(5));

	return a + b;
}

int main()
{
	// �����Ľ��
	future<int> result = async(sum, 1, 2);// move��ֵ����

	result.wait(); // �ȴ�������,��������ִ��
	cout << "������:" << endl;
	int sum = result.get();
	cout << "���յĽ����:" << sum << endl;

	system("pause");
	return 0;
}