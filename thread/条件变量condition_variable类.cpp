#include <thread>
#include <iostream>
#include <mutex>
#include <condition_variable>

using namespace std;
using namespace std::this_thread;
using namespace std::chrono;

condition_variable cv; // 仅支持unique_lock<mutex> 作为wait参数
condition_variable_any cvAny; // 支持任何locakable参数
mutex m;


void ThreadFun(int id)
{
	unique_lock<mutex> lck(m);

	//cv.wait(lck); // 等待被唤醒

	cvAny.wait(lck);
	cout << "线程ID:" << id <<"执行"<< endl;
}

int main()
{
	thread t1(ThreadFun, 1);
	thread t2(ThreadFun, 2);
	thread t3(ThreadFun, 3);

	cout << "3秒后唤醒:" << endl;

	sleep_for(seconds(3)); // 3秒之后唤醒所有线程

	//cv.notify_all();// 唤醒所有
	//cv.notify_one();
	//cv.notify_one();

	cvAny.notify_all();

	t1.join();
	t2.join();
	t3.join();

	system("pause");
	return 0;
}