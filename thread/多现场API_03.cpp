#include <process.h>
#include <stdio.h>
#include <Windows.h>

void __cdecl ThreadFunc(void * param);
int main(void)
{
	printf("���߳̿�ʼ\n");
	// �Ƽ�ʹ��
	HANDLE hThread = reinterpret_cast<HANDLE>(_beginthread(ThreadFunc, 0, "hello"));

	WaitForSingleObject(hThread, INFINITE);
	printf("���߳̽���\n");
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
		printf("��%d�δ�ӡ%s \n", n, name);
		// ����_beginthread�������߳�,����ExitThread�˳�
		if (n == 3) {
			_endthread();
		}
	}
	printf("���߳̽���\n");
}