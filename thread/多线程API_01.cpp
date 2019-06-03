#include <Windows.h> // 线程相关头文件
#include <iostream>

using namespace std;

// 线程处理函数,window标准调用约定_stdcall
DWORD WINAPI TheadFun(LPVOID lpThreadParameter);

int main(void)
{
	DWORD threadId  = 0;
    HANDLE hThread =   CreateThread(NULL,// 设为NULL使用默认安全性
		0,  // 如果为0,默认堆栈大小
		TheadFun,//线程处理函数,函数名就是函数指针
		"hello", // 向线程传入的参数
		0, // 创建后马上运行
		&threadId // 线程id
		);
	if (hThread == nullptr) {
		cout << "线程创建失败:" << GetLastError() << endl;
	}
	cout << "线程的句柄:" << hThread << endl;
	cout << "线程的id:" << threadId << endl;

	cout << "主线程ID:" << GetCurrentThreadId() << endl;

	// 关闭线程句柄,引用计数-1,并没有结束线程
	//CloseHandle(hThread); // 表示以后不再引用句柄

	getchar();

	// 挂起线程
	SuspendThread(hThread);

	getchar();

	// 恢复线程执行
	ResumeThread(hThread);

	system("pause");
	return 0;
}

DWORD WINAPI TheadFun(LPVOID lpThreadParameter)
{
	char * str = static_cast<char *>(lpThreadParameter);
	while (TRUE)
	{
		cout << "线程处理函数中:" << str << endl;
		cout << "子线程ID:" << GetCurrentThreadId() << endl;
		Sleep(1000);  // 修改1秒
	}

	return 0;
}