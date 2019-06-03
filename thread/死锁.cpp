#include <process.h>
#include <Windows.h>
#include <stdio.h>

CRITICAL_SECTION cs1;
CRITICAL_SECTION cs2;


void ThreadFunc1(void * param);
void ThreadFunc2(void * param);

int main(void)
{
	InitializeCriticalSection(&cs1);
	InitializeCriticalSection(&cs2);


   uintptr_t t1 = _beginthread(ThreadFunc1,0,"A");
   uintptr_t t2 = _beginthread(ThreadFunc2,0,"B");

   // A��1����,����B��2�������
   // B��2����,����A��1�������
   // �໥�ȴ�,��������
   HANDLE hArr[] = { (HANDLE)t1, (HANDLE)t2 };
   WaitForMultipleObjects(2, hArr, true, INFINITE);

}
void ThreadFunc1(void * param)
{
	char * name = (char *)param;
	// ����1����֮��,�κ����޷���ȥ1����
	EnterCriticalSection(&cs1);
	printf("%s������1����,��Ϣ3��\n", name);
	Sleep(3000);
	printf("%s�������2����\n", name);
	EnterCriticalSection(&cs2);

	printf("%s�뿪��2����\n", name);
	LeaveCriticalSection(&cs2);
	LeaveCriticalSection(&cs1);

}

void ThreadFunc2(void * param)
{
	char * name = (char *)param;

	// ����2����֮��,�κ����޷���ȥ2����
	EnterCriticalSection(&cs2);
	printf("%s������2����,��Ϣ3��\n", name);
	Sleep(3000);
	printf("%s�������1����\n", name);
	EnterCriticalSection(&cs1);

	printf("%s�뿪��2����\n", name);
	LeaveCriticalSection(&cs1);
	LeaveCriticalSection(&cs2);
}