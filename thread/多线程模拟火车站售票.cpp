#include<process.h>
#include<Windows.h>
#include <stdio.h>

void __cdecl  SellThread1(void * param);
void __cdecl  SellThread2(void * param);

// �ٽ����ṹ
CRITICAL_SECTION crticalSection;
// 100��Ʊ
int ticket = 100;
int main(void)
{
	printf("��ʼ��Ʊ��!");

	// ��ʼ���ٽ���
	InitializeCriticalSection(&crticalSection);

	// ����������Ʊ����
	uintptr_t t1 = _beginthread(SellThread1, 0, "��Ʊ����A");
	uintptr_t t2 = _beginthread(SellThread2, 0, "��Ʊ����B");

	// ���ߵȴ������߳�ȫ��ִ�����
	HANDLE hThreads[] = { (HANDLE)t1, (HANDLE)t2 };
	WaitForMultipleObjects(2, hThreads, true, INFINITE);

	// ɾ���ٽ�����Դ
	DeleteCriticalSection(&crticalSection);
	printf("��Ʊ����!");
	system("pause");
	return 0;
}


void __cdecl  SellThread1(void * param)
{
	char * name = (char *)param;
	// �����ٽ���,��ֹ�����̷߳���

	while (ticket > 0)
	{
		Sleep(10);

		if (TryEnterCriticalSection(&crticalSection))
		{
			if (ticket > 0)
			{
				// CPUǡ��ִ�е�����,���ʱ���߳�ʱ��Ƭ����,���Ҵ�ʱ��ʣ���һ��Ʊ
				printf("%s ������%d��Ʊ!\n", name, ticket--);
			}

			// �뿪�ٽ���
			LeaveCriticalSection(&crticalSection);
		}
			
	}

}
void __cdecl  SellThread2(void * param)
{
	char * name = (char *)param;
	// �����ٽ���,��ֹ�����̷߳���

	while (ticket > 0)
	{
		Sleep(10);
		//���Խ����ٽ���,��������
		if (TryEnterCriticalSection(&crticalSection))
		{
			if (ticket > 0)
			{
				// CPUǡ��ִ�е�����,���ʱ���߳�ʱ��Ƭ����,���Ҵ�ʱ��ʣ���һ��Ʊ
				printf("%s ������%d��Ʊ!\n", name, ticket--);
			}

			// �뿪�ٽ���
			LeaveCriticalSection(&crticalSection);
		}

	}

}
