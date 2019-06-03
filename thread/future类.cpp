#include <iostream>
#include <future>
#include <thread>

using namespace std;
using namespace std::this_thread;
using namespace std::chrono;

// 费时的操作
int sum(int a, int b)
{
	cout << "开始计算:" << endl;

	sleep_for(seconds(5));

	return a + b;
}

int main()
{
	// 将来的结果
	future<int> result = async(sum, 1, 2);// move赋值操作

	result.wait(); // 等待结果算出,算出后继续执行
	cout << "算出结果:" << endl;
	int sum = result.get();
	cout << "最终的结果是:" << sum << endl;

	system("pause");
	return 0;
}