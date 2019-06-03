#include<process.h>
#include<Windows.h>
#include <stdio.h>

void __cdecl  SellThread1(void * param);
void __cdecl  SellThread2(void * param);

HANDLE hMutex = INVALID_HANDLE_VALUE;

// 100��Ʊ
int ticket = 100;
int main(void)
{
	printf("��ʼ��Ʊ��!");

	// ����������
	hMutex = CreateMutex(NULL, FALSE, L"��Ʊ������");

	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		printf("ֻ����һ�����̷���\n");
		//������л������������ͷž��
		CloseHandle(hMutex);
		system("pause");
		return 0;
	}

	// ����������Ʊ����
	uintptr_t t1 = _beginthread(SellThread1, 0, "��Ʊ����A");
	uintptr_t t2 = _beginthread(SellThread2, 0, "��Ʊ����B");

	// ���ߵȴ������߳�ȫ��ִ�����
	HANDLE hThreads[] = { (HANDLE)t1, (HANDLE)t2 };
	WaitForMultipleObjects(2, hThreads, true, INFINITE);


	printf("��Ʊ����!");
	system("pause");
	return 0;
}


void __cdecl  SellThread1(void * param)
{
	char * name = (char *)param;

	while (ticket > 0)
	{
		Sleep(10);

		// ������������Ϊ���ź�״̬(û���߳�ӵ����),���ȡ�������ִ��
		WaitForSingleObject(hMutex, INFINITE);
		if (ticket > 0)
		{
			// CPUǡ��ִ�е�����,���ʱ���߳�ʱ��Ƭ����,���Ҵ�ʱ��ʣ���һ��Ʊ
			printf("%s ������%d��Ʊ!\n", name, ticket--);
		}
		// �ͷŶԻ������ӵ��Ȩ,��������ź�״̬
		ReleaseMutex(hMutex);
			
	}

}
void __cdecl  SellThread2(void * param)
{
	char * name = (char *)param;

	while (ticket > 0)
	{
		Sleep(10);

		WaitForSingleObject(hMutex, INFINITE);
		if (ticket > 0)
		{
			// CPUǡ��ִ�е�����,���ʱ���߳�ʱ��Ƭ����,���Ҵ�ʱ��ʣ���һ��Ʊ
			printf("%s ������%d��Ʊ!\n", name, ticket--);
		}
		ReleaseMutex(hMutex);
	}

}
