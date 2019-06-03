#include <Windows.h>
#include <stdio.h>

DWORD WINAPI TheadFunc(LPVOID lpThreadParameter);

int main(void)
{
	printf("主线程开头\n");
	HANDLE hThead1 = CreateThread(NULL, 0, TheadFunc, (LPWORD)"A", 0, NULL);
	HANDLE hThead2 = CreateThread(NULL, 0, TheadFunc, (LPWORD)"B", 0, NULL);
	HANDLE hThead3 = CreateThread(NULL, 0, TheadFunc, (LPWORD)"C", 0, NULL);

	HANDLE handleArr[] = { hThead1, hThead2, hThead3 };
	

	// 无线等待所有线程结束
	//DWORD ret = WaitForMultipleObjects(3, handleArr,true,INFINITE);
	//printf("ret = %d \n", ret == WAIT_OBJECT_0);
	
	//// 等待任意一个线程结束就返回数组索引
	//DWORD ret = WaitForMultipleObjects(3, handleArr, false, INFINITE);
	//printf("ret = %d \n", ret);

	// 设置等待超时时间1秒
	DWORD ret = WaitForMultipleObjects(3, handleArr, false, 1000);
	printf("ret = %d \n", ret==WAIT_TIMEOUT);


	printf("主线程结尾\n");
	system("pause");
	return 0;
}


DWORD WINAPI TheadFunc(LPVOID lpThreadParameter)
{
	int n = 0;
	char * name = static_cast<char *>(lpThreadParameter);

	if (strcmp(name, "A") == 0) {
		
		Sleep(10000);
	}
	else if (strcmp(name, "B") == 0) {

		Sleep(3000);
	}
	else
	{
		Sleep(8000);
	}
	printf("子线程%s结束\n", name);
	return 0;
}