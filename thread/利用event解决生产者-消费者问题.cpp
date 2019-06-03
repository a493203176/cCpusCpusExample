#include <Windows.h>
#include <queue>
#include <process.h>

using namespace std;

// 有一个仓库
queue<int> store;
int StoreSize = 3; //仓库可以放3个货物
int ID = 1; // 货物起始ID

// 随机时间数组,模拟随机生产和消费的速度
int arr1[10] = { 2, 4, 7, 1 ,3, 6, 8, 1, 4, 2};
int arr2[10] = { 1, 5, 2, 1, 9, 6, 8, 3, 5, 8};

// 需要两个事件来通知
HANDLE hEvent1 = INVALID_HANDLE_VALUE; // 有货物时通知消费者取货物
HANDLE hEvent2 = INVALID_HANDLE_VALUE; // 仓库为空的时候,通知生产者开始生产


// 生产者
void  __cdecl ProducerThread(void * param);
// 消费者
void  __cdecl CunsumerThread(void * param);

int main(void)
{
	hEvent1 = CreateEvent(NULL, TRUE, TRUE, L"事件对象1");// 需要先开始生产
	hEvent2 = CreateEvent(NULL, TRUE, FALSE, L"事件对象2");// 一开始,仓库没货,取货等待


	uintptr_t t1 = _beginthread(ProducerThread, 0, NULL);
	uintptr_t t2 = _beginthread(CunsumerThread, 0, NULL);

	HANDLE hThreadSet[] = { (HANDLE)t1, (HANDLE)t2 };
	// 无限等待两个线程运行结束
	WaitForMultipleObjects(2, hThreadSet, TRUE, INFINITE);

	CloseHandle(hEvent1);
	CloseHandle(hEvent2);

	CloseHandle((HANDLE)t1);
	CloseHandle((HANDLE)t2);

	system("pause");

	return 0;
}

// 生产者
void  __cdecl ProducerThread(void * param)
{
	while (TRUE)
	{
		WaitForSingleObject(hEvent1, INFINITE);
		if (store.size() < StoreSize) // 有仓库空位
		{
			int id = ID++; // 货物id号
			store.push(id);// 把货物放置到仓库中
			printf("生产商品id : %d\n", id);
			Sleep(arr1[id%10] * 1000); // 模拟生产有时快,又是慢
		}
		else // 仓库满了
		{
			printf("仓库满了,无法生产商品\n");
			ResetEvent(hEvent1);// 把事件设为无信号事件
		}

		// 仓库有货物,可以通知消费者取货物
		if (store.size() > 0)
		{
			SetEvent(hEvent2);// 让消费者的事件有事件
		}
	}
}

//消费者
void  __cdecl CunsumerThread(void * param)
{
	while (TRUE)
	{
		WaitForSingleObject(hEvent2, INFINITE);
		if (store.size() > 0)
		{
			int commodity = store.front(); // 获取队列中货物,先进先出
			store.pop(); // 卸走货物,腾出空位
			printf("                   取出商品id : %d\n", commodity);
			Sleep(arr2[commodity % 10] * 1000);
		}
		else
		{
			printf("仓库空了,无法再取货物\n");
			ResetEvent(hEvent2);
		}

		// 说明仓库没有满,可以继续生产
		if (store.size() < 3) {
			SetEvent(hEvent1);
		}
	}
}