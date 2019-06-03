#include <iostream>
#include <thread>

using namespace std;

void ThreadFunc(string &prame);

int main()
{
	// 默认构造函数
	thread t1;
	
	cout << t1.get_id() << endl; // 线程id为0
	cout << t1.joinable() << endl; // 为0,表示不可以被join

	// 使用带参数构造函数
	thread t2(ThreadFunc, string("hello"));

	cout << t2.get_id() << endl; //
	cout << t2.joinable() << endl; //

	// thread对象在销毁之前,必须调用join,否则程序终止,或者detach
	//t2.join(); // 等待子线程执行完毕,类似于waitforsingleobject函数
	t2.detach();// 与当前线程分离,成为孤儿线程

	system("pause");
	return 0;
}

void ThreadFunc(string &prame)
{
	cout << prame.c_str() << endl;
}