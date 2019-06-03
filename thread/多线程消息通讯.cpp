#include <Windows.h>
#include <stdio.h>

DWORD  WINAPI ThreadFun1(LPVOID param);
DWORD  WINAPI ThreadFun2(LPVOID param);

// �Զ�����Ϣ(�������Զ�����Ϣ���ϵ���ֵ)
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
	// ��ȡ��һ���̵߳�ID,����ڶ����̸߳���һ���̷߳���Ϣ
	HANDLE t1 = CreateThread(NULL, 0, ThreadFun1, NULL, 0, &threadID);
	HANDLE t2 = CreateThread(NULL, 0, ThreadFun2, &threadID, 0, NULL);

	HANDLE hArr[] = { t1, t2 };
	WaitForMultipleObjects(2, hArr, TRUE, INFINITE);

	system("pause");
	return 0;
}

DWORD  WINAPI ThreadFun1(LPVOID param)
{
	// ���յڶ����̷߳�������Ϣ

	MSG msg;

	//while (GetMessage(&msg, NULL, 0, 0)) // �������Ϣ,����,��������
	//while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	//{ 
	//	switch(msg.message)
	//	{
	//		case MY_MSG:
	//			printf("�յ���Ϣ: %d\n", (int)msg.wParam);
	//			break;
	//		default:
	//			break;
	//	}
	//}
	Messsgae * pMsg = NULL;
	// peekmessage���÷�
	while (TRUE)
	{
		// ���Ͼͷ���,�������߳�
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{ 
			switch(msg.message)
			{
				case MY_MSG:
					pMsg = (Messsgae *)msg.wParam;
					
					printf("�յ���Ϣ: %d %d\n", pMsg->a, pMsg->b);
					break;
				case WM_QUIT:
					printf("�յ�WM_QUIT��Ϣ,�˳�\n");
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
	// ����һ���̷߳���Ϣ
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
			//�õ�һ���߳��˳�
			PostThreadMessage(*pthreadID, WM_QUIT, NULL, NULL);
			return 0;
		}

		Sleep(1000);
	}

	return 0;
}