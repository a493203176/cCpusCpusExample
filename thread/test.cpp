#include <windows.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
	//  C:\Users\zhout\documents\visual studio 2013\Projects\C++MutilThread\Debug\C++MutilThread.exe
	TCHAR szPath[MAX_PATH];
	if (!GetModuleFileName(NULL, szPath, MAX_PATH))
	{
		printf("GetModuleFileName failed (%d)\n", GetLastError());
		return FALSE;
	}

	return TRUE;
}