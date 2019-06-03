#include <Windows.h>
#include <process.h>
#include <stdio.h>

DWORD WINAPI ThreadFunc(LPVOID param);

// 车辆名称和停车时间
struct Car
{
	char name[20];
	DWORD time;
};

HANDLE hSemaphore = INVALID_HANDLE_VALUE;
int main(void)
{
	// 只有3个停车位资源
	hSemaphore  = CreateSemaphore(NULL, 3, 3, L"停车位");

	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		printf("程序已经允许,请不要开启多个进程!\n");
		getchar();
		// 如果已经有信号量存在则释放句柄
		CloseHandle(hSemaphore);

		return 0;
	}
	printf("程序第一次启动!\n");

	HANDLE hArr5[5] = { INVALID_HANDLE_VALUE };
	Car * pCar = new Car[5];
	for (int i = 0; i < 5; i++)
	{


		sprintf(pCar[i].name, "车辆%c", 'A' + i);
		pCar[i].time = 3 + i * 2;
		// 创建车辆线程
		hArr5[i] = CreateThread(NULL, 0, ThreadFunc, &pCar[i], 0, NULL);


	
	}

	// 等待所有线程完毕
	WaitForMultipleObjects(5, hArr5, true, INFINITE);
	delete [] pCar;
	system("pause");
	return 0;
}

DWORD WINAPI ThreadFunc(LPVOID param)
{
	// 如果停止位资源剩余(有信号状态,信号量-1),就放行
	WaitForSingleObject(hSemaphore, INFINITE);
	Car * pCar = (Car *)param;

	printf("%s停入停车场,停车%d秒!\n", pCar->name,pCar->time);
	Sleep(1000 * pCar->time);
	printf("%s驶离停车场\n", pCar->name);

	// 释放一个停车位(信号量+1)
	ReleaseSemaphore(hSemaphore, 1, NULL);

	return 0;
}