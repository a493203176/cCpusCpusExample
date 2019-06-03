#include <iostream>
#include <thread>

using namespace std;

// �����ռ�this_thread �����е��̸߳������� get_id() yield() , sleep_for() sleep_util
using namespace std::this_thread;
// �����ռ�chrono��secondsģ���� millisecondsģ����
using namespace std::chrono;
void ThreadFun(string &param);

int main()
{
	thread t1(ThreadFun,string("hello"));
	cout << t1.get_id() << endl;

	// �ȴ����߳����
	t1.join();

	return 0;
}

void ThreadFun(string &param)
{
	cout <<"�߳�id:"<< get_id() << endl;
	while (true)
	{
		cout << param.c_str() << endl;
		//yield(); // ���߳�һ����С��ʱ��Ƭ,�������߳�����
		//sleep_for(seconds(1));// ���߳�˯��1��
		sleep_until(system_clock::now() + milliseconds(1000)); // ��ǰʱ��+1��
	}
}
