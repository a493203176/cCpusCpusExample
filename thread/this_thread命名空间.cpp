#include <iostream>
#include <thread>

using namespace std;

// 命名空间this_thread 有所有的线程辅助函数 get_id() yield() , sleep_for() sleep_util
using namespace std::this_thread;
// 命名空间chrono有seconds模板类 milliseconds模板类
using namespace std::chrono;
void ThreadFun(string &param);

int main()
{
	thread t1(ThreadFun,string("hello"));
	cout << t1.get_id() << endl;

	// 等待子线程完成
	t1.join();

	return 0;
}

void ThreadFun(string &param)
{
	cout <<"线程id:"<< get_id() << endl;
	while (true)
	{
		cout << param.c_str() << endl;
		//yield(); // 让线程一个极小的时间片,给其他线程运行
		//sleep_for(seconds(1));// 让线程睡眠1秒
		sleep_until(system_clock::now() + milliseconds(1000)); // 当前时间+1秒
	}
}
