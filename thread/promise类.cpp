#include <iostream>
#include <thread>
#include <mutex>
#include <future>

using namespace std;
using namespace std::this_thread;
using namespace std::chrono;


void work(promise<int> & prom)
{
	cout << "��ʼ����:" << endl;
	sleep_for(seconds(5));

	try
	{
		throw runtime_error("����ʱ�쳣");
	}
	catch (runtime_error &e)
	{
		// promise�����쳣
		prom.set_exception(current_exception());
	}

	// ���ý��ֵ
	prom.set_value(101); // ���ý��
}

int main(void)
{
	// ����һ��promise
	promise<int> prom;
	// future��promise����ʹ��,������aynsc
	future<int> result = prom.get_future();

	//std::thread::thread<void(__cdecl &)(std::promise<int> &), std::promise<int>&>(_Fn, std::promise<int> &)��������
	//thread t1(work,prom);
	thread t1(work, ref(prom));
	t1.detach();

	try
	{
		int sum = result.get();
		cout << "��ȡ���:" << sum << endl;
	}
	catch (exception &e)
	{
		cout <<"����쳣:"<< e.what() << endl;
	}

	system("pause");
	return 0;
}