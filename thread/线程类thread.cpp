#include <iostream>
#include <thread>

using namespace std;

void ThreadFunc(string &prame);

int main()
{
	// Ĭ�Ϲ��캯��
	thread t1;
	
	cout << t1.get_id() << endl; // �߳�idΪ0
	cout << t1.joinable() << endl; // Ϊ0,��ʾ�����Ա�join

	// ʹ�ô��������캯��
	thread t2(ThreadFunc, string("hello"));

	cout << t2.get_id() << endl; //
	cout << t2.joinable() << endl; //

	// thread����������֮ǰ,�������join,���������ֹ,����detach
	//t2.join(); // �ȴ����߳�ִ�����,������waitforsingleobject����
	t2.detach();// �뵱ǰ�̷߳���,��Ϊ�¶��߳�

	system("pause");
	return 0;
}

void ThreadFunc(string &prame)
{
	cout << prame.c_str() << endl;
}