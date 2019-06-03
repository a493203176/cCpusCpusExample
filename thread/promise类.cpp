#include <iostream>
#include <thread>
#include <mutex>
#include <future>

using namespace std;
using namespace std::this_thread;
using namespace std::chrono;


void work(promise<int> & prom)
{
	cout << "开始计算:" << endl;
	sleep_for(seconds(5));

	try
	{
		throw runtime_error("运行时异常");
	}
	catch (runtime_error &e)
	{
		// promise设置异常
		prom.set_exception(current_exception());
	}

	// 设置结果值
	prom.set_value(101); // 设置结果
}

int main(void)
{
	// 定义一个promise
	promise<int> prom;
	// future和promise搭配使用,类似于aynsc
	future<int> result = prom.get_future();

	//std::thread::thread<void(__cdecl &)(std::promise<int> &), std::promise<int>&>(_Fn, std::promise<int> &)”的引用
	//thread t1(work,prom);
	thread t1(work, ref(prom));
	t1.detach();

	try
	{
		int sum = result.get();
		cout << "获取结果:" << sum << endl;
	}
	catch (exception &e)
	{
		cout <<"结果异常:"<< e.what() << endl;
	}

	system("pause");
	return 0;
}