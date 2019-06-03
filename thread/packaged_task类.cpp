#include <iostream>
#include <future>
#include <thread>

using namespace std;
using namespace std::this_thread;
using namespace std::chrono;

int work(int a, int b)
{
	cout << "��ʼ����" << endl;
	// �����ʱ����
	sleep_for(seconds(5));

	return a + b;
}

int main(void)
{
	// packaged_task��װ�˿ɵ��õ�Ŀ��
	packaged_task<int(int, int)> pack(work);

	future<int> result =  pack.get_future(); // ��ȡpacketed_task�ڲ�future

	thread t1(move(pack), 1, 2);//��packaged_task���߳�ִ��
	t1.detach();

	int sum  = result.get();
	cout << "���:" << sum << endl;
	system("pause");
	return 0;
}