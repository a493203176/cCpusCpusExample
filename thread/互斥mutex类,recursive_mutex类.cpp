#include <stdio.h>
#include <thread>
#include <mutex>

using namespace std;
using namespace std::this_thread;
using namespace std::chrono;

int tickets = 100;
// 定义互斥对象
mutex m;

recursive_mutex m2; // 可以递归加锁
timed_mutex m3; // 可以指定锁住的时间

void SellThread(string &str);


int main(void)
{
	thread t1(SellThread, string("售票窗口A"));
	thread t2(SellThread, string("售票窗口B"));

	t1.join();
	t2.join();

	system("pause");
	return 0;
}
void SellThread(string &str)
{
	while (tickets > 0)
	{
		// 加锁
		if (m3.try_lock_for(seconds(2)))
		{
			if (tickets > 0)
			{
				sleep_for(milliseconds(100));
				printf("%s 售票第%d \n", str.c_str(), tickets--);
			}
			m3.unlock();
		}
		

		sleep_for(milliseconds(100));
	}
}
