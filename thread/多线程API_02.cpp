#include <Windows.h>
#include <stdio.h>

DWORD WINAPI TheadFunc(LPVOID lpThreadParameter);

int main(void)
{
	printf("主线程开头\n");
	HANDLE hThead = CreateThread(NULL, 0, TheadFunc, NULL, 0, NULL);
	DWORD exitID;
	GetExitCodeThread(hThead, &exitID);
	if (exitID == STILL_ACTIVE) // 如果线程没有结束,返回STILL_ACTIVE
	{
		printf("子线程没有退出\n");
	}



	DWORD ret = WaitForSingleObject(hThead, 3000);
	if (ret == WAIT_TIMEOUT) {
		printf("WaitForSingleObject等待子线程退出超时\n");
	}

	// 强制终止线程,避免使用
	TerminateThread(hThead, 888);

	// 无线等待,除非子线程运行结束
	WaitForSingleObject(hThead, INFINITE);

	GetExitCodeThread(hThead, &exitID);
	printf("子线程退出吗:%d\n", exitID);
	printf("主线程结尾\n");
	system("pause");
	return 0;
}


DWORD WINAPI TheadFunc(LPVOID lpThreadParameter)
{
	int n = 0;
	while (++n < 6)
	{

		printf("第%d次子线程 hello!\n",n);
		//if (n == 3) {
		//	// 退出线程,退出码666,避免使用
		//	ExitThread(666);
		//}
		Sleep(1000);
	}
	return 0;
}