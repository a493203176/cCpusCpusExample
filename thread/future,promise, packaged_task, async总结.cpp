#include <thread>
#include <future>
#include <iostream>

using namespace std;
using namespace std::this_thread;
using namespace std::chrono;

void work1(promise<int> &prom, int a,int b)
{
	cout << "work1 ��ʼ����" << endl;
	sleep_for(seconds(2));

	prom.set_value(a + b);
}

int work2(int a, int b)
{
	cout << "work2 ��ʼ����" << endl;
	sleep_for(seconds(2));

	return a + b;
}


int work3(int a, int b)
{
	cout << "work3 ��ʼ����" << endl;
	sleep_for(seconds(2));

	return a + b;
}


int main()
{
	// promise�ڲ���װ��һ��ֵ
	promise<int> prom;
	future<int> f1 = prom.get_future(); 

	thread t1(work1, ref(prom), 1, 2);
	t1.detach();
	f1.wait(); //�ȴ�ֵ����

	int sum = f1.get();
	cout << "������:" << sum << endl;

	// packaged_task
	packaged_task<int(int, int)> task(work2);
	future<int> f2 = task.get_future();

	thread t2(move(task), 1, 2);
	t2.detach();
	
	cout << "������2:" << f2.get() << endl;

	// async�ڲ���һ���߳�
	future<int> f3 = async(work3, 1, 2);
	f3.wait(); //�ȴ����
	cout << "������3:" << f3.get() << endl;

	system("pause");
	return 0;
}