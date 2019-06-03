#include <atomic>
#include <iostream>
#include <thread>
#include <vector>


using namespace std;

atomic<bool> reday = false; // �Ƿ�ǹ��
atomic_flag win = ATOMIC_FLAG_INIT; // �յ���

void RunThread(int id)
{
	// ǹû��,������
	while (!reday)
	{
		this_thread::yield();  // �������߳���ִ��
	}

	for (unsigned long i = 0; i < 1000000; i++) {
	}

	// ���û�б����ù�,����false
	if (!win.test_and_set())// ���ú�Ὣ������
	{
		cout <<"��"<< id <<"��ѡ��Ӯ�õ�һ��"<< endl;
	}
}

int main(void)
{
	// ʮ��ѡ������
	vector<thread> vecPlayers;

	for (int i = 0; i < 10; i++)
	{
		vecPlayers.emplace_back(thread(RunThread,i));
	}
	cout << "10��ѡ���Ѿ�׼����!" << endl;

	// ׼������:Ԥ����
	this_thread::sleep_for(chrono::seconds(3));
	cout << "3,2,1 Ԥ����!" << endl;
	reday = true;

	// �ȴ�����ѡ������
	for (thread &t : vecPlayers) {
		t.join();
	}
	system("pause");
	return 0;
}