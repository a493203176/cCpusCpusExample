#include <Windows.h>
#include <stdio.h>

DWORD WINAPI TheadFunc(LPVOID lpThreadParameter);

int main(void)
{
	printf("���߳̿�ͷ\n");
	HANDLE hThead = CreateThread(NULL, 0, TheadFunc, NULL, 0, NULL);
	DWORD exitID;
	GetExitCodeThread(hThead, &exitID);
	if (exitID == STILL_ACTIVE) // ����߳�û�н���,����STILL_ACTIVE
	{
		printf("���߳�û���˳�\n");
	}



	DWORD ret = WaitForSingleObject(hThead, 3000);
	if (ret == WAIT_TIMEOUT) {
		printf("WaitForSingleObject�ȴ����߳��˳���ʱ\n");
	}

	// ǿ����ֹ�߳�,����ʹ��
	TerminateThread(hThead, 888);

	// ���ߵȴ�,�������߳����н���
	WaitForSingleObject(hThead, INFINITE);

	GetExitCodeThread(hThead, &exitID);
	printf("���߳��˳���:%d\n", exitID);
	printf("���߳̽�β\n");
	system("pause");
	return 0;
}


DWORD WINAPI TheadFunc(LPVOID lpThreadParameter)
{
	int n = 0;
	while (++n < 6)
	{

		printf("��%d�����߳� hello!\n",n);
		//if (n == 3) {
		//	// �˳��߳�,�˳���666,����ʹ��
		//	ExitThread(666);
		//}
		Sleep(1000);
	}
	return 0;
}