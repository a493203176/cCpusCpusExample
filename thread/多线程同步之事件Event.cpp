#include<process.h>
#include<Windows.h>
#include <stdio.h>

void __cdecl  SellThread1(void * param);
void __cdecl  SellThread2(void * param);

// 事件句柄
HANDLE hEvent = INVALID_HANDLE_VALUE;
// 100张票
int ticket = 100;
int main(void)
{
	printf("开始买票了!");

	// 创建事件,此刻为有信号状态
	// 自动重置信号状态,初始化为有信号状态,线程直接获取
	hEvent = CreateEvent(NULL, FALSE, TRUE, L"事件对象");

	// 将事件设置为无信号状态
	//ResetEvent(hEvent);

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
	// 进入临界区,禁止其他线程访问

	while (ticket > 0)
	{
		Sleep(10);
		// 如果事件对象为有信号状态(没有线程拥有它,则线程可以获取它执行)
		// 自动重置的事件对象,调用了WaitForSingleObject之后,自动重置为无信号
		WaitForSingleObject(hEvent, INFINITE);
		if (ticket > 0)
		{
			// CPU恰合执行到这里,这个时候线程时间片到了,并且此时还剩最后一张票
			printf("%s 卖出第%d张票!\n", name, ticket--);
		}

		// SetEvent让事件对象变成有信号状态
		SetEvent(hEvent);
	}

}
void __cdecl  SellThread2(void * param)
{
	char * name = (char *)param;
	// 进入临界区,禁止其他线程访问

	while (ticket > 0)
	{
		Sleep(10);
		// 如果事件对象为有信号状态(没有线程拥有它,则线程可以获取它执行)
		// 自动重置的事件对象,调用了WaitForSingleObject之后,自动重置为无信号
		WaitForSingleObject(hEvent, INFINITE);
		if (ticket > 0)
		{
			// CPU恰合执行到这里,这个时候线程时间片到了,并且此时还剩最后一张票
			printf("%s 卖出第%d张票!\n", name, ticket--);
		}

		// SetEvent让事件对象变成有信号状态
		SetEvent(hEvent);
	}
}
