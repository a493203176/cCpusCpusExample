#include <iostream>
#include <future>
#include <thread>

using namespace std;
using namespace std::this_thread;
using namespace std::chrono;

int work(int a, int b)
{
	cout << "开始计算" << endl;
	// 处理费时操作
	sleep_for(seconds(5));

	return a + b;
}

int main(void)
{
	// packaged_task包装了可调用的目标
	packaged_task<int(int, int)> pack(work);

	future<int> result =  pack.get_future(); // 获取packeted_task内部future

	thread t1(move(pack), 1, 2);//将packaged_task给线程执行
	t1.detach();

	int sum  = result.get();
	cout << "结果:" << sum << endl;
	system("pause");
	return 0;
}