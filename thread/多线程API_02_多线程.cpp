#include <Windows.h>
#include <stdio.h>

DWORD WINAPI TheadFunc(LPVOID lpThreadParameter);

int main(void)
{
	printf("���߳̿�ͷ\n");
	HANDLE hThead1 = CreateThread(NULL, 0, TheadFunc, (LPWORD)"A", 0, NULL);
	HANDLE hThead2 = CreateThread(NULL, 0, TheadFunc, (LPWORD)"B", 0, NULL);
	HANDLE hThead3 = CreateThread(NULL, 0, TheadFunc, (LPWORD)"C", 0, NULL);

	HANDLE handleArr[] = { hThead1, hThead2, hThead3 };
	

	// ���ߵȴ������߳̽���
	//DWORD ret = WaitForMultipleObjects(3, handleArr,true,INFINITE);
	//printf("ret = %d \n", ret == WAIT_OBJECT_0);
	
	//// �ȴ�����һ���߳̽����ͷ�����������
	//DWORD ret = WaitForMultipleObjects(3, handleArr, false, INFINITE);
	//printf("ret = %d \n", ret);

	// ���õȴ���ʱʱ��1��
	DWORD ret = WaitForMultipleObjects(3, handleArr, false, 1000);
	printf("ret = %d \n", ret==WAIT_TIMEOUT);


	printf("���߳̽�β\n");
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
	printf("���߳�%s����\n", name);
	return 0;
}