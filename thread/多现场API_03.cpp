#include <process.h>
#include <stdio.h>
#include <Windows.h>

void __cdecl ThreadFunc(void * param);
int main(void)
{
	printf("主线程开始\n");
	// 推荐使用
	HANDLE hThread = reinterpret_cast<HANDLE>(_beginthread(ThreadFunc, 0, "hello"));

	WaitForSingleObject(hThread, INFINITE);
	printf("主线程结束\n");
	getchar();
	return 0;
}

void __cdecl ThreadFunc(void * param)
{
	int n = 0;
	char * name = static_cast<char *>(param);
	while (++n <6)
	{
	
		Sleep(1000);
		printf("第%d次打印%s \n", n, name);
		// 结束_beginthread创建的线程,别用ExitThread退出
		if (n == 3) {
			_endthread();
		}
	}
	printf("子线程结束\n");
}