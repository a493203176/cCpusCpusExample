#include <Windows.h>
#include <stdio.h>

DWORD WINAPI ThreadFun1(LPVOID param);
DWORD WINAPI ThreadFun2(LPVOID param);

// ����Ϊ��̬TLS(�̱߳��ش洢����)
__declspec(thread) int N = 0; // ÿ���߳��е�ֵ����Ӱ��

int main(void)
{
	HANDLE hThread1 = CreateThread(NULL, 0, ThreadFun1, NULL, 0, NULL);
	HANDLE hThread2 = CreateThread(NULL, 0, ThreadFun2, NULL, 0, NULL);

	HANDLE hArr[] = { hThread1, hThread2 };

	WaitForMultipleObjects(2, hArr, TRUE, INFINITE);

	system("pause");
	return 0;
}

DWORD WINAPI ThreadFun1(LPVOID param)
{
	while (TRUE)
	{
		// ÿ���̶߳����Լ���N
		printf("�߳�A��ӡ: %d \n", ++N);
		Sleep(1000);
	}
}

DWORD WINAPI ThreadFun2(LPVOID param)
{
	while (TRUE)
	{
		printf("�߳�B��ӡ: %d \n", N);
		Sleep(1000);
	}
}