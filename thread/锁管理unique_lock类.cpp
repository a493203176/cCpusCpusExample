#include <iostream>
#include <mutex>
#include <thread>
#include <stdexcept>

using namespace std;
using namespace std::chrono;
using namespace std::this_thread;

mutex m;


void ThreadFun()
{
	try
	{
		for (int i = 0; i < 10; i++) {
			/*m.lock();*/
			unique_lock<mutex> lck(m);// 哪怕发生异常也是可以安全解锁,因为lck会析构,调用unlock

			if (i == 3) throw logic_error("发现异常了");

			cout << "A打印" << i << endl;
		
			lck.unlock(); // 可以控制解锁
			//m.unlock(); // 抛出异常,导致没有unlock,使得B无法获取mutex,死锁
			sleep_for(seconds(1));
		}
	}
	catch (logic_error &e) {
		cout << "错误" << e.what() << endl;
	}

}
void ThreadFun2()
{
	for (int i = 0; i < 10; i++) {
	
		//m.lock();
		unique_lock<mutex> lck(m);
	
		cout << "B打印" << i << endl;
		lck.unlock();
		sleep_for(seconds(1));
		//m.unlock();
	}
}

int main(void)
{
	thread t1(ThreadFun);
	thread t2(ThreadFun2);

	t1.join();
	t2.join();

	system("pause");
	return 0;
}