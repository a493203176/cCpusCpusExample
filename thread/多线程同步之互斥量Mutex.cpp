#include<process.h>
#include<Windows.h>
#include <stdio.h>

void __cdecl  SellThread1(void * param);
void __cdecl  SellThread2(void * param);

HANDLE hMutex = INVALID_HANDLE_VALUE;

// 100张票
int ticket = 100;
int main(void)
{
	printf("开始买票了!");

	// 创建互斥体
	hMutex = CreateMutex(NULL, FALSE, L"售票互斥体");

	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		printf("只允许一个进程访问\n");
		//如果已有互斥量存在则释放句柄
		CloseHandle(hMutex);
		system("pause");
		return 0;
	}

	// 创建两个售票窗口
	uintptr_t t1 = _beginthread(SellThread1, 0, "售票窗口A");
	uintptr_t t2 = _beginthread(SellThread2, 0, "售票窗口B");

	// 无线等待两个线程全部执行完毕
	HANDLE hThreads[] = { (HANDLE)t1, (HANDLE)t2 };
	WaitForMultipleObjects(2, hThreads, true, INFINITE);


	printf("卖票结束!");
	system("pause");
	return 0;
}


void __cdecl  SellThread1(void * param)
{
	char * name = (char *)param;

	while (ticket > 0)
	{
		Sleep(10);

		// 如果这个互斥体为有信号状态(没有线程拥有它),则获取它后继续执行
		WaitForSingleObject(hMutex, INFINITE);
		if (ticket > 0)
		{
			// CPU恰合执行到这里,这个时候线程时间片到了,并且此时还剩最后一张票
			printf("%s 卖出第%d张票!\n", name, ticket--);
		}
		// 释放对互斥体的拥有权,它变成有信号状态
		ReleaseMutex(hMutex);
			
	}

}
void __cdecl  SellThread2(void * param)
{
	char * name = (char *)param;

	while (ticket > 0)
	{
		Sleep(10);

		WaitForSingleObject(hMutex, INFINITE);
		if (ticket > 0)
		{
			// CPU恰合执行到这里,这个时候线程时间片到了,并且此时还剩最后一张票
			printf("%s 卖出第%d张票!\n", name, ticket--);
		}
		ReleaseMutex(hMutex);
	}

}
