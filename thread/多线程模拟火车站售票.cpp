#include<process.h>
#include<Windows.h>
#include <stdio.h>

void __cdecl  SellThread1(void * param);
void __cdecl  SellThread2(void * param);

// 临界区结构
CRITICAL_SECTION crticalSection;
// 100张票
int ticket = 100;
int main(void)
{
	printf("开始买票了!");

	// 初始化临界区
	InitializeCriticalSection(&crticalSection);

	// 创建两个售票窗口
	uintptr_t t1 = _beginthread(SellThread1, 0, "售票窗口A");
	uintptr_t t2 = _beginthread(SellThread2, 0, "售票窗口B");

	// 无线等待两个线程全部执行完毕
	HANDLE hThreads[] = { (HANDLE)t1, (HANDLE)t2 };
	WaitForMultipleObjects(2, hThreads, true, INFINITE);

	// 删除临界区资源
	DeleteCriticalSection(&crticalSection);
	printf("卖票结束!");
	system("pause");
	return 0;
}


void __cdecl  SellThread1(void * param)
{
	char * name = (char *)param;
	// 进入临界区,禁止其他线程访问

	while (ticket > 0)
	{
		Sleep(10);

		if (TryEnterCriticalSection(&crticalSection))
		{
			if (ticket > 0)
			{
				// CPU恰合执行到这里,这个时候线程时间片到了,并且此时还剩最后一张票
				printf("%s 卖出第%d张票!\n", name, ticket--);
			}

			// 离开临界区
			LeaveCriticalSection(&crticalSection);
		}
			
	}

}
void __cdecl  SellThread2(void * param)
{
	char * name = (char *)param;
	// 进入临界区,禁止其他线程访问

	while (ticket > 0)
	{
		Sleep(10);
		//尝试进入临界区,不会阻塞
		if (TryEnterCriticalSection(&crticalSection))
		{
			if (ticket > 0)
			{
				// CPU恰合执行到这里,这个时候线程时间片到了,并且此时还剩最后一张票
				printf("%s 卖出第%d张票!\n", name, ticket--);
			}

			// 离开临界区
			LeaveCriticalSection(&crticalSection);
		}

	}

}
