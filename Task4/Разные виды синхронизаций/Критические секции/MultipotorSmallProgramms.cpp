#include <windows.h>
#include <iostream>
using namespace std;
CRITICAL_SECTION cs;
int a[5];
DWORD WINAPI tr(LPVOID pr)
{
	int i;

	EnterCriticalSection(&cs);
	for (int j = 0; j < 5; j++)  cout << "THREAD2";
	LeaveCriticalSection(&cs);

	return 0;
}
int main()
{
	DWORD thID;
	InitializeCriticalSection(&cs);
	for (int i = 0; i < 5; i++)
	{
		EnterCriticalSection(&cs);
		for (int i = 0; i < 5; i++) cout << "THREAD1";
		cout << endl;
		CreateThread(NULL, NULL, tr, NULL, NULL, &thID);
		LeaveCriticalSection(&cs);
	}
	return 0;
}
