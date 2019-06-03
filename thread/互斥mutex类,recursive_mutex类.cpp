#include <stdio.h>
#include <thread>
#include <mutex>

using namespace std;
using namespace std::this_thread;
using namespace std::chrono;

int tickets = 100;
// ���廥�����
mutex m;

recursive_mutex m2; // ���Եݹ����
timed_mutex m3; // ����ָ����ס��ʱ��

void SellThread(string &str);


int main(void)
{
	thread t1(SellThread, string("��Ʊ����A"));
	thread t2(SellThread, string("��Ʊ����B"));

	t1.join();
	t2.join();

	system("pause");
	return 0;
}
void SellThread(string &str)
{
	while (tickets > 0)
	{
		// ����
		if (m3.try_lock_for(seconds(2)))
		{
			if (tickets > 0)
			{
				sleep_for(milliseconds(100));
				printf("%s ��Ʊ��%d \n", str.c_str(), tickets--);
			}
			m3.unlock();
		}
		

		sleep_for(milliseconds(100));
	}
}
