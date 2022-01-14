#include<windows.h>
#include<iostream>
using namespace std;

HANDLE hMutex;//дискриптор

DWORD WINAPI TR(LPVOID pr) {
	int i;
	for (int j = 0; j < 5; j++)
	{
	WaitForSingleObject(hMutex, INFINITE);
	for (i = 0; i < 5; i++) cout << "THREAD2" << endl;
	ReleaseMutex(hMutex);
	}
	return 0;
}

int main() {
	DWORD thID;
	hMutex = CreateMutex(NULL, FALSE, NULL);
	CreateThread(NULL, NULL, TR, NULL, NULL, &thID);
	for (int j = 0; j < 5; j++)
	{
		WaitForSingleObject(hMutex, INFINITE);
		for (int i = 0; i < 5; i++) cout << "THREAD1";
		cout << endl;
		ReleaseMutex(hMutex);
	}
	return 0;
}