#include <Windows.h>
#include <process.h>
#include <stdio.h>

DWORD WINAPI ThreadFunc(LPVOID param);

// �������ƺ�ͣ��ʱ��
struct Car
{
	char name[20];
	DWORD time;
};

HANDLE hSemaphore = INVALID_HANDLE_VALUE;
int main(void)
{
	// ֻ��3��ͣ��λ��Դ
	hSemaphore  = CreateSemaphore(NULL, 3, 3, L"ͣ��λ");

	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		printf("�����Ѿ�����,�벻Ҫ�����������!\n");
		getchar();
		// ����Ѿ����ź����������ͷž��
		CloseHandle(hSemaphore);

		return 0;
	}
	printf("�����һ������!\n");

	HANDLE hArr5[5] = { INVALID_HANDLE_VALUE };
	Car * pCar = new Car[5];
	for (int i = 0; i < 5; i++)
	{


		sprintf(pCar[i].name, "����%c", 'A' + i);
		pCar[i].time = 3 + i * 2;
		// ���������߳�
		hArr5[i] = CreateThread(NULL, 0, ThreadFunc, &pCar[i], 0, NULL);


	
	}

	// �ȴ������߳����
	WaitForMultipleObjects(5, hArr5, true, INFINITE);
	delete [] pCar;
	system("pause");
	return 0;
}

DWORD WINAPI ThreadFunc(LPVOID param)
{
	// ���ֹͣλ��Դʣ��(���ź�״̬,�ź���-1),�ͷ���
	WaitForSingleObject(hSemaphore, INFINITE);
	Car * pCar = (Car *)param;

	printf("%sͣ��ͣ����,ͣ��%d��!\n", pCar->name,pCar->time);
	Sleep(1000 * pCar->time);
	printf("%sʻ��ͣ����\n", pCar->name);

	// �ͷ�һ��ͣ��λ(�ź���+1)
	ReleaseSemaphore(hSemaphore, 1, NULL);

	return 0;
}