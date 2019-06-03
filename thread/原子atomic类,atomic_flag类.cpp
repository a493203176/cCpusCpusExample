#include <iostream>
#include <atomic> // 原子操作头文件
#include <thread>

using namespace std;
using namespace std::this_thread;
using namespace std::chrono;


//unsigned long N = 0;
atomic<unsigned long> N = 0; // 用atomic保证对N的操作原子性

void  ThreadFun1();
void  ThreadFun2();

int main()
{
	// 每个线程100次+1
	thread t1(ThreadFun1);
	thread t2(ThreadFun1);

	t1.join();
	t2.join();
	
	cout << N << endl; // 应该是200
	system("pause");
	return 0;
}


void  ThreadFun1()
{

	for (unsigned long i = 0; i < 1000000; i++)
	{
		++N; // 线程并发导致 加操作重叠,不是原子因此肯定少于2000000
	}

		//sleep_for(seconds(1));
}

void  ThreadFun2()
{
	
	for (int i = 0; i < 100; i++)
	{
		++N;
	}

	//sleep_for(seconds(1));
	
}

