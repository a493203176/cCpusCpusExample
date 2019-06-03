#include <thread>
#include <iostream>
#include <mutex>
#include <condition_variable>

using namespace std;
using namespace std::this_thread;
using namespace std::chrono;

condition_variable cv; // ��֧��unique_lock<mutex> ��Ϊwait����
condition_variable_any cvAny; // ֧���κ�locakable����
mutex m;


void ThreadFun(int id)
{
	unique_lock<mutex> lck(m);

	//cv.wait(lck); // �ȴ�������

	cvAny.wait(lck);
	cout << "�߳�ID:" << id <<"ִ��"<< endl;
}

int main()
{
	thread t1(ThreadFun, 1);
	thread t2(ThreadFun, 2);
	thread t3(ThreadFun, 3);

	cout << "3�����:" << endl;

	sleep_for(seconds(3)); // 3��֮���������߳�

	//cv.notify_all();// ��������
	//cv.notify_one();
	//cv.notify_one();

	cvAny.notify_all();

	t1.join();
	t2.join();
	t3.join();

	system("pause");
	return 0;
}