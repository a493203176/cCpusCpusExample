#include <Windows.h> // �߳����ͷ�ļ�
#include <iostream>

using namespace std;

// �̴߳�����,window��׼����Լ��_stdcall
DWORD WINAPI TheadFun(LPVOID lpThreadParameter);

int main(void)
{
	DWORD threadId  = 0;
    HANDLE hThread =   CreateThread(NULL,// ��ΪNULLʹ��Ĭ�ϰ�ȫ��
		0,  // ���Ϊ0,Ĭ�϶�ջ��С
		TheadFun,//�̴߳�����,���������Ǻ���ָ��
		"hello", // ���̴߳���Ĳ���
		0, // ��������������
		&threadId // �߳�id
		);
	if (hThread == nullptr) {
		cout << "�̴߳���ʧ��:" << GetLastError() << endl;
	}
	cout << "�̵߳ľ��:" << hThread << endl;
	cout << "�̵߳�id:" << threadId << endl;

	cout << "���߳�ID:" << GetCurrentThreadId() << endl;

	// �ر��߳̾��,���ü���-1,��û�н����߳�
	//CloseHandle(hThread); // ��ʾ�Ժ������þ��

	getchar();

	// �����߳�
	SuspendThread(hThread);

	getchar();

	// �ָ��߳�ִ��
	ResumeThread(hThread);

	system("pause");
	return 0;
}

DWORD WINAPI TheadFun(LPVOID lpThreadParameter)
{
	char * str = static_cast<char *>(lpThreadParameter);
	while (TRUE)
	{
		cout << "�̴߳�������:" << str << endl;
		cout << "���߳�ID:" << GetCurrentThreadId() << endl;
		Sleep(1000);  // �޸�1��
	}

	return 0;
}