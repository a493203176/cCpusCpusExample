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
			unique_lock<mutex> lck(m);// ���·����쳣Ҳ�ǿ��԰�ȫ����,��Ϊlck������,����unlock

			if (i == 3) throw logic_error("�����쳣��");

			cout << "A��ӡ" << i << endl;
		
			lck.unlock(); // ���Կ��ƽ���
			//m.unlock(); // �׳��쳣,����û��unlock,ʹ��B�޷���ȡmutex,����
			sleep_for(seconds(1));
		}
	}
	catch (logic_error &e) {
		cout << "����" << e.what() << endl;
	}

}
void ThreadFun2()
{
	for (int i = 0; i < 10; i++) {
	
		//m.lock();
		unique_lock<mutex> lck(m);
	
		cout << "B��ӡ" << i << endl;
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