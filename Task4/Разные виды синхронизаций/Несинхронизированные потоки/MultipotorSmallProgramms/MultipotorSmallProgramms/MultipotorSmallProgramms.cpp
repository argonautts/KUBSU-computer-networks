#include <windows.h>
#include <string>
#include <iostream>
using namespace std;
int num = 0;
int a[5];

DWORD WINAPI TR(LPVOID pr)
{
	int i;
	for (i = 0; i < 10; i++)
	{
		cout << "THREAD2" << endl;
	}
	return 0;
}

int main()
{
	DWORD thID;
	CreateThread(NULL, NULL, TR, NULL, NULL, &thID);
	int k = 0;
	for (int i = 0; i < 10; i++)
	{
		cout << "THREAD1";
	}
	return 0;
}

