#include<process.h>
#include<Windows.h>
#include <stdio.h>

void __cdecl  SellThread1(void * param);
void __cdecl  SellThread2(void * param);

// �¼����
HANDLE hEvent = INVALID_HANDLE_VALUE;
// 100��Ʊ
int ticket = 100;
int main(void)
{
	printf("��ʼ��Ʊ��!");

	// �����¼�,�˿�Ϊ���ź�״̬
	// �Զ������ź�״̬,��ʼ��Ϊ���ź�״̬,�߳�ֱ�ӻ�ȡ
	hEvent = CreateEvent(NULL, FALSE, TRUE, L"�¼�����");

	// ���¼�����Ϊ���ź�״̬
	//ResetEvent(hEvent);

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
	// �����ٽ���,��ֹ�����̷߳���

	while (ticket > 0)
	{
		Sleep(10);
		// ����¼�����Ϊ���ź�״̬(û���߳�ӵ����,���߳̿��Ի�ȡ��ִ��)
		// �Զ����õ��¼�����,������WaitForSingleObject֮��,�Զ�����Ϊ���ź�
		WaitForSingleObject(hEvent, INFINITE);
		if (ticket > 0)
		{
			// CPUǡ��ִ�е�����,���ʱ���߳�ʱ��Ƭ����,���Ҵ�ʱ��ʣ���һ��Ʊ
			printf("%s ������%d��Ʊ!\n", name, ticket--);
		}

		// SetEvent���¼����������ź�״̬
		SetEvent(hEvent);
	}

}
void __cdecl  SellThread2(void * param)
{
	char * name = (char *)param;
	// �����ٽ���,��ֹ�����̷߳���

	while (ticket > 0)
	{
		Sleep(10);
		// ����¼�����Ϊ���ź�״̬(û���߳�ӵ����,���߳̿��Ի�ȡ��ִ��)
		// �Զ����õ��¼�����,������WaitForSingleObject֮��,�Զ�����Ϊ���ź�
		WaitForSingleObject(hEvent, INFINITE);
		if (ticket > 0)
		{
			// CPUǡ��ִ�е�����,���ʱ���߳�ʱ��Ƭ����,���Ҵ�ʱ��ʣ���һ��Ʊ
			printf("%s ������%d��Ʊ!\n", name, ticket--);
		}

		// SetEvent���¼����������ź�״̬
		SetEvent(hEvent);
	}
}
