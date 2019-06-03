#include <Windows.h>
#include <stdio.h>

DWORD  WINAPI ThreadFun1(LPVOID param);
DWORD  WINAPI ThreadFun2(LPVOID param);

// 自定义消息(必须是自定义消息以上的数值)
#define MY_MSG WM_USER+1

struct Messsgae
{
	int a;
	int b;
};
Messsgae msg_thread;
int main(void)
{
	DWORD threadID = 0;
	// 获取第一个线程的ID,方便第二个线程给第一个线程发消息
	HANDLE t1 = CreateThread(NULL, 0, ThreadFun1, NULL, 0, &threadID);
	HANDLE t2 = CreateThread(NULL, 0, ThreadFun2, &threadID, 0, NULL);

	HANDLE hArr[] = { t1, t2 };
	WaitForMultipleObjects(2, hArr, TRUE, INFINITE);

	system("pause");
	return 0;
}

DWORD  WINAPI ThreadFun1(LPVOID param)
{
	// 接收第二个线程发来的消息

	MSG msg;

	//while (GetMessage(&msg, NULL, 0, 0)) // 如果有消息,继续,否则阻塞
	//while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	//{ 
	//	switch(msg.message)
	//	{
	//		case MY_MSG:
	//			printf("收到消息: %d\n", (int)msg.wParam);
	//			break;
	//		default:
	//			break;
	//	}
	//}
	Messsgae * pMsg = NULL;
	// peekmessage的用法
	while (TRUE)
	{
		// 马上就返回,不阻塞线程
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{ 
			switch(msg.message)
			{
				case MY_MSG:
					pMsg = (Messsgae *)msg.wParam;
					
					printf("收到消息: %d %d\n", pMsg->a, pMsg->b);
					break;
				case WM_QUIT:
					printf("收到WM_QUIT消息,退出\n");
					return 0;
					break;
				default:
					break;
			}
		}
	}
	return 0;
	
}
DWORD  WINAPI ThreadFun2(LPVOID param)
{
	LPWORD pthreadID = (LPWORD)param;
	int N = 1;
	// 给第一个线程发消息
	while (TRUE)
	{
		if (N <= 10)
		{
			msg_thread.a = N++;
			msg_thread.b = N++;
			PostThreadMessage(*pthreadID, MY_MSG, (WPARAM)&msg_thread, NULL);
		}
		else
		{
			//让第一个线程退出
			PostThreadMessage(*pthreadID, WM_QUIT, NULL, NULL);
			return 0;
		}

		Sleep(1000);
	}

	return 0;
}