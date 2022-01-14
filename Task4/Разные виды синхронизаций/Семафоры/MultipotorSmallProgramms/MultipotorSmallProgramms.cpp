#include<windows.h>
#include<iostream>
using namespace std;

HANDLE hSem, newP1, newP2;//дискриптор

DWORD WINAPI TR(LPVOID pr) {
	int i, num = 0;
	for (int j = 0; j < 5; j++)
	{
		WaitForSingleObject(hSem, INFINITE);
		for (i = 0; i < 5; i++) cout << "THREAD2" << endl;
		num++;
		ReleaseSemaphore(hSem, 1, NULL);
	}
	return 0;
}

DWORD WINAPI RT(LPVOID pr) {
	int i, num = 0;
	for (int j = 0; j < 5; j++)
	{
		WaitForSingleObject(hSem, INFINITE);
		for (i = 0; i < 5; i++) cout << "THREAD3" << endl;
		num++;
		ReleaseSemaphore(hSem, 1, NULL);
	}
	return 0;
}

int main() {
	DWORD thID;
	hSem = CreateSemaphore(NULL, 1, 1, NULL);
	for (int i=0;i<5;i++)
	{
		WaitForSingleObject(hSem, INFINITE);
		newP1 = CreateThread(NULL, 0, TR, NULL, 0, &thID);
		for (int j = 0; j < 5; j++)cout << "THREAD1";
		cout << endl;
		newP2 = CreateThread(NULL, 0, RT, NULL, 0, &thID);
		ReleaseSemaphore(hSem, 1, NULL);
	}
	return 0;
}