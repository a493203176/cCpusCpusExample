#include <Windows.h>
#include <queue>
#include <process.h>

using namespace std;

// ��һ���ֿ�
queue<int> store;
int StoreSize = 3; //�ֿ���Է�3������
int ID = 1; // ������ʼID

// ���ʱ������,ģ��������������ѵ��ٶ�
int arr1[10] = { 2, 4, 7, 1 ,3, 6, 8, 1, 4, 2};
int arr2[10] = { 1, 5, 2, 1, 9, 6, 8, 3, 5, 8};

// ��Ҫ�����¼���֪ͨ
HANDLE hEvent1 = INVALID_HANDLE_VALUE; // �л���ʱ֪ͨ������ȡ����
HANDLE hEvent2 = INVALID_HANDLE_VALUE; // �ֿ�Ϊ�յ�ʱ��,֪ͨ�����߿�ʼ����


// ������
void  __cdecl ProducerThread(void * param);
// ������
void  __cdecl CunsumerThread(void * param);

int main(void)
{
	hEvent1 = CreateEvent(NULL, TRUE, TRUE, L"�¼�����1");// ��Ҫ�ȿ�ʼ����
	hEvent2 = CreateEvent(NULL, TRUE, FALSE, L"�¼�����2");// һ��ʼ,�ֿ�û��,ȡ���ȴ�


	uintptr_t t1 = _beginthread(ProducerThread, 0, NULL);
	uintptr_t t2 = _beginthread(CunsumerThread, 0, NULL);

	HANDLE hThreadSet[] = { (HANDLE)t1, (HANDLE)t2 };
	// ���޵ȴ������߳����н���
	WaitForMultipleObjects(2, hThreadSet, TRUE, INFINITE);

	CloseHandle(hEvent1);
	CloseHandle(hEvent2);

	CloseHandle((HANDLE)t1);
	CloseHandle((HANDLE)t2);

	system("pause");

	return 0;
}

// ������
void  __cdecl ProducerThread(void * param)
{
	while (TRUE)
	{
		WaitForSingleObject(hEvent1, INFINITE);
		if (store.size() < StoreSize) // �вֿ��λ
		{
			int id = ID++; // ����id��
			store.push(id);// �ѻ�����õ��ֿ���
			printf("������Ʒid : %d\n", id);
			Sleep(arr1[id%10] * 1000); // ģ��������ʱ��,������
		}
		else // �ֿ�����
		{
			printf("�ֿ�����,�޷�������Ʒ\n");
			ResetEvent(hEvent1);// ���¼���Ϊ���ź��¼�
		}

		// �ֿ��л���,����֪ͨ������ȡ����
		if (store.size() > 0)
		{
			SetEvent(hEvent2);// �������ߵ��¼����¼�
		}
	}
}

//������
void  __cdecl CunsumerThread(void * param)
{
	while (TRUE)
	{
		WaitForSingleObject(hEvent2, INFINITE);
		if (store.size() > 0)
		{
			int commodity = store.front(); // ��ȡ�����л���,�Ƚ��ȳ�
			store.pop(); // ж�߻���,�ڳ���λ
			printf("                   ȡ����Ʒid : %d\n", commodity);
			Sleep(arr2[commodity % 10] * 1000);
		}
		else
		{
			printf("�ֿ����,�޷���ȡ����\n");
			ResetEvent(hEvent2);
		}

		// ˵���ֿ�û����,���Լ�������
		if (store.size() < 3) {
			SetEvent(hEvent1);
		}
	}
}