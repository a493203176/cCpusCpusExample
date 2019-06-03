#include <Windows.h>
#include <stdio.h>

DWORD WINAPI ThreadFun1(LPVOID param);
DWORD WINAPI ThreadFun2(LPVOID param);

// ��̬TLS������
DWORD tlsIndex = 0;

BOOL flag1 = false;
BOOL flag2 = false;

int main(void)
{
	tlsIndex = TlsAlloc();

	if (tlsIndex == TLS_OUT_OF_INDEXES)
	{
		printf("��������ʧ��\n");
		return 0;
	}
	// �����߳�����
	TlsSetValue(tlsIndex, "cpp");
	char * p = (char *)TlsGetValue(tlsIndex);
	printf("���̴߳�ӡ:%s \n", p);

	HANDLE hThread1 = CreateThread(NULL, 0, ThreadFun1, NULL, 0, NULL);
	HANDLE hThread2 = CreateThread(NULL, 0, ThreadFun2, NULL, 0, NULL);

	HANDLE hArr[] = { hThread1, hThread2 };

	WaitForMultipleObjects(2, hArr, TRUE, INFINITE);

	TlsFree(tlsIndex);
	system("pause");
	return 0;
}

DWORD WINAPI ThreadFun1(LPVOID param)
{

	TlsSetValue(tlsIndex, "hello");


	while (TRUE)
	{
		// ÿ���߳�ͬһ������λ�õ������Լ�,�������߳�û�й�ϵ
		char * p = (char *)TlsGetValue(tlsIndex);
		printf("�߳�A��ӡ:%s \n",p);
		Sleep(1000);
	}
}

DWORD WINAPI ThreadFun2(LPVOID param)
{

	TlsSetValue(tlsIndex, "world");
	
	while (TRUE)
	{
		// ÿ���߳�ͬһ������λ�õ������Լ�,�������߳�û�й�ϵ
		char * p = (char *)TlsGetValue(tlsIndex);
		printf("�߳�B��ӡ: %s \n", p);
		Sleep(1000);
	}
}