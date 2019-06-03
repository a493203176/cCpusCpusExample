#include <atomic>
#include <iostream>
#include <thread>
#include <vector>


using namespace std;

atomic<bool> reday = false; // 是否枪响
atomic_flag win = ATOMIC_FLAG_INIT; // 终点线

void RunThread(int id)
{
	// 枪没响,不能跑
	while (!reday)
	{
		this_thread::yield();  // 让其他线程先执行
	}

	for (unsigned long i = 0; i < 1000000; i++) {
	}

	// 如果没有被设置过,返回false
	if (!win.test_and_set())// 调用后会将它设置
	{
		cout <<"第"<< id <<"号选手赢得第一名"<< endl;
	}
}

int main(void)
{
	// 十个选手赛跑
	vector<thread> vecPlayers;

	for (int i = 0; i < 10; i++)
	{
		vecPlayers.emplace_back(thread(RunThread,i));
	}
	cout << "10个选手已经准备好!" << endl;

	// 准备发令:预备跑
	this_thread::sleep_for(chrono::seconds(3));
	cout << "3,2,1 预备跑!" << endl;
	reday = true;

	// 等待所有选手跑玩
	for (thread &t : vecPlayers) {
		t.join();
	}
	system("pause");
	return 0;
}