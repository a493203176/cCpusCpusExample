#include <iostream>
#include <atomic> // ԭ�Ӳ���ͷ�ļ�
#include <thread>

using namespace std;
using namespace std::this_thread;
using namespace std::chrono;


//unsigned long N = 0;
atomic<unsigned long> N = 0; // ��atomic��֤��N�Ĳ���ԭ����

void  ThreadFun1();
void  ThreadFun2();

int main()
{
	// ÿ���߳�100��+1
	thread t1(ThreadFun1);
	thread t2(ThreadFun1);

	t1.join();
	t2.join();
	
	cout << N << endl; // Ӧ����200
	system("pause");
	return 0;
}


void  ThreadFun1()
{

	for (unsigned long i = 0; i < 1000000; i++)
	{
		++N; // �̲߳������� �Ӳ����ص�,����ԭ����˿϶�����2000000
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

